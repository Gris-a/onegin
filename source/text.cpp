#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "../include/text.h"

int text_ctor(struct Buffer *buf, struct Text *text, const char path[])
{
    assert(text != NULL);
    assert(buf  != NULL);

    int err_code = 0;
    if(path)
    {
        if((err_code = read_text_buf(buf, path)))
        {
            return err_code;
        }
    }

    text->n_lines = text_preprocessing(buf);
    text->lines   = (struct Line *)calloc(text->n_lines + 1, sizeof(Line));
    if(text->lines == NULL)
    {
        perror(__func__);

        return ENOMEM;
    }

    text_lines(text, buf);

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
        perror(path);

        return ENOENT;
    }
    buf->text_size = filesize(path);

    buf->text_buf  = (char *)calloc(buf->text_size + 1, sizeof(char));
    if(buf->text_buf == NULL)
    {
        perror(__func__);

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

size_t text_preprocessing(struct Buffer *buf)
{
    assert(buf           != NULL);
    assert(buf->text_buf != NULL);

    char *write_ptr = buf->text_buf;
    char *read_ptr  = buf->text_buf;

    size_t n_lines = 0;

    if(*write_ptr == '\0')
    {
        return 0;
    }
    write_ptr++;
    read_ptr++;

    while(*read_ptr != '\0')
    {
        if(*read_ptr == '\n')
        {
            if(*(read_ptr - 1) != '\n')
            {
                n_lines++;
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
    n_lines += *(read_ptr - 1) != '\n';
    buf->text_buf = (char *)realloc(buf->text_buf, buf->text_size = (size_t)(read_ptr - buf->text_buf + 1));

    return n_lines;
}

void text_lines(struct Text *text, struct Buffer *buf)
{
    assert(text          != NULL);
    assert(text->lines   != NULL);
    assert(buf           != NULL);
    assert(buf->text_buf != NULL);

    char *text_from_buf = buf->text_buf;

    size_t line_len = 0;
    size_t index    = 0;

    text->lines[index].line = text_from_buf;

    while(*text_from_buf != '\0')
    {
        if(*text_from_buf == '\n')
        {
            text->lines[index].len    = line_len;
            text->lines[index].l_num  = index + 1;
            text->lines[++index].line = text_from_buf + 1;

            line_len = 0;
            *text_from_buf = '\0';
        }
        else
        {
            line_len++;
        }

        text_from_buf++;
    }

    if(index < text->n_lines)
    {
        text->lines[index].len   = line_len;
        text->lines[index].l_num = index + 1;
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
    free(buf->text_buf);
}

size_t filesize(const char *path)
{
    assert(path != NULL);

    struct stat file_info = {};
    if(stat(path, &file_info) == -1)
    {
        perror(__func__);
    }

    return (size_t)file_info.st_size;
}