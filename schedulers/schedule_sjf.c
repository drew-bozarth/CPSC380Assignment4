#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpu.h"
#include "list.h"
#include "task.h"
#include "schedulers.h"

struct node * curr = NULL;
struct node * head = NULL;
struct node * previous = NULL;

void add(char * name, int priority, int burst) {
  if (head == NULL) {
    head = malloc(sizeof(struct node));

    head->task = malloc(sizeof(struct task));
    head->task->name = name;
    head->task->burst = burst;
    head->task->priority = priority;

    head->next = NULL;
    previous = head;
  } 
  else {
    curr = malloc(sizeof(struct node));
    curr->task = malloc(sizeof(struct task));
    curr->task->burst = burst;
    curr->task->name = name;
    curr->task->priority = priority;

    if (!(previous->next)) {
      if ((curr->task->burst == previous->task->burst) || (curr->task->burst > previous->task->burst)) {
        previous->next = curr;  
        curr->next = NULL;
      }
	  else {
        curr->next = previous; 	
        head = curr;
        previous = curr;
      }	   
    }
	else {  
	  while (1) {
        if ((curr ->task ->burst < previous->next->task->burst)) {
	        if (curr->task->burst > previous->task->burst) {
                curr->next = previous->next;
                previous->next = curr ;
                previous = head; 
                break;
            }
	        else if (curr->task->burst < previous->task->burst) {
                head = curr;
                curr->next = previous;
                previous = head;
                break;
	        }	  
        }
	  
        else if (curr->task->burst == previous->next->task->burst) {
            previous = previous -> next;
            if (previous->next == NULL) {
                curr->next = NULL;
            }
            else if (curr->task->burst == previous->next->task->burst) {
                previous = previous -> next ;   
                curr->next = previous->next;   
            }   
            else {
                curr->next = previous->next;	   
            }     
            previous->next = curr;  
            previous = head;		    
            break;  
        }  
        else if ((curr->task->burst) > (previous->next->task->burst)) {
            previous = previous -> next;
            if (previous->next == NULL) {
                previous->next = curr;  
                curr->next = NULL;
                previous = head;
                break;  
            }	     
        }	    
	  }	  
    }
  }
}

// invoke the scheduler
void schedule() {
 struct node *curr = head;    
    while (curr != NULL) {
        run(curr->task, curr->task->burst);  
        curr = curr->next;    
    }
}