#ifndef DIFF_FLAGGED_H
#define DIFF_FLAGGED_H

#define FLAG int

/**
 * An object with a flag to represent something (e.g. either a string is added, removed or keeped)
 */
template <typename T>
class flagged {
public:
    T object;
    FLAG flag;

    flagged(T o, FLAG f) {
        object = o;
        flag = f;
    }
};

#endif //DIFF_FLAGGED_H
