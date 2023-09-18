#include <assert.h>
#include <stdio.h>

#include "../include/text_to_file.h"
#include "../include/qsort.h"
//TODO return value
void fwrite_text_sorted(struct Text *text, int (*cmp_func)(const void *, const void *), FILE *file)
{
    assert(file     != NULL);
    assert(text     != NULL);
    assert(cmp_func != NULL);

    my_qsort(text->text, text->text + text->n_lines - 1, sizeof(Line), cmp_func);

    fwrite_text(text, file);
    fputs("\n\n\n\n\n\n\n\n\n\n", file);
}

void fwrite_text(const struct Text *text, FILE *file)
{
    assert(file       != NULL);
    assert(text       != NULL);
    assert(text->text != NULL);

    for(size_t i = 0; i < text->n_lines; i++)
    {
        fprintf(file, "%4zu\t%s\n", text->text[i].l_num, text->text[i].line);
    }
}