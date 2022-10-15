#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head = NULL;
struct node *prev = NULL;
struct node *currNode = NULL;

void add(char *name, int priority, int burst) {
    if (head == NULL) {
        head = malloc(sizeof(struct node)) ;
        prev = malloc(sizeof(struct node)) ;

        head->task = malloc(sizeof(struct task));
        head->task->name = name;
        head->task->burst = burst;
        head->task->priority = priority;
        head->next = NULL;

        prev = head;
    }	
    else {
        currNode =  malloc(sizeof(struct node));	
        prev->next = currNode;
        currNode->task = malloc(sizeof(struct task));
        currNode->task->name = name;
        currNode->task->burst = burst;
        currNode->task->priority = priority;
        currNode->next = NULL;	
        prev = currNode;
    }
}

void schedule() {
    struct node *currNode = head;
    struct node *temp = head;
    struct node *tester = NULL;
    tester = malloc(sizeof ( struct node) );
    tester = head;
    int currburst = 0;
    int totalBurst = 0;

    while (temp != NULL) {
        if (temp->task->burst >= 10) {	
            currburst = temp->task->burst-10; 

            if (currNode!=head) {
                while(tester != currNode) {
                    tester = tester->next;
                }
                tester = head;
            }	

            totalBurst = totalBurst + 10; 

            temp->task->burst = 10;

            run(temp->task,10);	
        }
        else if (temp-> task-> burst  < 10 ) {
            currburst = 0;
 
            totalBurst = totalBurst + temp->task->burst; 

            run(temp->task,temp->task->burst);	
        }	
    
        while(1) {	
            if (currNode->next !=NULL) { 
                currNode = currNode->next; 
                if (currNode->next == NULL) { 
                    if (currburst != 0) {
                        struct node * currnode = malloc(sizeof(struct node));
                        currnode->task = malloc(sizeof(struct task));	
                        currnode->task->name = temp->task->name ;
                        currnode->task->burst = currburst;
                        currnode->task->priority = temp->task->priority;
                        temp = temp->next ; 
                        currNode->next = currnode;	
                        currnode->next = NULL; 
                        currNode = temp;     

                        break;	
                    }
                    else if (currburst == 0) {
                        temp = temp->next;	
                        currNode = temp; 
                        break;
                    }	
                }
            }
            else {
                if (currburst !=0) {
                    struct node *currNode2 = malloc(sizeof(struct node));
                    currNode2->task = malloc(sizeof(struct task));	
                    currNode2->task->name = temp->task->name ;
                    currNode2->task->priority = temp->task->priority;
                    currNode2->task->burst = currburst;
                    temp->next = currNode2;
                    temp = temp->next;
                    currNode2->next = NULL;
                    currNode = currNode2;
                }
                else {
                    temp = temp->next;
                }
                break;	
            }	
        }
    }

}