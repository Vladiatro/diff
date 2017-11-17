#include <gtest/gtest.h>
#include <dirent.h>
#include <fstream>
#include <main/PatchMaker.h>
#include <main/patch_formats/UnifiedFormat.h>
#include "tools.cpp"

/**
 * Test that make diff between every file in directory 'old' and corresponding file in 'new'
 * and then applies resultant patch to the old file and expects its equality to the new.
 */
TEST(RoundTripTest, TestMain) {
    PatchMaker maker;
    UnifiedFormat format = UnifiedFormat();
    DIR *dir;
    struct dirent *file;
    if ((dir = opendir("resources/old/")) != NULL) {
        while ((file = readdir(dir)) != NULL) {
            if (strcmp(file->d_name, "..") != 0 && strcmp(file->d_name, ".") != 0) {
                // go through all files
                ofstream diff("diff.txt");
                char *oldFile = getFilename((char*) "resources/old/", file->d_name);
                char *newFile = getFilename((char*) "resources/new/", file->d_name);
                maker.create_patch(oldFile, newFile, diff);
                diff.close();
                ofstream patched("patched_old.txt");
                format.apply_patch(oldFile, (char*) "diff.txt", patched);
                patched.close();
                EXPECT_TRUE(files_equal(newFile, "patched_old.txt")) << "Failure on file " << file->d_name;
                delete oldFile;
                delete newFile;
            }
        }
        closedir(dir);
    }
}