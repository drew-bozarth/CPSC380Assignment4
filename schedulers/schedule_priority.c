#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "task.h"
#include "schedulers.h"

struct node *head = NULL;
struct node *curr = NULL;
struct node *newNode = NULL;
struct node *endNode = NULL;

void add(char *name, int priority, int burst) {
	
    if (head == NULL) {
        head = malloc(sizeof(struct node));

        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;

        head->next = NULL;
        curr = head;
    } else {
        newNode = malloc(sizeof(struct node));

        newNode->task = malloc(sizeof(struct task));
        newNode->task->burst = burst;
        newNode->task->name = name;
        newNode->task->priority = priority;

        if (!(curr->next)) {
            if ((newNode->task->priority == curr->task->priority) || (newNode->task->priority < curr -> task -> priority)) {
                curr->next = newNode; 
                newNode->next = NULL;
            }
            else {
                newNode->next = curr; 	
                head = newNode;
                curr = newNode;	  
            }	   
        }
    
        else {
            while(1) {
                if ((newNode->task->priority > curr->next->task->priority) ) {
                    if (newNode->task->priority < curr->task->priority) {
                        newNode->next = curr->next;
                        curr->next = newNode ;
                        curr = head; 
                        break;
                    }
                    else if (newNode->task->priority == curr->task->priority) {
                        newNode->next = curr->next;
                        curr->next = newNode;	
                        break;		
                    }
                    else if (newNode->task->priority > curr->task->priority) {
                        head = newNode;
                        newNode->next = curr;
                        curr = head;
                        break;
                    }
                }
                else if (newNode->task->priority < curr->next->task->priority) {
                    curr = curr -> next;
        
                    if (curr->next == NULL) {
                        curr->next = newNode;  
                        newNode->next = NULL;
                        curr = head;
                        break;
                    }	  
                }
                else if (newNode->task->priority == curr->next->task->priority) {
                    curr = curr->next;
                    if (newNode->task->priority == curr->next->task->priority) {
                        curr = curr -> next ;   
                        newNode->next = curr->next;
                    }
                    else if (curr->next == NULL) {
                        newNode->next = NULL; 
                    }   
                    else {
                        newNode->next = curr->next;
                    }
                    curr->next = newNode;
                    curr = head;		    
                    break;
                }
            }
        }
    }
}

void schedule() {
    struct node *curr = head;    
    while (curr != NULL) {
        run(curr->task, curr->task->burst);  
        curr = curr->next;    
    }
}