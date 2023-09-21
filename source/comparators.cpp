#include <assert.h>
#include <ctype.h>

#include "../include/comparators.h"
#include "../include/text.h"

/**
 * @file comparators.cpp
 * @brief comparators.h functions
*/

int my_line_cmp(const void *line1, const void *line2)
{
    assert(line1 != NULL);
    assert(line2 != NULL);

    struct Line str1 = *(const struct Line *)line1;
    struct Line str2 = *(const struct Line *)line2;

    while(str1.line_begin != str1.line_end && !isalpha(*str1.line_begin)) str1.line_begin++;
    while(str2.line_begin != str2.line_end && !isalpha(*str2.line_begin)) str2.line_begin++;

    while(tolower(*str1.line_begin) == tolower(*str2.line_begin) && str1.line_begin != str1.line_end &&
                                                                    str2.line_begin != str2.line_end)
    {
        str1.line_begin++;
        str2.line_begin++;
    }

    return tolower(*str1.line_begin) - tolower(*str2.line_begin);
}

int my_line_cmp_reverse(const void *line1, const void *line2)
{
    assert(line1 != NULL);
    assert(line2 != NULL);

    struct Line str1 = *(const struct Line *)line1;
    struct Line str2 = *(const struct Line *)line2;

    while(str1.line_end != str1.line_begin && !isalpha(*str1.line_end)) str1.line_end--;
    while(str2.line_end != str2.line_begin && !isalpha(*str2.line_end)) str2.line_end--;

    while(tolower(*str1.line_end) == tolower(*str2.line_end) && str1.line_end != str1.line_begin &&
                                                                str2.line_end != str2.line_begin)
    {
        str1.line_end--;
        str2.line_end--;
    }

    return tolower(*str1.line_end) - tolower(*str2.line_end);
}