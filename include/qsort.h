#ifndef QSORT_H
#define QSORT_H

#include <stddef.h>

void my_qsort(void *begin, void *end, const size_t mem_size, int (*cmp)(const void *, const void *));
void *my_partition(void *ptr_on_arr_begin, void *ptr_on_arr_end, const size_t mem_size, int (*cmp)(const void *, const void *));
int my_swap(void *ptr1, void *ptr2, const size_t mem_size);

#endif //QSORT_H