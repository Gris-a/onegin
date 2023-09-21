#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/text.h"
#include "../include/text_to_file.h"
#include "../include/qsort.h"
#include "../include/comparators.h"

/**
 * @file main.cpp
*/

int main(const int argc, const char *argv[])
{
    struct Buffer buf = {};
    struct Text text  = {};

    int err_code = text_ctor(&buf, &text, "Onegin.txt");
    if(err_code)
    {
        return err_code;
    }

    FILE *onegin_text = fopen("Onegins.txt", "w");

    if(argc == 1)
    {
        fwrite_buffer(&buf, onegin_text);
    }
    else if(argc == 2)
    {
        if(!strcmp(argv[1], "--sort"))
            fwrite_text_sorted(&text, my_line_cmp, onegin_text);
        else if(!strcmp(argv[1], "--sort_reverse"))
            fwrite_text_sorted(&text, my_line_cmp_reverse, onegin_text);
        else
            printf("bag args.\n");
    }
    else
        printf("bag args.\n");


    buf_dtor(&buf);
    text_dtor(&text);
    fclose(onegin_text);

    return EXIT_SUCCESS;
}