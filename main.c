#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "cscan.h"
#include "scan.h"
#include "sstf.h"

List* list_rand_int;
List* list_cscan;
List* list_scan;
List* list_sstf;

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
    printf("1: %d, 2: %d\n", *item1, *item2);
    return *item1 == *item2;
}

/**
 * @brief Create a list of at least 50 random integers
 * 
 */
void initialize_random_list(){
    list_rand_int = List_create();
    if(list_rand_int == NULL){
        perror("Failed to create a list of random integers\n.");
        return;
    }

    int total = rand() % 150 + 50;

    COMPARATOR_FN pComparatorFn = &list_comparator;

    while(List_count(list_rand_int) != total){
        int num = rand() % 200;
        // printf("total: %d\nint: %d\ncount: %d\n\n", total, num, List_count(list_rand_int));
        if(List_search(list_rand_int, pComparatorFn, (rand() % 200)) == NULL){
            List_prepend(list_rand_int, &num);
        }
    }
}

int main(){
    initialize_random_list();

    Node* head = List_trim(list_rand_int);

    // sort list_rand_int and pass it to disk scheduling function
    

    return 0;
}