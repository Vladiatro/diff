#ifndef DIFF_MAXIMUM_MATCH_DIFF_CREATOR_H
#define DIFF_MAXIMUM_MATCH_DIFF_CREATOR_H

#define t flagged<string>


#include "DifferenceCreator.h"

/**
 * Creates a difference with the most possible matches.
 */
class MaximumMatchDifferenceCreator : public DifferenceCreator {
public:
    vector<FlaggedString>
    get_full_ordered_diff(vector<HashedString> *old_lines, vector<HashedString> *new_lines) override;

};


#endif //DIFF_MAXIMUM_MATCH_DIFF_CREATOR_H
