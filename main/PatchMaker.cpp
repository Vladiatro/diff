#include "PatchMaker.h"
#include "diff_creators/MaximumMatchDifferenceCreator.h"
#include "patch_formats/UnifiedFormat.h"

#include <fstream>

vector<HashedString> get_hashed_file_lines(char *file_name) {
    ifstream in(file_name);
    if (in.is_open()) {
        string line;
        vector<HashedString> lines;
        lines.begin();
        while (getline(in, line)) {
            lines.emplace_back(line);
        }
        in.close();
        return lines;
    } else {
        cerr << "Unable to open " << file_name << endl;
        exit(1);
    }
}

void PatchMaker::create_patch(char *old_file_name, char *new_file_name, ostream& target) {
    auto old_lines = get_hashed_file_lines(old_file_name);
    auto new_lines = get_hashed_file_lines(new_file_name);

    if (diffCreator == nullptr) {
        diffCreator = new ptr<DifferenceCreator>(new MaximumMatchDifferenceCreator());
    }
    if (patchFormat == nullptr) {
        patchFormat = new ptr<PatchFormat>(new UnifiedFormat());
    }

    auto ordered_diff = get_full_ordered_diff(old_lines, new_lines);
    output_lines(old_file_name, new_file_name, &ordered_diff, target);
}

vector<FlaggedString> PatchMaker::get_full_ordered_diff(vector<HashedString> old_lines,
                                                                      vector<HashedString> new_lines) {
    return diffCreator->get()->get_full_ordered_diff(&old_lines, &new_lines);
}

void PatchMaker::output_lines(char *old_file_name, char *new_file_name,
                              vector<FlaggedString> *ordered_diff, ostream &target) {
    patchFormat->get()->output_lines(old_file_name, new_file_name, ordered_diff, target);
}
