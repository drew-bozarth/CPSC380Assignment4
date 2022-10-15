#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node * head = NULL;
struct node * curr = NULL;
struct node * new = NULL;
struct node * final = NULL;

void add(char * name, int priority, int burst) {
	
    if (head == NULL) {
        head = malloc(sizeof(struct node));

        // set the name of the task 
        head -> task = malloc(sizeof(struct task));
        head -> task -> name = name;
        head -> task -> burst = burst;
        head -> task -> priority = priority;
        // set the next node to be null
        head -> next = NULL;

        curr = head;
    } else {
        new = malloc(sizeof(struct node));

        new -> task = malloc(sizeof(struct task));
        new -> task -> burst = burst;
        new -> task -> name = name;
        new -> task -> priority = priority;
        // if curr->next is NULL
        if (!(curr -> next)) {
            if (((new -> task -> priority) < (curr -> task -> priority)) || ((new -> task -> priority) ==(curr -> task -> priority))) {
                curr -> next = new; // head points to second node 
                new -> next = NULL;
            }
            // if the second node burst is smaller than the curr burst  
            else {
            // set new to point to head which is in the second position
            new->next = curr; 	
            // head now holds the address of new which is in the first position
            head = new;
            // reset curr to new
            curr = new;	  
            // we still have the second node connected to null  
            }	   
        }
    
        // T3 and on execute from here I think 
        else {
            while(1) {
                if ((new -> task -> priority > curr -> next -> task -> priority) ) {
        
                    if (new->task->priority < curr->task->priority) {
                        new->next = curr->next;
                        curr->next = new ;
                        curr = head; 
                        break;
                    }
                    // if the new priority == the curr priority
                    else if(new->task->priority == curr->task->priority) {
                        new->next = curr->next;
                        curr->next = new;	
                        break;		
                    }
                    else if (new->task->priority > curr->task->priority) {

                        head = new;
                        new->next = curr;
                        curr = head;
                        break;
                    }
                }
                // if the new priority is less than the curr priority
                else if ((new -> task -> priority) <(curr -> next -> task -> priority)) {
                    curr = curr -> next;
        
                    if ( curr->next == NULL) {
                        //printf("testing"); 
                        curr->next = new;  
                        new->next = NULL;
                        curr = head;
                        break;
                    }	  
                }
                else if (new -> task -> priority == curr -> next -> task -> priority) {
                    curr = curr -> next ;
                    if (curr->next == NULL) {
                        new->next = NULL;
                    }
                    else if (new-> task-> priority == curr->next->task->priority) {
                        curr = curr -> next ;   
                        new->next = curr->next;   
                    }   
                    else {
                        new->next = curr->next;
                    }
                    curr->next = new;
                    curr = head;		    
                    break;
                }
            }
        }
    }
}

// invoke the scheduler
void schedule() {
    int num = 0;
    float ResponseTime = 0;
    float turnaroundtime = 0;
    float WaitTime = 0;
    int burst = 0;

    struct node * ref = head;
    while (ref != NULL) {
        num = num + 1;
        run(ref -> task, ref -> task -> burst);
        burst = burst + ref->task->burst;
        turnaroundtime = turnaroundtime + burst ; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)
        if (ref->next !=NULL) {
            ResponseTime = ResponseTime + burst;
        }
        ref = ref -> next;
    }
    WaitTime = turnaroundtime - burst;
    printf("The average turnaround time is : %f time units \n" , (float)turnaroundtime/num);    
    printf("The average ResponseTime is : %f time units \n" , (float)ResponseTime/num);
    printf("The average WaitTime is : %f time units\n " , (float)WaitTime/num);
}