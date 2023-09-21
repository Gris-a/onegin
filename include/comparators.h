#ifndef COMPARATORS_H
#define COMPARATORS_H

/**
 * @file comparators.h
 * @brief Functions-comparators for qsort @b Text structure
*/

/**
 * @brief Function-comparator for sorting lines from left to right
 * @param line1 first line to compare
 * @param line2 second line to compare
 * @return difference between two first not matching chars
*/
int my_line_cmp(const void *line1, const void *line2);

/**
 * @brief Function-comparator for sorting lines from right to left
 * @param line1 first line to compare
 * @param line2 second line to compare
 * @return difference between two first not matching chars
*/
int my_line_cmp_reverse(const void *line1, const void *line2);

#endif //COMPARATORS_H