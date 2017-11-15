#include <iostream>
#include "UnifiedFormat.h"

#define BLOCK_COST 2 // extra lines when new block appears

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
