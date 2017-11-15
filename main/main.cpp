#include <iostream>
#include <cstring>
#include <fstream>
#include "PatchMaker.h"

using namespace std;

void help() {
    cout << "Great patchizator, version 0.1" << endl
         << "Usage: diff create old_file_name new_file_name [output_patch_file_name]" << endl
         << "   or  diff apply target_file_name patch_file_name" << endl;
}

int main(int argc, char ** argv) {
    if (argc < 3) {
        help();
    } else {
        if (strcmp(argv[1], "create") == 0) {
            PatchMaker maker;
            if (argc == 4) {
                maker.create_patch(argv[2], argv[3]);
            } else if (argc == 5) {
                ofstream out(argv[4]);
                maker.create_patch(argv[2], argv[3], out);
            } else {
                help();
            }
        } else if (strcmp(argv[1], "apply") == 0) {

        } else {
            help();
        }
    }
    return 0;
}