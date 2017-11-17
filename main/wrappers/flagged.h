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

    friend bool operator == (flagged<T> f1, flagged<T> f2) {
        return f1.object == f2.object && f1.flag == f2.flag;
    }
};

#endif //DIFF_FLAGGED_H
