#ifndef DIFF_CREATE_PATCH_H
#define DIFF_CREATE_PATCH_H

#include <iostream>
#include <vector>
#include <memory>
#include "wrappers/flagged.h"
#include "wrappers/HashedString.h"
#include "diff_creators/DifferenceCreator.h"
#include "patch_formats/PatchFormat.h"

using namespace std;

/**
 * Linear patch creator. Uses MaximumMatchDifferenceCreator as the default difference creator
 * and UnifiedFormat as the default format.
 *
 * Note that it keeps all the text in the memory and expected to work
 * approximately at O(lines_in_old_text * lines_in_new_text).
 */
class PatchMaker {
public:
    /**
     * Creates a patch and outputs it in target (console if not specified).
     * @param old_file_name
     * @param new_file_name
     * @param target stream where to output the result
     */
    void create_patch(char *old_file_name, char *new_file_name, ostream& target = cout);

    void set_difference_creator(ptr<DifferenceCreator> *creator) {
        diffCreator = creator;
    }

    void set_patch_format(ptr<PatchFormat> *format) {
        patchFormat = format;
    }

protected:
    vector<FlaggedString> get_full_ordered_diff(vector<HashedString> old_lines,
                                                  vector<HashedString> new_lines);

    void output_lines(char *old_file_name, char *new_file_name,
                      vector<FlaggedString> *ordered_diff, ostream& target);

private:
    ptr<DifferenceCreator> *diffCreator = nullptr;

    ptr<PatchFormat> *patchFormat = nullptr;

};


#endif //DIFF_CREATE_PATCH_H
