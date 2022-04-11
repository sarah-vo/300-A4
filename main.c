#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "list.h"
#include "cscan.h"
#include "scan.h"
#include "fn.h"

List* list_fcfs;
List* list_sorted;
List* list_cscan;
List* list_scan;

// Node* head;
int* rand_int;
int* sorted;

//search comparator
COMPARATOR_FN pComparatorFn = &list_comparator;




/**
 * @brief Create a list of at least 50 random integers
 * 
 */
void initialize_lists(){
    srand(time(NULL));

    list_fcfs = List_create();
    list_sorted = List_create();
    

    if(list_fcfs == NULL || list_sorted == NULL){
        perror("Failed to create list_fcfs/list_sorted\n.");
        return;
    }

    int total = rand() % 150 + 50;
    // int total = rand() % 10 + 1;
    // int total = 5;
    rand_int = (int*)malloc(total*sizeof(int));
    sorted = (int*)malloc(total*sizeof(int));

    // printf("total: %d\n\n", total);

    int i = 0;
    // printf("\nfcfs: \n");
    while(List_count(list_fcfs) != total){
        int num = rand() % 200;
        List_first(list_fcfs);
        if(List_search(list_fcfs, pComparatorFn, &num) == NULL){
            *(rand_int+i) = num;
            *(sorted+i) = num;
            List_append(list_fcfs, rand_int+i);
            // printf("%d ", *(rand_int + i));
            i++;
        }
        
    }
    rand_int = rand_int;

    qsort(sorted, total, sizeof(int), int_compare);
    for(int i = 0; i < total; i++){
        List_append(list_sorted, sorted+i);
        // printf("%d ", *(rand_int+i));
    }
    // printf("\n\n%d\n", List_count(list_sorted));

    List_first(list_sorted);
    List_first(list_fcfs);
    
    printf("\nfcfs: \n");
    for(int i = 0; i < total; i++){
        printf("%d ", *(int*)List_curr(list_fcfs));
        List_next(list_fcfs);
    }

    printf("\n\nsorted: \n");
    for(int i = 0; i < total; i++){
        printf("%d ", *(int*)List_curr(list_sorted));
        List_next(list_sorted);
    }
    printf("\n\n");
}



void list_item_free(void* pItem){
    pItem = NULL;
}

int totalTrack(List* list){
    int returnValue = 0;
    List_first(list);
    while(List_next(list) != NULL){
        List_prev(list);
        int track = *(int*)List_curr(list) - *(int*) List_next(list);
        returnValue += abs(track);
    }
    return returnValue;
}

int longestDelayLoop(List* list, int next_fcfs){
    int delay = 0;
    int origValue = *(int*)List_curr(list);
    while(true){
        if(*(int*)List_curr(list) == next_fcfs){
            break;
        }
        delay++;
        if(List_curr(list) == NULL || List_next(list) == NULL){
            List_first(list);
        }
        else{
            List_prev(list);
        }
        if(*(int*)List_next(list) == next_fcfs){
            break;
        }

    }
    return delay;
}

int delayList(List *list, int currNum) {
    int delay = 0;
    while(true){
        if(*(int*)List_curr(list) == currNum){
            if(delay != 0){
                delay--;
                }
            List_first(list);
            break;
        }
        else{
            List_next(list);
            delay++;
        }
    }
    return delay;
}

int delay_fcfs(List *list, int currNum) {
    List_first(list);
    int delay = 0;
    while(true){
        if(*(int*)List_curr(list) == currNum){
            if(delay != 0){
                delay--;
            }
            break;
        }
        else{
            delay++;
            List_next(list);
        }
    }
    return delay;
}

int longestDelay(List* list){
    int largestDelay = 0;
    List_first(list);
    List_first(list_fcfs);
    while(List_curr(list_fcfs) != NULL){
        int currNum = *(int*)List_curr(list_fcfs);
        int delayAlgo = delayList(list, currNum);
        int delayFCFS = delay_fcfs(list_fcfs, currNum);
        int delayDifference = delayAlgo - delayFCFS;
        if(delayDifference >= largestDelay){
            largestDelay = delayDifference;
        }
        List_next(list_fcfs);
    }
    return largestDelay;
}

float averageDelay(List* list){
    List_first(list);
    List_first(list_fcfs);
    float delayCount = 0;
    float totalDelay = 0;
    while(List_curr(list_fcfs) != NULL){

        int currNum = *(int*)List_curr(list_fcfs);
        int delayAlgo = delayList(list, currNum);
        int delayFCFS = delay_fcfs(list_fcfs, currNum);
        int delayDifference = delayAlgo - delayFCFS;
        if(delayDifference > 0){
            totalDelay += delayDifference;
            delayCount++;
        }
        List_next(list_fcfs);
    }
    float averageDelay = totalDelay/delayCount;
    return averageDelay;
}

int main(){
    initialize_lists();
    Node* head = List_first(list_fcfs);    // first item in the list = head
    // printf("\nhead: %p\n", List_first(list_fcfs));
    // printf("\nhead: %p\n", head);
    // printf("\nhead: %d\n", *(int*)head);

    // sort list_fcfs and pass it to disk scheduling function
    list_scan = disk_scan(list_sorted, head);
    list_cscan = disk_cscan(list_sorted, head);

    printf("Total number of tracks traversed for each algorithm:\n");
    printf("  - FCFS: %d tracks traversed.\n", totalTrack(list_fcfs));
    printf("  - SCAN: %d tracks traversed.\n", totalTrack(list_scan));
    printf("  - CSCAN: %d tracks traversed.\n", totalTrack(list_cscan));

    printf("Longest track delay for each algorithm compared to FCFS:\n");
    printf("  - SCAN: %d\n", longestDelay(list_scan));
    printf("  - CSCAN: %d\n", longestDelay(list_cscan));

    printf("Average track delay for each algorithm compared to FCFS:\n");
    printf("  - SCAN: %.1f\n", averageDelay(list_scan));
    printf("  - CSCAN: %.1f\n", averageDelay(list_cscan));
    
     List_free(list_fcfs, &list_item_free);
     List_free(list_sorted, &list_item_free);
     List_free(list_scan, &list_item_free);
     List_free(list_cscan, &list_item_free);

    return 0;
}