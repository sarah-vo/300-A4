#include <stdio.h>
#include <stdlib.h>

#include "scan.h"
#include "list.h"
#include "fn.h"

List* list_cscan;

/**
 * @brief scan through the sorted plist with scan algorithm
 * 
 * @param plist 
 * @param head 
 * @return List* 
 */
List* disk_cscan(List* plist, Node* phead){
    
    // Create a list for scan algorithm
    list_cscan = List_create();

    if(list_cscan == NULL){
        printf("Failed to create a list_cscan\n");
        return NULL;
    }

    // Find the head in plist and point
    COMPARATOR_FN pComparatorFn = &list_comparator;

    List_first(plist);
    if(List_search(plist, pComparatorFn, phead) == NULL){
        printf("Wrong input: Cannot find the head in the list.\n");
        return NULL;
    }

    int* curr = (int*)List_curr(plist);  // curr = head
    List_append(list_cscan, List_curr(plist));   // add curr into the list_cscan
    List_prev(list_cscan);
    
    bool left_dir = true;           // bool for direction
    bool scan = true;               // scan through plist

    while(scan){
        curr = List_prev(plist);    // scanning to the left

        if(curr == NULL){   // if pointing beyond the start, set curr -> right-most element
            curr = List_last(plist);
            List_append(list_cscan, curr);
        }else{
            if(*(int*)curr == *(int*)phead){
                scan = false;
            }else{
                List_append(list_cscan, curr);
            }
        }
    }

    List_first(list_cscan);
    printf("CSCAN: \n");
    for(int i = 0; i < List_count(list_cscan); i++){
        printf("%d ", *(int*)(List_curr(list_cscan)));
        List_next(list_cscan);
    }
    printf("\n\n");
    return list_cscan;
}