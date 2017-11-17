#include <iostream>
#include "LinesCopier.h"

LinesCopier::LinesCopier(char *old_file_name, ostream &target) : out(target) {
    in = ifstream(old_file_name);
    if (!in.is_open()) {
        cerr << "Unable to open " << old_file_name << endl;
        exit(1);
    }
}

bool LinesCopier::copy_lines_until(int targetPos) {
    while (pos < targetPos) {
        string line;
        if (!getline(in, line)) {
            return false;
        }
        end_line();
        out << line;
        pos++;
    }
    return true;
}

void LinesCopier::copy_remaining_lines() {
    string line;
    while (getline(in, line)) {
        end_line();
        out << line;
    }
}

void LinesCopier::close() {
    in.close();
}

void LinesCopier::insert_line(char *line) {
    end_line();
    out << line;
}

bool LinesCopier::check_and_copy_line(char *expected_line) {
    string line;
    bool result = getline(in, line) && expected_line == line;
    if (result) {
        end_line();
        out << line;
    }
    pos++;
    return result;
}

bool LinesCopier::check_and_skip_line(char *expected_line) {
    string line;
    pos++;
    return getline(in, line) && expected_line == line;
}

void LinesCopier::end_line() {
    if (not_first_line) {
        out << endl;
    } else {
        not_first_line = true;
    }
}
