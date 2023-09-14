#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "text.h"
#include "comparators.h"

int main(void)
{
    struct Text text = {};
    FILE *file = fopen("file.txt", "w");

    int err_code = make_text("text.txt", &text);
    if(err_code) return err_code;

    fwrite_text(&text, file);

    fputs("\n\n\n\n\n\n\n\n\n\n", file);

    qsort(text.text, text.n_lines, sizeof(char *), my_strcmp);
    fwrite_text(&text, file);

    fputs("\n\n\n\n\n\n\n\n\n\n", file);

    qsort(text.text, text.n_lines, sizeof(char *), my_strcmp_reverse);
    fwrite_text(&text, file);

    text_destroy(&text);
    fclose(file);

    return EXIT_SUCCESS;

}