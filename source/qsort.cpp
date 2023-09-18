#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/qsort.h"

void my_qsort(void *begin, void *end, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(begin != NULL);
    assert(end   != NULL);
    assert(cmp   != NULL);

    void *temp = calloc(1, mem_size);
    if(temp == NULL)
    {
        perror(__func__);

        return;
    }

    sort(begin, end, temp, mem_size, cmp);
    free(temp);
}

void sort(void *begin, void *end, void *temp, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(begin != NULL);
    assert(end   != NULL);
    assert(temp  != NULL);
    assert(cmp   != NULL);

    if(end > begin)
    {
        void *mid = my_partition(begin, end, temp, mem_size, cmp);

        sort(begin, mid, temp, mem_size, cmp);
        sort((char *)mid + mem_size, end, temp, mem_size, cmp);
    }
}

void *my_partition(void *ptr_on_arr_begin, void *ptr_on_arr_end, void *temp, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(ptr_on_arr_begin != NULL);
    assert(ptr_on_arr_end   != NULL);
    assert(cmp              != NULL);

    char *begin = (char *)ptr_on_arr_begin;
    char *end   = (char *)ptr_on_arr_end;

    memcpy(temp, begin, mem_size);

    while(true)
    {
        while(cmp(begin, temp) < 0) begin += mem_size;
        while(cmp(end  , temp) > 0) end   -= mem_size;

        if(begin >= end)
        {
            return end;
        }

        my_swap(begin, end, mem_size);

        begin += mem_size;
        end   -= mem_size;
    }
}

void my_swap(void *ptr_on_elem1, void *ptr_on_elem2, const size_t mem_size) //TODO faster
{
    assert(ptr_on_elem1 != NULL);
    assert(ptr_on_elem2 != NULL);

    char *ptr1 = (char *)ptr_on_elem1;
    char *ptr2 = (char *)ptr_on_elem2;

    for(size_t i = 0; i < mem_size; i++)
    {
        char temp = *ptr1 + *ptr2;
        *ptr2 = *ptr1;
        *ptr1 = temp - *ptr2;

        ptr1++;
        ptr2++;
    }
}