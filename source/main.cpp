#include <stdio.h>
#include <stdlib.h>

#include "../include/text.h"
#include "../include/text_to_file.h"
#include "../include/qsort.h"
#include "../include/comparators.h"

int main(void)
{
    struct Buffer buf = {};
    struct Text text  = {};

    int err_code = text_ctor(&buf, &text, "Onegin.txt");
    if(err_code)
    {
        return err_code;
    }

    FILE *onegin_text = fopen("Onegins.txt", "w");

    fwrite_text_sorted(&text, my_line_cmp, onegin_text);

    fputs("\n\n\n\n\n\n\n\n\n\n", onegin_text);

    fwrite_text_sorted(&text, my_line_cmp_reverse, onegin_text);

    fputs("\n\n\n\n\n\n\n\n\n\n", onegin_text);

    fwrite_buffer(&buf, onegin_text);

    buf_dtor(&buf);
    text_dtor(&text);
    fclose(onegin_text);

    return EXIT_SUCCESS;
}