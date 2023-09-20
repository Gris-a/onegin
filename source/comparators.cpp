#include <assert.h>
#include <ctype.h>

#include "../include/comparators.h"
#include "../include/text.h"

int my_strcmp(const void *elem1, const void *elem2)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    struct Line str1 = *(const Line *)elem1;
    struct Line str2 = *(const Line *)elem2;

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

int my_strcmp_reverse(const void *elem1, const void *elem2)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    struct Line str1 = *(const Line *)elem1;
    struct Line str2 = *(const struct Line *)elem2;

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

int base_text_cmp(const void *elem1, const void *elem2)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    size_t l_num1 = ((const Line *)elem1)->l_num;
    size_t l_num2 = ((const Line *)elem2)->l_num;

    if(l_num1 == l_num2) return 0;
    return l_num1 > l_num2 ? 1 : -1;
}

int length_cmp(const void *elem1, const void *elem2)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    size_t len1 = ((const Line *)elem1)->len;
    size_t len2 = ((const Line *)elem2)->len;

    if(len1 == len2) return my_strcmp(elem1, elem2);
    return len1 > len2 ? 1 : -1;
}

int length_cmp_reverse(const void *elem1, const void *elem2)
{
    assert(elem1 != NULL);
    assert(elem2 != NULL);

    size_t len1 = ((const Line *)elem1)->len;
    size_t len2 = ((const Line *)elem2)->len;

    if(len1 == len2) return my_strcmp(elem1, elem2);
    return len1 < len2 ? 1 : -1;
}