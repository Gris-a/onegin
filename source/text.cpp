#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "../include/text.h"

int make_text(const char path[], struct Text *text)
{
    assert(path != NULL);
    assert(text != NULL);

    int err_code = 0;

    if((err_code = read_text_buf(path, text)))
    {
        return err_code;
    }

    text->n_lines = n_lines(text->text_buf);
    text->text    = (struct Line *)calloc(text->n_lines + 1, sizeof(Line));
    if(text->text == NULL)
    {
        perror(__func__);

        return ENOMEM;
    }

    text_lines(text);

    return EXIT_SUCCESS;
}

int read_text_buf(const char path[], struct Text *text)
{
    assert(path != NULL);
    assert(text != NULL);

    int err_code = 0;

    FILE *file = fopen(path, "rb");
    if(file == NULL)
    {
        perror(path);

        return ENOENT;
    }
    text->text_size = filesize(path);

    text->text_buf  = (char *)calloc(text->text_size + 1, sizeof(char));
    if(text->text_buf == NULL)
    {
        perror(__func__);

        err_code = ENOMEM;
    }

    if (text->text_buf != NULL)
    {
        size_t n_ch_readed = fread(text->text_buf, sizeof(char), text->text_size, file);

        if(n_ch_readed != text->text_size)
        {
            printf("Error while reading file \"%s\". %zu/%zu chars are read.\n", path, n_ch_readed, text->text_size);

            err_code = EIO;
        }
    }

    fclose(file);

    return err_code;
}

size_t n_lines(const char *buf)
{
    assert(buf != NULL);

    size_t n_lines = 0;

    if(*buf == '\0')
    {
        return 0;
    }
    buf++;

    while(*buf != '\0')
    {
        if(*buf == '\n' && *(buf - 1) != '\n')
        {
            n_lines++;
        }

        buf++;
    }

    n_lines += *(buf - 1) != '\n';

    return n_lines;
}

void text_lines(struct Text *text)
{
    assert(text           != NULL);
    assert(text->text_buf != NULL);
    assert(text->text     != NULL);

    char *buf = text->text_buf;

    size_t line_len = 0;
    size_t index    = 0;

    text->text[index].line = buf;

    while(*buf != '\0')
    {
        if(*buf == '\n')
        {
            if(line_len > 0)
            {
                text->text[index].len    = line_len;
                text->text[index].l_num  = index + 1;
                text->text[++index].line = buf + 1;

                line_len = 0;
            }
            else
            {
                text->text[index].line += 1;
            }
            *buf = '\0';
        }
        else
        {
            line_len++;
        }

        buf++;
    }

    if(index < text->n_lines)
    {
        text->text[index].len   = line_len;
        text->text[index].l_num = index + 1;
    }
}

void text_destroy(struct Text *text)
{
    assert(text != NULL);

    text->text_size = 0;
    text->n_lines   = 0;

    free(text->text_buf);
    free(text->text);
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