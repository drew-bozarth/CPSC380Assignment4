#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "task.h"
#include "schedulers.h"

struct node *curr = NULL;
struct node *head = NULL;
struct node *prev = NULL;
struct node *new = NULL;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node));
        //standard code to assign a task to a linked list node
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;
        head -> next = NULL;

        curr = head;
    } 
    else {
        new = malloc(sizeof(struct node));

        new->task = malloc(sizeof(struct task));
        new->task->burst = burst;
        new->task->name = name;
        new->task->priority = priority;
        if (!(curr -> next)) {
            if ((new->task->priority == curr->task->priority) || (new->task->priority < curr->task->priority)) {
                curr->next = new; 
                new->next = NULL;
            }
            else {
                new->next = curr; 	
                curr = new;	  
                head = new;
            }	   
        }
        else {
            while(1) {
                if ((new->task->priority > curr->next->task->priority)) {
                    if (new->task->priority < curr->task->priority) {
                        new->next = curr->next;
                        curr->next = new;
                        curr = head; 
                        break;
                    }
                    else if (new->task->priority == curr->task->priority) {
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
                else if ((new->task->priority) < (curr->next->task->priority)) {
                    curr = curr -> next;
                    if (curr->next == NULL) {
                        curr->next = new;  
                        new->next = NULL;
                        curr = head;
                        break;
                    }
                } 
                else if (new->task->priority == curr->next->task->priority) {
                    curr = curr -> next ;
                    if (new->task->priority == curr->next->task->priority) {
                        curr = curr -> next ;   
                        new->next = curr->next;
                    }
                    else if (curr->next == NULL) {
                        new->next = NULL; 
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
    struct node *point = head;	
    struct node *lead = malloc(sizeof(struct node));
    int tempBurst = 0;
    while (point !=NULL) {
        if (point->next == NULL) {
            run(point->task, point->task->burst);
            break;	
        }
        else {
            if ((point->task->priority != point->next->task->priority)) {	
                run(point->task,point->task->burst);
                point = point->next; 
            }
            else {
                if (point->next !=NULL) {
                    if ((point->task->priority == point->next->task->priority)) {
                        curr = point;  
                        while (curr->next != NULL) {
                            curr = curr->next; 	 
                            if (curr->task->priority != curr->next->task->priority) {	
                                lead = curr->next; 
                                curr->next = NULL;
                                curr = point; 
                                break;
                            }
                            else {
                                
                            }
                        }
                        while (point != NULL) {
                            if (point->task->burst >= 10) {
                                tempBurst = point->task->burst-10; 
                                point->task->burst = 10;
                                run(point->task,10);
                            }
                            else if (point-> task-> burst  < 10) {
                                tempBurst = 0;
                                run(point->task,point->task->burst);
                            }
                            while(1) {
                                if (curr->next !=NULL) { 
                                    curr = curr->next;
                                    if (curr->next == NULL) { 
                                        if (tempBurst != 0) {
                                            struct node *temp = malloc(sizeof(struct node));
                                            temp->task = malloc(sizeof(struct task));	
                                            temp->task->name = point->task->name ;
                                            temp->task->burst = tempBurst;
                                            temp->task->priority = point->task->priority;
                                            point = point->next ;
                                            curr->next = temp;	
                                            temp->next = NULL;
                                            curr = point;
                                            break;
                                        }
                                        else if (tempBurst == 0) {
                                            point = point->next;	
                                            curr = point; 
                                            break;
                                        }
                                    }
                                }
                                else { 
                                    point = point->next; 
                                    curr = lead;
                                    break;
                                }
                            }
                        }
                        point = lead;
                    }	
                }
            }
        }
    }
}