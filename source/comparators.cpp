#include <assert.h>
#include <ctype.h>
#include <stddef.h>

#include "comparators.h"

int my_strcmp(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);

    const char *str1 = *(const char * const *)a;
    const char *str2 = *(const char * const *)b;

    while(true)
    {
        while(*str1 != '\0' && !isalpha(*str1)) str1++;
        while(*str2 != '\0' && !isalpha(*str2)) str2++;

        if(*str1 != *str2 || *str1 == '\0' || *str2 == '\0')
        {
            break;
        }

        str1++;
        str2++;
    }

    return *str1 - *str2;
}

int my_strcmp_reverse(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);

    const char *str1 = *(const char * const *)a;
    const char *str2 = *(const char * const *)b;

    const char *str1_end = str1;
    const char *str2_end = str2;

    while(*str1_end != '\0') str1_end++;
    while(*str2_end != '\0') str2_end++;

    while(true)
    {
        while(str1_end > str1 && !isalpha(*str1_end)) str1_end--;
        while(str2_end > str2 && !isalpha(*str2_end)) str2_end--;

        if(*str1_end != *str2_end || str1_end == str1 || str2_end == str2)
        {
            break;
        }

        str1_end--;
        str2_end--;
    }

    return *str1_end - *str2_end;
}