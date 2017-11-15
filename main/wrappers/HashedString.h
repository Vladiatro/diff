#ifndef DIFF_HASHED_STRING_H
#define DIFF_HASHED_STRING_H

using namespace std;

// a class to be used for many repeating string comparisons
class HashedString {
public:
    explicit HashedString(string str);

    bool operator == (HashedString str);

    string getString() {
        return str;
    }

private:
    string str;
    size_t hash_code;
};


#endif //DIFF_HASHED_STRING_H
