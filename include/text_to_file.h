#ifndef TEXT_TO_FILE_H
#define TEXT_TO_FILE_H

/**
 * @file text_to_file.h
 * @brief functions for writing @b Text to file
*/

#include <stdio.h>
#include "text.h"

/**
 * @brief Sorts text and write it to the file. Calls @b qsort and @b fwrite_text
 * @param text pointer to @b Text structure
 * @param cmp_func function comparator for @b qsort
 * @param file pointer to file to write in
*/
void fwrite_text_sorted(struct Text *text, int (*cmp_func)(const void *, const void *), FILE *file);

/**
 * @brief Writes text to the file
 * @param text pointer to @b Text structure
 * @param file pointer to file to write in
*/
void fwrite_text(const struct Text *text, FILE *file);

/**
 * @brief Writes text buffer to the file
 * @param buf pointer to @b Buffer structure
 * @param file pointer to file to write in
*/
void fwrite_buffer(const struct Buffer *buf, FILE *file);

#endif //TEXT_TO_FILE_H