#include <stdio.h>
#include "planner.h"

void generate_plan_from_result(const QuizResult *res) {
    printf("\n=== Personalized Review Plan ===\n");
    if (res->score == res->total) {
        printf("Excellent! You answered all questions correctly. Suggest: practice exercises and projects.\n");
        printf("Suggested exercises: Implement linked list using pointers; build dynamic 2D grid; write custom memory allocator (toy).\n");
        return;
    }
    printf("You missed %d question(s). Review these lessons:\n", res->incorrect_count);
    for (int i=0;i<res->incorrect_count;i++) {
        int qid = res->incorrect_ids[i];
        switch(qid) {
            case 1: printf("- Q1: Address-of operator — review Pointer Basics (declaration & & operator).\n"); break;
            case 2: printf("- Q2: Dereference — review Pointer Basics and Dereferencing.\n"); break;
            case 3: printf("- Q3: Pointers & Arrays — review arrays and pointer arithmetic.\n"); break;
            case 4: printf("- Q4: Dynamic Memory — review malloc/free/calloc/realloc.\n"); break;
            case 5: printf("- Q5: Pointer Bugs — review double free/dangling pointers.\n"); break;
            case 6: printf("- Q6: Pointers & Functions — review passing by pointer and side effects.\n"); break;
            default: printf("- Unknown question id %d\n", qid);
        }
    }
    printf("\nPlan (2-week sample):\n");
    printf("Week 1: Re-learn targeted lessons, do 3 small exercises (reverse array, swap via pointers, simple dynamic 2D).\n");
    printf("Week 2: Build a small project: linked list + unit tests; review memory errors with valgrind.\n");
}