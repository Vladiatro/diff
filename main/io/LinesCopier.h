//
// Created by vladiator on 11/17/17.
//

#ifndef DIFF_LINESMOVER_H
#define DIFF_LINESMOVER_H


#include <ostream>
#include <fstream>

using namespace std;

/**
 * Utility class for iterating through a file and copying lines from it to another file.
 * Also checks consistency of the initial file and can add custom lines to target.
 */
class LinesCopier {
public:
    LinesCopier(char *old_file_name, ostream &target);

    /**
     * Copies lines to the target file until target line.
     * By the end iterator stands on the targetPos.
     * @param targetPos line until which copy lines (starting from 1, not included)
     * @return false if targetPos is greater than number of lines in the file
     */
    bool copy_lines_until(int targetPos);

    /**
     * Copies all the remaining lines to the target file.
     */
    void copy_remaining_lines();

    /**
     * Closes input file.
     */
    void close();

    /**
     * Inserts a line to the target file without iterating through the initial one.
     * @param line inserted line
     */
    void insert_line(char *line);

    /**
     * Checks if line at the current position is equal to expected_line and outputs it to the target file.
     * Makes iteration step.
     * @param expected_line expected current line in the initial file.
     * @return true if expected_line is equal to current line, false otherwise.
     */
    bool check_and_copy_line(char *expected_line);

    /**
     * Checks if line at the current position is equal to expected_line and just skips it.
     * Makes iteration step.
     * @param expected_line expected current line in the initial file.
     * @return true if expected_line is equal to current line, false otherwise.
     */
    bool check_and_skip_line(char *expected_line);

private:
    ifstream in;
    ostream &out;
    int pos = 1;

    bool not_first_line = false;
    void end_line();
};


#endif //DIFF_LINESMOVER_H
