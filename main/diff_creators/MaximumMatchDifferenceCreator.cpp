#include <iostream>
#include "MaximumMatchDifferenceCreator.h"

#define dp(a, b) *(dp + (a) * (m + 1) + (b))

vector<FlaggedString>
MaximumMatchDifferenceCreator::get_full_ordered_diff(vector<HashedString> *old_lines,
                                                     vector<HashedString> *new_lines) {
    size_t n = old_lines->size();
    size_t m = new_lines->size();

    // dp[i][j] is the longest sequence (may have breaks)
    // within first i lines of the old text and first j lines of the second one.
    auto *dp = (int *) (malloc((1 + n) * (1 + m) * sizeof(int)));

    // longest sequences will be 0 when any of subtexts is empty
    for (size_t i = 0; i <= n; i++) {
        dp(i, 0) = 0;
    }
    for (size_t i = 0; i <= m; i++) {
        dp(0, i) = 0;
    }

    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= m; j++) {
            if (old_lines->at(i - 1) == new_lines->at(j - 1)) {
                dp(i, j) = dp(i - 1, j - 1) + 1;
            } else {
                dp(i, j) = max(dp(i - 1, j), dp(i, j - 1));
            }
        }
    }

    // getting the path
    size_t result_size = n + m - dp(n, m);
    vector<FlaggedString> result(result_size, FlaggedString("", 0));
    for (size_t index = result_size - 1, i = n, j = m; i + j > 0; index--) {
        if (i > 0 && j > 0 && old_lines->at(i - 1) == new_lines->at(j - 1)) {
            result[index] = FlaggedString(old_lines->at(i - 1).getString(), LINE_KEPT);
            i--;
            j--;
        } else if (j == 0 || i > 0 && dp(i - 1, j) >= dp(i, j - 1)) {
            result[index] = FlaggedString(old_lines->at(i - 1).getString(), LINE_REMOVED);
            i--;
        } else {
            result[index] = FlaggedString(new_lines->at(j - 1).getString(), LINE_ADDED);
            j--;
        }
    }

    delete(dp);
    return result;
}
