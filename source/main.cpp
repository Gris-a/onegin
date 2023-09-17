#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/text.h"
#include "../include/qsort.h"
#include "../include/comparators.h"

int main(void)
{
    struct Text text = {};
    FILE *file = fopen("oNIGGinERS.txt", "w");

    int err_code = make_text("oNIGGinA.txt", &text);
    if(err_code) return err_code;

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), my_strcmp);
    fwrite_text(&text, file);

    fputs("\n\n\n\n\n\n\n\n\n\n", file);

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), base_text_cmp);
    fwrite_text(&text, file);

    fputs("\n\n\n\n\n\n\n\n\n\n", file);

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), my_strcmp_reverse);
    fwrite_text(&text, file);

    text_destroy(&text);
    fclose(file);

    return EXIT_SUCCESS;
}