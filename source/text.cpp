#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "text.h"

int make_text(const char path[], struct Text *text)
{
    assert(path != NULL);
    assert(text != NULL);

    int err_code = 0;

    if(err_code = read_text_buf(path, text))
    {
        return err_code;
    }

    text->n_lines = n_lines(text->text_buf);
    text->text    = (char **)calloc(text->n_lines + 1, sizeof(char *));
    if(text->text == NULL)
    {
        printf("Function %s: Unable to allocate memory.\n", __func__);

        return ENOMEM;
    }

    text_lines(text);

    return EXIT_SUCCESS;
}

size_t n_lines(const char *buf)
{
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

    size_t str_len = 0;
    size_t index   = 0;

    text->text[index++] = buf;

    while(*buf != '\0')
    {
        if(*buf == '\n')
        {
            if(str_len == 0)
            {
                text->text[index - 1] += 1;
            }
            else
            {
                text->text[index++] = buf + 1;

                str_len = 0;
            }
            *buf = '\0';
        }
        else
        {
            str_len++;
        }

        buf++;
    }

    text->text[text->n_lines] = NULL;
}

int read_text_buf(const char path[], struct Text *text)
{
    assert(path != NULL);
    assert(text != NULL);

    int err_code = 0;

    FILE *file = fopen(path, "rb");
    if(file == NULL)
    {
        printf("No such file \"%s\" \n", path);

        return ENOENT;
    }
    text->text_size = filesize(path);

    text->text_buf  = (char *)calloc(text->text_size + 1, sizeof(char));
    if(text->text_buf == NULL)
    {
        printf("Function %s: Unable to allocate memory.\n", __func__);

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

void fwrite_text(const struct Text *text, FILE *file)
{
    for(size_t i = 0; i < text->n_lines; i++)
    {
        fputs(text->text[i], file);
        putc('\n', file);
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
    stat(path, &file_info);

    return (size_t)file_info.st_size;
}