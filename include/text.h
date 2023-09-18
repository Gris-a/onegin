#ifndef TEXT_H
#define TEXT_H

#include <stddef.h>
struct Line
{
    char *line;
    size_t len;
    size_t l_num;
};

struct Text
{
    char *text_buf;
    size_t text_size;

    struct Line *text;
    size_t n_lines;
};


int make_text(const char path[], struct Text *text);

int read_text_buf(const char path[], struct Text *text);

size_t n_lines(const char *buf);

void text_lines(struct Text *text);

void text_dtor(struct Text *text);

size_t filesize(const char *path);

#endif //TEXT_H