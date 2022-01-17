#include <stdio.h>
#include <stdlib.h>

typedef struct task {
    int priority_rank;
    char task_name[100];
    char task_desc[1000];
    char assigned_to[100];
    char date[6];
} TASK;

TASK * readTask() {
    TASK *new;
    new = (TASK *)malloc(sizeof(TASK));
    int priority;

    printf("Enter Task Name: \n");
    scanf("%s", new->task_name);
    printf("\n");

    printf("Enter Task Description: \n");
    scanf("%s", new->task_desc);
    printf("\n");

    printf("Assigned to: \n");
    scanf("%s", new->assigned_to);
    printf("\n");

    printf("Date of Assignment: \n");
    scanf("%d", &new->date);
    printf("\n");

    printf("Enter Task Priority [(min) 1 to (max) 99]: \n");
    scanf("%d", &priority);
    new->priority_rank = 100 - priority;
    printf("\n");

    return new;
}

void displayTask(TASK * task) {
    printf("\n\n\n");
    printf("---------- TASK ----------\n");
    printf("> Task Name\t: %s\n", task->task_name);
    printf("> Task Description: %s\n", task->task_desc);
    printf("> Assined to\t: %s\n", task->assigned_to);
    printf("> Assigned on\t: %c%c-%c%c-%c%c\n", task->date[0], task->date[1], task->date[2], task->date[4], task->date[5], task->date[6]);
    printf("> Priority Rank: %d\n", task->priority_rank);
}

// void main() {
//     TASK * node;

//     node = readTask();

//     displayTask(node);
// }