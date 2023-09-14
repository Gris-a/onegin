#include <assert.h>
#include <stdio.h>

#include "qsort.h"

void qsort(int *begin, int *end)
{
    assert(begin != NULL);
    assert(end   != NULL);

    if(end > begin)
    {
        int *mid_elem = partition(begin, end);

        qsort(begin, mid_elem);
        qsort(mid_elem + 1, end);
    }
}

int *partition(int *begin, int *end)
{
    assert(begin != NULL);
    assert(end   != NULL);

    int mid_elem = *(begin + (end - begin) / 2);

    while(true)
    {
        while(*begin < mid_elem) begin++;
        while(*end   > mid_elem) end--;

        if(begin >= end)
        {
            return end;
        }

        swap(begin++, end--);
    }
}

void swap(int *ptr1, int *ptr2)
{
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    int temp = *ptr1;

    *ptr1 = *ptr2;
    *ptr2 = temp;
}