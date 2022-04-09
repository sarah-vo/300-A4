#include <stdio.h>
#include <stdlib.h>

#include "scan.h"
#include "list.h"
#include "fn.h"

List* list_scan;

/**
 * @brief scan through the sorted plist with scan algorithm
 * 
 * @param plist 
 * @param head 
 * @return List* 
 */
List* disk_scan(List* plist, Node* phead){
    
    // Create a list for scan algorithm
    list_scan = List_create();

    if(list_scan == NULL){
        printf("Failed to create a list_scan\n");
        return NULL;
    }

    // Find the head in plist and point
    COMPARATOR_FN pComparatorFn = &list_comparator;

    List_first(plist);
    if(List_search(plist, pComparatorFn, phead) == NULL){
        printf("Wrong input: Cannot find the head in the list.\n");
        return NULL;
    }

    printf("head: %d\n\n", *(int*)phead);


    int* curr = (int*)List_curr(plist);  // curr = head
    List_append(list_scan, List_curr(plist));   // add curr into the list_scan
    
    bool left_dir = true;           // bool for direction
    bool scan = true;               // scan through plist
    
    while(scan){
        if(curr == NULL){   // either left-most or right-most
            if(left_dir){   // past the head (i.e. reached 0). Change the direction and find the phead
                left_dir = false;   // scaning to the right
                List_search(plist, pComparatorFn, phead); // its curr will be pointing at phead
                curr = List_next(plist);   // move the pointer to the right by 1
            }else{
                scan = false;
            }
        }else{
            if(left_dir){
                curr = (int*)List_prev(plist);
            }else{
                curr = (int*)List_next(plist);
            }
        }

        if(curr != NULL){
            List_append(list_scan, curr);
        }
    }

    // printf("scan size: %d\n", List_count(list_scan));
    List_first(list_scan);
    printf("Scan: \n");
    for(int i = 0; i < List_count(list_scan); i++){
        printf("%d ", *(int*)(List_curr(list_scan)));
        List_next(list_scan);
    }
    printf("\n\n");
    return list_scan;
}