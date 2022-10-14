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

void add(char * name, int priority, int burst) {
  if (head == NULL) {
    head = malloc(sizeof(struct node));

    head->task = malloc(sizeof(struct task));
    head->task->name = name;
    head->task->burst = burst;
    head->task->priority = priority;

    head->next = NULL;
    prev = head;
  } 
  else {
    curr = malloc(sizeof(struct node));
    curr->task = malloc(sizeof(struct task));
    curr->task->burst = burst;
    curr->task->name = name;
    curr->task->priority = priority;

    if (!(prev->next)) {
      if ((curr->task->burst == prev->task->burst) || (curr->task->burst > prev->task->burst)) {
        prev->next = curr;  
        curr->next = NULL;
      }
	  else {
        curr->next = prev; 	
        head = curr;
        prev = curr;	  
      }	   
    }
	else {  
	  while (1) {
        if ((curr ->task ->burst < prev->next->task->burst)) {
	        if (curr->task->burst > prev->task->burst) {
                curr->next = prev->next;
                prev->next = curr ;
                prev = head; 
                break;
            }
	        else if (curr->task->burst < prev->task->burst) {
                head = curr;
                curr->next = prev;
                prev = head;
                break;
	        }	  
        }
	  
        else if (curr->task->burst == prev->next->task->burst) {
            prev = prev -> next;
            if (prev->next == NULL) {
                curr->next = NULL;
            }
            else if (curr->task->burst == prev->next->task->burst) {
                prev = prev -> next ;   
                curr->next = prev->next;   
            }   
            else {
                curr->next = prev->next;	   
            }     
            prev->next = curr;  
            prev = head;		    
            break;  
        }  
        else if ((curr->task->burst) > (prev->next->task->burst)) {
            prev = prev -> next;
            if (prev->next == NULL) {
                prev->next = curr;  
                curr->next = NULL;
                prev = head;
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