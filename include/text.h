#ifndef TEXT_H
#define TEXT_H

/**
 * @file text.h
 * @brief functions and structures for text generating
*/

#include <stddef.h>

/**
 * @brief struct of one line of text
*/
struct Line
{
    char *line_begin; ///< pointer to the beginning of the line
    char *line_end;   ///< pointer to the line ending
};

/**
 * @brief struct of text buffer
*/
struct Buffer
{
    char *text_buf;   ///< text buffer
    size_t text_size; ///< size of the text in bytes
    size_t n_lines;   ///< number of lines of the text
};

/**
 * @brief struct of text
*/
struct Text
{
    struct Line *lines; ///< Lines dynamic array
    size_t n_lines;     ///< number of lines of the text
};

/**
 * @brief Constructor of the text. Fills @b buf and @b text with data from @b path by calling @b read_text_buf and @b fill_text
 * @param buf pointer to @b Buffer structure
 * @param text pointer to @b Text structure
 * @param path path of the file to read from
 * @return error code from @b errno
*/
int text_ctor(struct Buffer *buf, struct Text *text, const char *path);

/**
 * @brief Reads text from @b path to @b buf
 * @param buf pointer to @b Buffer structure
 * @param path path of the file to read from
 * @return error code from @b errno
*/
int read_text_buf(struct Buffer *buf, const char path[]);

/**
 * @brief Removes empty lines from the buffer
 * @param buf pointer to @b Buffer structure
*/
void text_preprocessing(struct Buffer *buf);

/**
 * @brief Fills @b text with data from @b buf and replaces @b '\n' on @b '\0'
 * @param text pointer to @b Text structure
 * @param buf pointer to @b Buffer structure
*/
void fill_text(struct Text *text, struct Buffer *buf);

/**
 * @brief @b text destructor. Makes the text incapacitated
 * @param text pointer to @b Text structure
*/
void text_dtor(struct Text *text);

/**
 * @brief  @b buf destructor. Makes the buffer incapacitated
 * @param buf pointer to @b Buffer structure
*/
void buf_dtor(struct Buffer *buf);

/**
 * @brief Finds file size by path @b path
 * @param path path tothe file
 * @return Size of file
*/
size_t filesize(const char *path);

#endif //TEXT_H