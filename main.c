#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "cscan.h"
#include "scan.h"
#include "sstf.h"

List* list_rand_int;
List* list_sorted;
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
    // int* item1 = (int*) item;
    // int* item2 = (int*) comp;
    int item1 = *(int*) item;
    int item2 = *(int*) comp;

    // printf("val1 %d, val2 %d\t\t\n", item1, item2);
    return item1 == item2;
}

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

/**
 * @brief Create a list of at least 50 random integers
 * 
 */
void initialize_lists(){
    srand(time(NULL));

    list_rand_int = List_create();
    list_sorted = List_create();

    if(list_rand_int == NULL || list_sorted == NULL){
        perror("Failed to create a list of random integers\n.");
        return;
    }

    int total = rand() % 150 + 50;
    int rand_int[total];

    // printf("total: %d\n\n", total);

    COMPARATOR_FN pComparatorFn = &list_comparator;
    int i = 0;
    while(List_count(list_rand_int) != total){
        int num = rand() % 200;
        List_first(list_rand_int);
        if(List_search(list_rand_int, pComparatorFn, &num) == NULL){
            rand_int[i] = num;
            List_append(list_rand_int, &rand_int[i]);
            // printf("\n\ni\t\t%d\n\n", i);
            i++;
        }
        
    }
    // printf("\n\ncount: %d\n", List_count(list_rand_int));
    // printf("total: %d\n", total);

    qsort((int*)rand_int, total, sizeof(int), int_compare);
    for(int i = 0; i < total; i++){
        List_append(list_sorted, &rand_int[i]);
        // printf("%d, ", rand_int[i]);
    }


    // while(List_count(list_sorted) != 0){
    //     List_first(list_sorted);
    //     printf("%d, ", *(int*)List_remove(list_sorted));
    // }
}



void sort_random_list(){
    
}

int main(){
    initialize_lists();
    // List_first(list_rand_int);
    Node* head = List_remove(list_rand_int);    // first item in the list

    // sort list_rand_int and pass it to disk scheduling function
    

    return 0;
}