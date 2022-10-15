#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node * head = NULL;
struct node * prev = NULL;
struct node * new = NULL;
struct node * curr = NULL;

void add(char *name, int priority, int burst) {
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
                        curr = curr -> next;
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
    curr = head;
    struct node * ref = head;	
    struct node *beginning = malloc(sizeof(struct node));
    int newburst = 0;
    while (ref !=NULL) {
        // ref->next = 3 (this is the second 3rd) 
        if (ref->next ==NULL) {
            run(ref->task, ref->task->burst);
            break;	
        }
        else {
            //	ref->task->priority = first 3
            // ref->next->task->priority = second 3
            if ((ref->task->priority != ref->next->task->priority)) {	
                run(ref->task,ref->task->burst);
                ref = ref->next; // ref = first 3
            }
            else {
                if (ref->next !=NULL) {
                // first 3 = second 3 priority
                    if ((ref->task->priority == ref->next->task->priority)) {
                        // set curr to point to ref ( location of first 3)	
                        curr = ref ;  
                        // curr->next is 3
                        while (curr->next != NULL) {
                            curr = curr->next; 	 // curr is third 3 
                            // the 3rd 3 priority != the 3rd 3 priority)
                            if (curr->task->priority != curr->next->task->priority) {	
                                beginning = curr->next; // set the beginning
                                curr->next = NULL;
                                curr = ref; // move curr back to ref so we can do round robin
                                break;
                            }
                            else {
                                //curr = curr->next;
                                // curr = 2nd 3 priority
                            }
                        }
                        while (ref !=NULL) {
                            if (ref->task->burst >= 10) {
                                newburst = ref->task->burst-10; // set newburst to 0
                                ref->task->burst = 10;
                                run(ref->task,10);
                            }
                            else if (ref-> task-> burst  < 10) {
                                newburst = 0;
                                run(ref->task,ref->task->burst);
                            }
                            while(1) {
                                if (curr->next !=NULL) { 
                                    curr = curr->next;// curr points to newT3
                                    if (curr->next == NULL) { // 
                                        if (newburst != 0) {
                                            struct node * newnode = malloc(sizeof(struct node));
                                            newnode->task = malloc(sizeof(struct task));	
                                            newnode->task->name = ref->task->name ;
                                            newnode->task->burst = newburst;
                                            newnode->task->priority = ref->task->priority;
                                            ref = ref->next ;
                                            curr->next = newnode;	
                                            newnode->next = NULL;
                                            curr = ref;

                                            break;
                                        }
                                        else if (newburst == 0) {
                                            ref = ref->next;	 // ref points to new T3
                                            curr = ref; // curr points to new T3 
                                            break;
                                        }
                                    }
                                }
                                else { // if this is the last element
                                    ref = ref->next; // ref == NULL after this
                                    curr = beginning;
                                    break;
                                }
                            }
                        }
                        ref = beginning;
                    }	
                }
            }
        }
    }
}