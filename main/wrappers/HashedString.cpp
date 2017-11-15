#include <system_error>
#include "HashedString.h"

HashedString::HashedString(std::string s) {
    str = s;
    hash_code = std::hash<std::string>{}(s);
}

bool HashedString::operator==(HashedString s) {
    if (s.hash_code != hash_code) {
        return false;
    }
    return str == s.str;
}
