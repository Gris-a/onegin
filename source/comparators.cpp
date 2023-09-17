#include <assert.h>
#include <ctype.h>

#include "../include/comparators.h"
#include "../include/text.h"

int my_strcmp(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);

    struct Line str1 = *(const Line *)a;
    struct Line str2 = *(const Line *)b;

    assert(str1.line != NULL);
    assert(str2.line != NULL);

    while(true)
    {
        while(str1.len > 0 && !isalpha(*str1.line)) {str1.line++; str1.len--;}
        while(str2.len > 0 && !isalpha(*str2.line)) {str2.line++; str2.len--;}

        if(tolower(*str1.line) != tolower(*str2.line) || str1.len == 0 || str2.len == 0)
        {
            break;
        }

        str1.line++;
        str1.len--;

        str2.line++;
        str2.len--;
    }

    return tolower(*str1.line) - tolower(*str2.line);
}

int my_strcmp_reverse(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);

    struct Line str1 = *(const Line *)a;
    struct Line str2 = *(const Line *)b;

    assert(str1.line != NULL);
    assert(str2.line != NULL);

    while(true)
    {
        while(str1.len > 0 && !isalpha(str1.line[str1.len])) str1.len--;
        while(str2.len > 0 && !isalpha(str2.line[str2.len])) str2.len--;

        if(tolower(str1.line[str1.len]) != tolower(str2.line[str2.len]) || str1.len == 0 || str2.len == 0)
        {
            break;
        }

        str1.len--;
        str2.len--;
    }

    return tolower(str1.line[str1.len]) - tolower(str2.line[str2.len]);
}

int base_text_cmp(const void *a, const void *b)
{
    assert(a != NULL);
    assert(b != NULL);

    size_t l_num1 = ((const Line *)a)->l_num;
    size_t l_num2 = ((const Line *)b)->l_num;

    if(l_num1 == l_num2) return 0;
    return l_num1 > l_num2 ? 1 : -1;
}