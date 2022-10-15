#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node * head = NULL;
struct node * prev = NULL;
struct node * curr = NULL;
struct node * test = NULL;
int num = 0;

void add(char *name, int priority, int burst) {
    num = num + 1;
    if (head == NULL) {
        head = malloc(sizeof(struct node)) ;
        prev = malloc(sizeof(struct node)) ;

        // set the name of the task 
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;
        // set the next node to be null
        head->next = NULL;

        prev = head;
    }	
    else {
        curr =  malloc(sizeof(struct node));	
        prev->next = curr;
        curr->task = malloc(sizeof(struct task));
        curr->task->name = name;
        curr->task->burst = burst;
        curr->task->priority = priority;
        curr->next = NULL;	
        prev = curr;
    }
}

// invoke the scheduler
void schedule() {

    struct node * current = head;
    struct node * ref = head;
    struct node * monitor = NULL;
    monitor = malloc(sizeof ( struct node) );
    monitor = head;
    int currburst = 0;
    int totburst = 0;
    float turnaroundtime = 0;
    float ResponseTime = 0;
    float WaitTime = 0;
    int check = 1;

    while (ref != NULL) {
        if (ref->task->burst >= 10) {	
            currburst = ref->task->burst-10; // set currburst to 10

            if (current!=head) {
                while(monitor!=current) {
                    if (strcmp(current->task->name ,monitor->task->name) == 0) {	
                        check = 0;
                        break;
                    }
                    monitor = monitor->next;
                }
                monitor = head;
            }	

            if (ref->task->burst >10 && ref!=head) {
                if (ref->next !=NULL) {
                    if (check == 1){
                        ResponseTime = ResponseTime + totburst;
                    }
                }
            }

            if (ref->task->burst ==10 ) {

                if (check ==1){
                    ResponseTime = ResponseTime + totburst;
                }
                
            }

            totburst = totburst + 10; // totburst is 60
            if (ref->task->burst ==10) {    
                turnaroundtime = totburst +  turnaroundtime; // turnaroundtime = 60
            }

            ref->task->burst = 10;

            run(ref->task,10);	
        }
        else if (ref-> task-> burst  < 10 ) {
            currburst = 0;
            if (check ==1) {
                ResponseTime = ResponseTime + totburst;
            }
            totburst = totburst + ref->task->burst; 

            turnaroundtime = turnaroundtime + totburst ; 

            run(ref->task,ref->task->burst);	
        }	
    
        while(1) {	
            if (current->next !=NULL) { 
                current = current->next; // current = T4;
                if (current->next == NULL) { 
                    if (currburst != 0) {
                        struct node * currnode = malloc(sizeof(struct node));
                        currnode->task = malloc(sizeof(struct task));	
                        currnode->task->name = ref->task->name ;
                        currnode->task->burst = currburst;
                        currnode->task->priority = ref->task->priority;
                        ref = ref->next ; // ref points to P2
                        current->next = currnode;	// P4 points to curr Node P1
                        currnode->next = NULL; // P4 points to null
                        current = ref;     // current points to P2

                        break;	
                    }
                    else if (currburst == 0) {
                        ref = ref->next;	 // ref points to T3
                        current = ref; // current points to T3
                        break;
                    }	
                }
            }
            else { // if this is the last element
                if (currburst !=0) {
                    struct node * curr = malloc(sizeof(struct node));
                    curr->task = malloc(sizeof(struct task));	
                    curr->task->name = ref->task->name ;
                    curr->task->priority = ref->task->priority;
                    curr->task->burst = currburst;
                    ref->next = curr;
                    ref = ref->next;
                    curr->next = NULL;
                    current = curr;
                }
                else {
                    ref = ref->next;
                }
                break;	
            }	
        }
    }
    WaitTime = turnaroundtime - totburst;
    printf("The average turnaround time is : %f time units \n" , turnaroundtime/num);  	
    printf("The average response time is : %f time units \n" , ResponseTime/num);
    printf("The average Wait time is : %f time units \n" , WaitTime/num);
}