#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/text.h"

/**
 * @file text.cpp
 * @brief text.h functions
*/

int text_ctor(struct Buffer *buf, struct Text *text, const char *path)
{
    assert(text != NULL);
    assert(buf  != NULL);
    assert(path != NULL);

    int err_code = 0;
    if((err_code = read_text_buf(buf, path)))
    {
        return err_code;
    }

    text_preprocessing(buf);

    text->n_lines = buf->n_lines;
    text->lines   = (struct Line *)calloc(text->n_lines + 1, sizeof(Line));
    if(text->lines == NULL)
    {
        printf("%s: Unable to allocate memory", __PRETTY_FUNCTION__);

        return ENOMEM;
    }

    fill_text(text, buf);

    return EXIT_SUCCESS;
}

int read_text_buf(struct Buffer *buf, const char path[])
{
    assert(path != NULL);
    assert(buf  != NULL);

    int err_code = 0;

    FILE *file = fopen(path, "rb");
    if(file == NULL)
    {
        printf("No such file \"%s\"", path);

        return ENOENT;
    }

    buf->text_size = filesize(path);
    buf->text_buf  = (char *)calloc(buf->text_size + 1, sizeof(char));
    if(buf->text_buf == NULL)
    {
        printf("%s: Unable to allocate memory", __PRETTY_FUNCTION__);

        err_code = ENOMEM;
    }

    if (buf->text_buf != NULL)
    {
        size_t n_ch_readed = fread(buf->text_buf, sizeof(char), buf->text_size, file);

        if(n_ch_readed != buf->text_size)
        {
            printf("Error while reading file \"%s\". %zu/%zu chars are read.\n", path, n_ch_readed, buf->text_size);

            err_code = EIO;
        }
    }

    fclose(file);

    return err_code;
}

void text_preprocessing(struct Buffer *buf)
{
    assert(buf           != NULL);
    assert(buf->text_buf != NULL);

    if(*buf->text_buf == '\0')
    {
        return;
    }

    char *write_ptr = buf->text_buf + 1;
    char *read_ptr  = buf->text_buf + 1;
    if(*buf->text_buf == '\n')
    {
        write_ptr--;
    }
    buf->n_lines = 0;

    while(*read_ptr != '\0')
    {
        if(*read_ptr == '\n')
        {
            if(*(read_ptr - 1) != '\n')
            {
                buf->n_lines++;
            }
            else
            {
                read_ptr++;

                continue;
            }
        }

        *write_ptr = *read_ptr;
        read_ptr++;
        write_ptr++;
    }
    *write_ptr = *read_ptr;

    buf->n_lines += (*(read_ptr - 1) != '\n');
    buf->text_buf = (char *)realloc(buf->text_buf, buf->text_size = (size_t)(write_ptr - buf->text_buf + 1));
}

void fill_text(struct Text *text, struct Buffer *buf)
{
    assert(text          != NULL);
    assert(text->lines   != NULL);
    assert(buf           != NULL);
    assert(buf->text_buf != NULL);

    char *text_from_buf = buf->text_buf;

    size_t line_count = 0;

    text->lines[line_count].line_begin = text_from_buf;

    while(*text_from_buf != '\0')
    {
        if(*text_from_buf == '\n')
        {
            text->lines[line_count++].line_end = text_from_buf;
            text->lines[line_count].line_begin = text_from_buf + 1;

            *text_from_buf = '\0';
        }

        text_from_buf++;
    }

    if(line_count < text->n_lines)
    {
        text->lines[line_count].line_end = text_from_buf;
    }
}

void text_dtor(struct Text *text)
{
    assert(text != NULL);

    text->n_lines = 0;
    free(text->lines);
}

void buf_dtor(struct Buffer *buf)
{
    assert(buf != NULL);

    buf->text_size = 0;
    buf->n_lines   = 0;
    free(buf->text_buf);
}

size_t filesize(const char *path)
{
    assert(path != NULL);

    struct stat file_info = {};
    if(stat(path, &file_info) == -1)
    {
        printf("No such file \"%s\"", path);
    }

    return (size_t)file_info.st_size;
}