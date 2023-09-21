#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/qsort.h"

/**
 * @file qsort.cpp
 * @brief qsort.h functions
*/

void my_qsort(void *ptr_on_arr_begin, void *ptr_on_arr_end, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(ptr_on_arr_begin != NULL);
    assert(ptr_on_arr_end   != NULL);
    assert(cmp              != NULL);

    void *temp = calloc(1, mem_size);
    if(temp == NULL)
    {
        perror(__func__);

        return;
    }

    sort(ptr_on_arr_begin, ptr_on_arr_end, temp, mem_size, cmp);
    free(temp);
}

void sort(void *ptr_on_arr_begin, void *ptr_on_arr_end, void *temp, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(ptr_on_arr_begin != NULL);
    assert(ptr_on_arr_end   != NULL);
    assert(temp             != NULL);
    assert(cmp              != NULL);

    if(ptr_on_arr_end > ptr_on_arr_begin)
    {
        void *mid = my_partition(ptr_on_arr_begin, ptr_on_arr_end, temp, mem_size, cmp);

        sort(ptr_on_arr_begin, mid, temp, mem_size, cmp);
        sort((char *)mid + mem_size, ptr_on_arr_end, temp, mem_size, cmp);
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

void my_swap(void *ptr_on_elem1, void *ptr_on_elem2, size_t mem_size)
{
    assert(ptr_on_elem1 != NULL);
    assert(ptr_on_elem2 != NULL);

    long long *ptr1 = (long long *)ptr_on_elem1;
    long long *ptr2 = (long long *)ptr_on_elem2;

    size_t n_chunks = mem_size / 8;

    for(size_t i = 0; i < n_chunks; i++)
    {
        *ptr1 = *ptr1 ^ *ptr2;
        *ptr2 = *ptr1 ^ *ptr2;
        *ptr1 = *ptr1 ^ *ptr2;

        ptr1++;
        ptr2++;
        mem_size -= 8;
    }

    char *ptr12 = (char *)ptr1;
    char *ptr22 = (char *)ptr2;

    for(size_t i = 0; i < mem_size; i++)
    {
        *ptr12 = *ptr12 ^ *ptr22;
        *ptr22 = *ptr12 ^ *ptr22;
        *ptr12 = *ptr12 ^ *ptr22;

        ptr12++;
        ptr22++;
    }
}