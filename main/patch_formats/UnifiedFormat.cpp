#include <iostream>
#include <regex>
#include <fstream>
#include "UnifiedFormat.h"
#include "../io/LinesCopier.h"

#define BLOCK_COST 2 // extra lines when new block appears

const char *CORRUPTED_INPUT = "Error: input file is corrupted";

const char *CORRUPTED_PATCH = "Error: patch file is corrupted";

void block_begin(size_t old_from, size_t old_length, size_t new_from, size_t new_length,
                 ostream &target) {
    target << "@@ -" << old_from << "," << old_length << " +" << new_from << "," << new_length << " @@" << endl;
}

void output_block(size_t old_from, size_t old_length, size_t new_from, size_t new_length,
                  size_t pos, vector<FlaggedString > *ordered_diff, ostream &target) {
    block_begin(old_from, old_length, new_from, new_length, target);
    while (old_length > 0 || new_length > 0) {
        auto line = ordered_diff->at(pos);
        if (line.flag == LINE_KEPT) {
            target << " " << line.object << endl;
            old_length--;
            new_length--;
        } else if (line.flag == LINE_ADDED) {
            target << "+" << line.object << endl;
            new_length--;
        } else {
            target << "-" << line.object << endl;
            old_length--;
        }
        pos++;
    }
    target << endl;
}

void UnifiedFormat::output_lines(char *old_file_name, char *new_file_name,
                                 vector<FlaggedString> *ordered_diff,
                                 ostream &target) {
    target << "---" << old_file_name << endl;
    target << "+++" << new_file_name << endl;

    long block_start = -1,   // start of currently processing block (-1 if none is processing)
            keep_length = 0; // length (in lines) of the block with the same text
    size_t old_from = 1,
            old_length = 0,
            new_from = 1,
            new_length = 0;
    for (long pos = 0; pos < ordered_diff->size(); pos++) {
        auto line = ordered_diff->at(pos);
        if (line.flag == LINE_KEPT) {
            if (block_start == -1) {
                old_from++;
                new_from++;
                continue;
            }
            keep_length++;
            if (keep_length > BLOCK_COST) {
                // it's OK to end the block now because of long equal text
                output_block(old_from, old_length, new_from, new_length, block_start, ordered_diff, target);
                block_start = -1;
                old_from += keep_length + old_length;
                new_from += keep_length + new_length;
                keep_length = 0;
            }
        } else {
            if (block_start == -1) {
                block_start = pos;
                old_length = 0;
                new_length = 0;
            }
            old_length += keep_length;
            new_length += keep_length;
            keep_length = 0;
            if (line.flag == LINE_ADDED) {
                new_length++;
            } else {
                old_length++;
            }
        }
    }
    if (block_start != -1) {
        output_block(old_from, old_length, new_from, new_length, block_start, ordered_diff, target);
    }
}

struct BlockBounds {
    int from;
    int length;
};

/**
 * Gets bounds from block's header's part like "4, 5" (will be from=4, length=5) and "5" (from=5, length=1)
 * @param input string with one number or two numbers separated by comma
 * @return bounds
 */
BlockBounds getBounds(const string &input) {
    BlockBounds result{};
    result.from = std::stoi(input);

    size_t comma = input.find(",");
    if (comma == string::npos) {
        result.length = 1;
    } else {
        result.length = std::stoi(input.substr(comma + 1));
    }

    return result;
}

void throw_error(const string &message) {
    cerr << message << endl;
    exit(1);
}

void UnifiedFormat::apply_patch(char *old_file_name, char *patch_file_name, ostream &target) {
    const regex block_header_regex(R"(@@ \-(\d+(?:,\d+)?) \+(\d+(?:,\d+)?) @@)");

    LinesCopier copier(old_file_name, target);
    ifstream patch(patch_file_name);
    if (patch.is_open()) {
        string line;

        // skip first two lines with file names
        getline(patch, line);
        getline(patch, line);

        while (getline(patch, line)) {
            smatch match;
            if (regex_search(line, match, block_header_regex)) { // read block header
                BlockBounds oldBounds = getBounds(match.str(1));
                BlockBounds newBounds = getBounds(match.str(2));
                if (!copier.copy_lines_until(oldBounds.from)) {
                    // input file is smaller than expected
                    throw_error(CORRUPTED_INPUT);
                }
                int currentOldLength = 0;
                int currentNewLength = 0;
                while (currentOldLength < oldBounds.length ||
                        currentNewLength < newBounds.length) {
                    if (!getline(patch, line)) {
                        // patch file is smaller than expected
                        throw_error(CORRUPTED_PATCH);
                    }
                    switch (line[0]) {
                        case '+':
                            copier.insert_line(&line[1]);
                            currentNewLength++;
                            break;
                        case ' ':
                            if (!copier.check_and_copy_line(&line[1])) {
                                // unexpected line
                                throw_error(CORRUPTED_INPUT);
                            }
                            currentOldLength++;
                            currentNewLength++;
                            break;
                        case '-':
                            if (!copier.check_and_skip_line(&line[1])) {
                                // unexpected line
                                throw_error(CORRUPTED_INPUT);
                            }
                            currentOldLength++;
                            break;
                        default:
                            throw_error(CORRUPTED_PATCH);
                    }
                }
            }
        }
        copier.copy_remaining_lines();
        copier.close();
        patch.close();
    } else {
        throw_error("Unable to open patch file");
    }
}