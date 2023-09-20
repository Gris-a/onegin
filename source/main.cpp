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

    fwrite_text_sorted(&text, my_strcmp         , onegin_text);

    fwrite_text_sorted(&text, base_text_cmp     , onegin_text);

    fwrite_text_sorted(&text, my_strcmp_reverse , onegin_text);

    fwrite_text_sorted(&text, length_cmp        , onegin_text);

    fwrite_text_sorted(&text, length_cmp_reverse, onegin_text);

    buf_dtor(&buf);
    text_dtor(&text);
    fclose(onegin_text);

    return EXIT_SUCCESS;
}