#ifndef QSORT_H
#define QSORT_H

/**
 * @file qsort.h
 * @brief my version of built-in qsort
*/

#include <stddef.h>
/**
 * @brief My qsort. Generates pivot element for any type of data and calls @b sort
 * @param ptr_on_arr_begin pointer to first element of sorting data
 * @param ptr_on_arr_end pointer to last element of sorting data
 * @param mem_size size of element of data
 * @param cmp pointer to comparator function
*/
void my_qsort(void *ptr_on_arr_begin, void *ptr_on_arr_end, const size_t mem_size, int (*cmp)(const void *, const void *));
/**
 * @brief Sorts data. Calls @b my_partition and recursively calls @b sort two times.
 * @param ptr_on_arr_begin pointer to first element of sorting data
 * @param ptr_on_arr_end pointer to last element of sorting data
 * @param temp pointer to pivot element
 * @param mem_size size of element of data
 * @param cmp pointer to comparator function
*/
void sort(void *ptr_on_arr_begin, void *ptr_on_arr_end, void *temp, const size_t mem_size, int (*cmp)(const void *, const void *));
/**
 * @brief Separates all the elements that are bigger than pivot element and others.
 * @param ptr_on_arr_begin pointer to first element of sorting data
 * @param ptr_on_arr_end pointer to last element of sorting data
 * @param temp pointer to pivot element
 * @param mem_size size of element of data
 * @param cmp pointer to comparator function
*/
void *my_partition(void *ptr_on_arr_begin, void *ptr_on_arr_end, void *temp, const size_t mem_size, int (*cmp)(const void *, const void *));
/**
 * @brief Swappin two data elements of equal size
 * @param ptr1 pointer to first element to swap
 * @param ptr2 pointer to second element to swap
 * @param mem_size size of elements
*/
void my_swap(void *ptr1, void *ptr2, size_t mem_size);

#endif //QSORT_H