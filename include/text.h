#ifndef TEXT_H
#define TEXT_H

#include <stddef.h>

struct Text
{
    char *text_buf;
    size_t text_size;

    char **text;
    size_t n_lines;
};

int make_text(const char path[], struct Text *text);

size_t n_lines(const char *buf);

void text_lines(struct Text *text);

int read_text_buf(const char path[], struct Text *text);

void fwrite_text(const struct Text *text, FILE *file);

void text_destroy(struct Text *text);

size_t filesize(const char *path);

#endif //TEXT_H