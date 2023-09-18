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

    if(end > begin)
    {
        void *mid_elem = my_partition(begin, end, mem_size, cmp);

        my_qsort(begin, mid_elem, mem_size, cmp);
        my_qsort((char *)mid_elem + mem_size, end, mem_size, cmp);
    }
}

void *my_partition(void *ptr_on_arr_begin, void *ptr_on_arr_end, const size_t mem_size, int (*cmp)(const void *, const void *))
{
    assert(ptr_on_arr_begin != NULL);
    assert(ptr_on_arr_end   != NULL);

    char *begin = (char *)ptr_on_arr_begin;
    char *end   = (char *)ptr_on_arr_end;

    void *mid_elem = calloc(1, mem_size);
    if(mid_elem == NULL)
    {
        perror(__func__);

        return NULL;
    }

    memcpy(mid_elem, begin, mem_size);

    while(true)
    {
        while(cmp(begin, mid_elem) < 0) begin += mem_size;
        while(cmp(end  , mid_elem) > 0) end   -= mem_size;

        if(begin >= end)
        {
            free(mid_elem);

            return end;
        }

        if(my_swap(begin, end, mem_size))
        {
            return NULL;
        }

        begin += mem_size;
        end   -= mem_size;
    }
}

int my_swap(void *ptr1, void *ptr2, const size_t mem_size)
{
    assert(ptr1 != NULL);
    assert(ptr2 != NULL);

    void *temp = calloc(1, mem_size);
    if(temp == NULL)
    {
        perror(__func__);

        return ENOMEM;
    }

    memcpy(temp, ptr1, mem_size);
    memcpy(ptr1, ptr2, mem_size);
    memcpy(ptr2, temp, mem_size);

    free(temp);

    return EXIT_SUCCESS;
}