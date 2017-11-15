#ifndef DIFF_UNIFIED_FORMAT_H
#define DIFF_UNIFIED_FORMAT_H


#include "PatchFormat.h"

/**
 * Outputs and inputs git-like diff format:
 * \code
 * ---old.txt
 * +++new.txt
 * @@ -1,2 +1,2 @@
 *  kept line
 * +added line
 * -removed line
 *
 * @@ -3,2 +3,3 @@
 * -1
 * -2
 * +3
 * +4
 * +5
 * \endcode
 *
 * Implements very simple algorithm which has main idea of minimizing of the output.
 */
class UnifiedFormat : public PatchFormat {
    /**
     * Packs the input and outputs it.
     *
     * @param old_file_name
     * @param new_file_name
     * @param ordered_diff vector of strings and string status flags
     *          (either LINE_ADDED, LINE_REMOVED, or LINE_KEPT)
     * @param target stream to output
     */
    void output_lines(char *old_file_name, char *new_file_name, vector<FlaggedString> *ordered_diff,
                      ostream &target) override;
};


#endif //DIFF_UNIFIED_FORMAT_H
