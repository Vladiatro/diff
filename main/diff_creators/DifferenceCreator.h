#ifndef DIFF_DIFF_CREATOR_H
#define DIFF_DIFF_CREATOR_H

#include <vector>
#include <string>
#include <memory>
#include "../wrappers/HashedString.h"
#include "../wrappers/flagged.h"
#include "../macro.h"

class DifferenceCreator {
public:
    virtual vector<FlaggedString> get_full_ordered_diff(vector<HashedString> *old_lines,
                                                  vector<HashedString> *new_lines) = 0;
};

#endif //DIFF_DIFF_CREATOR_H
