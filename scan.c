#include <stdio.h>
#include <stdlib.h>

#include "scan.h"
#include "list.h"

List* list_scan;


bool list_comparator(void* item, void* comp){
    int* item1 = (int*) item;
    int* item2 = (int*) comp;
    printf("1: %d, 2: %d\n", *item1, *item2);
    return *item1 == *item2;
}

/**
 * @brief scan through the sorted plist with scan algorithm
 * 
 * @param plist 
 * @param head 
 * @return List* 
 */
List* disk_scan(List* plist, Node* head){
    List_create(list_scan);

    if(list_scan == NULL){
        perror("Failed to create a scan_list\n");
        return LIST_FAIL;
    }

    // find the curr in plist and point

    // move the pointer to the left and take each node out of it and add it to the list_scan;
    // when no more node, move to the right
    // when list == null, return the list_scan;


    // Node* curr = head;  
    // List_search(plist, curr);

}