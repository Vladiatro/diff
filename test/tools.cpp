#include <fstream>
#include <cstring>

using namespace std;

char *getFilename(char *directory, char *filename) {
    auto *file = (char*) malloc(256 * sizeof(char));
    strcpy(file, directory);
    strcat(file, filename);
    return file;
}

bool files_equal(char *file1, char *file2) {
    ifstream f1(file1);
    ifstream f2(file2);
    if (f1.is_open() && f2.is_open()) {
        string line1, line2;
        while (getline(f1, line1)) {
            if (!getline(f2, line2)) { // not enough lines in file 2
                return false;
            }
            if (line1 != line2) {
                return false;
            }
        }
        if (getline(f2, line2)) { // extra lines in file 2
            return false;
        }
        f1.close();
        f2.close();
    }
    return true;
}