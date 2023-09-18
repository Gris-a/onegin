#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/text.h"
#include "../include/qsort.h"
#include "../include/comparators.h"

int main(void)
{
    struct Text text = {};
    int err_code = make_text("Onegin.txt", &text);
    if(err_code)
    {
        return err_code;
    }

    FILE *onegin_text = fopen("Onegins.txt", "w");

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), my_strcmp);
    fputs("sorted Onegin\n", onegin_text);
    fwrite_text(&text, onegin_text);
    fputs("\n\n\n\n\n\n\n\n\n\n", onegin_text);

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), base_text_cmp);
    fputs("Onegin\n", onegin_text);
    fwrite_text(&text, onegin_text);
    fputs("\n\n\n\n\n\n\n\n\n\n", onegin_text);

    my_qsort(text.text, text.text + text.n_lines - 1, sizeof(Line), my_strcmp_reverse);
    fputs("reverse-sorted Onegin\n", onegin_text);
    fwrite_text(&text, onegin_text);

    text_destroy(&text);
    fclose(onegin_text);

    return EXIT_SUCCESS;
}