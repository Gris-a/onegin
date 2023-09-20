#ifndef TEXT_H
#define TEXT_H

#include <stddef.h>
struct Line
{
    char *line_begin;
    char *line_end;
};

struct Buffer
{
    char *text_buf;
    size_t text_size;
    size_t n_lines;
};

struct Text
{
    struct Line *lines;
    size_t n_lines;
};


int text_ctor(struct Buffer *buf, struct Text *text, const char *path = NULL);

int read_text_buf(struct Buffer *buf, const char path[]);

void text_preprocessing(struct Buffer *buf);

void fill_text(struct Text *text, struct Buffer *buf);

void text_dtor(struct Text *text);

void buf_dtor(struct Buffer *buf);

size_t filesize(const char *path);

#endif //TEXT_H