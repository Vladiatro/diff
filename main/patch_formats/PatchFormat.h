//
// Created by vladiator on 11/15/17.
//

#ifndef DIFF_PATCH_FORMAT_H
#define DIFF_PATCH_FORMAT_H

#include <vector>
#include <string>
#include "../wrappers/HashedString.h"
#include "../wrappers/flagged.h"
#include "../macro.h"

/**
 * Abstract patch format which is used for ready difference output and for patch applying.
 */
class PatchFormat {
public:
    /**
     * Output lines from ordered_diff in required format.
     * @param old_file_name
     * @param new_file_name
     * @param ordered_diff
     * @param target
     */
    virtual void output_lines(char *old_file_name, char *new_file_name,
                              vector<FlaggedString> *ordered_diff, ostream& target) = 0;

    /**
     * Applies the patch.
     * @param old_file_name
     * @param patch_file_name
     * @param target
     */
    virtual void apply_patch(char *old_file_name, char *patch_file_name,
                             ostream& target) = 0;
};

#endif //DIFF_PATCH_FORMAT_H
