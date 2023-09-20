#include <assert.h>
#include <stdio.h>

#include "../include/text_to_file.h"
#include "../include/qsort.h"

void fwrite_text_sorted(struct Text *text, int (*cmp_func)(const void *, const void *), FILE *file)
{
    assert(file        != NULL);
    assert(text        != NULL);
    assert(text->lines != NULL);
    assert(cmp_func    != NULL);

    my_qsort(text->lines, text->lines + text->n_lines - 1, sizeof(Line), cmp_func);

    fwrite_text(text, file);
}

void fwrite_text(const struct Text *text, FILE *file)
{
    assert(file        != NULL);
    assert(text        != NULL);
    assert(text->lines != NULL);

    for(size_t i = 0; i < text->n_lines; i++)
    {
        fputs(text->lines[i].line_begin, file);
        putc('\n', file);
    }
}