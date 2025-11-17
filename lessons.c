#include <stdio.h>
#include "lessons.h"

void show_lesson_intro(void) {
    printf("\n=== Pointer Basics ===\n");
    printf("- What is a pointer? A variable that stores the memory address of another variable.\n");
    printf("- Declaration: int *p;\n");
    printf("- Dereference: *p\n");
    printf("- Address-of: &x\n");
}


void show_lesson_arithmetic(void) {
    printf("\n=== Pointer Arithmetic ===\n");
    printf("- Adding/subtracting moves by sizeof(type)\n");
    printf("- p+1 moves to next element for arrays.\n");
}


void show_lesson_arrays(void) {
    printf("\n=== Pointers & Arrays ===\n");
    printf("- Array name decays to pointer to first element.\n");
    printf("- Access: a[i] == *(a + i)\n");
}


void show_lesson_functions(void) {
    printf("\n=== Pointers & Functions ===\n");
    printf("- Pass by pointer to modify caller's data.\n");
    printf("- Example: void swap(int *a, int *b) { int t=*a;*a=*b;*b=t;}\n");
}


void show_lesson_dynamic(void) {
    printf("\n=== Dynamic Memory ===\n");
    printf("- malloc, free, calloc, realloc.\n");
    printf("- Always check for NULL and free memory when done.\n");
}


void show_lesson_common(void) {
    printf("\n=== Common Pointer Bugs ===\n");
    printf("- Dangling pointers, double free, buffer overflow, uninitialized pointers.\n");
}


void show_all_lessons(void) {
    printf("\n-- Full Pointer Lessons (comprehensive) --\n");
    show_lesson_intro();
    show_lesson_arithmetic();
    show_lesson_arrays();
    show_lesson_functions();
    show_lesson_dynamic();
    show_lesson_common();
    printf("\nExercises:\n");
    printf("1) Write a function that reverses an array using pointers.\n");
    printf("2) Allocate a 2D array dynamically and free it.\n");
    printf("3) Implement your own strdup using malloc and pointers.\n");
}