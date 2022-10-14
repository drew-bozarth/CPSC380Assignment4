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

void add(char *name, int priority, int burst) {
    //if linked list is empty
    if (head == NULL) {
        //prevents seg fault
        head = malloc(sizeof(struct node));
        prev = malloc(sizeof(struct node));

        //creating task object on the head node 
        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->priority = priority;
        head->task->burst = burst;

        //setting up next pointer to an empty node
        head->next = NULL;
        
        //this is now the first node in the linked list
        prev = head;
    } 
    //if something already occupies the linked list
    else {
        //prevents seg fault 
        curr = malloc(sizeof(struct node));    

        //updating the previous pointer to this current node
        prev->next = curr;

        //same as above, creating task object
        curr->task = malloc(sizeof(struct task));
        curr->task->name = name;
        curr->task->priority = priority;
        curr->task->burst = burst;

        //setting up next pointer to an empty node
        curr->next = NULL;    
        //increment
        prev = curr;
    }
}

void schedule() {
    struct node *curr = head;    
    while (curr != NULL) {
        run(curr->task, curr->task->burst);  
        curr = curr->next;    
    }
}






