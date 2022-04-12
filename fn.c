#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief comparator function that compares two integer pointers
 * 
 * @param item 
 * @param comp 
 * @return true 
 * @return false 
 */
bool list_comparator(void* item, void* comp){
    int* item1 = (int*) item;
    int* item2 = (int*) comp;

    return *item1 == *item2;
}

/**
 * @brief compare two integers (for qsort)
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int int_compare(const void *a, const void *b){
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    // return -1 if a < b, otherwise 1
    if(int_a < int_b){
        return -1;
    }else{
        return 1;
    }
}