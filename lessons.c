#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lessons.h"

#define LESSONS_DIR "lessons"
#define MAX_PATH 512

void show_lesson(const char *name) {
    char path[MAX_PATH];
    int n = snprintf(path, sizeof(path), "%s/%s.txt", LESSONS_DIR, name);
    if (n <= 0 || n >= (int)sizeof(path)) {
        fprintf(stderr, "Lesson path too long\n");
        return;
    }

    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "Lesson file not found: %s\n", path);
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        fputs(line, stdout);
    }
    fclose(f);
}

void show_lesson_intro(void)       { printf("\n=== Pointer Basics ===\n"); show_lesson("intro"); }
void show_lesson_arithmetic(void)  { printf("\n=== Pointer Arithmetic ===\n"); show_lesson("arithmetic"); }
void show_lesson_arrays(void)      { printf("\n=== Pointers & Arrays ===\n"); show_lesson("arrays"); }
void show_lesson_functions(void)   { printf("\n=== Pointers & Functions ===\n"); show_lesson("functions"); }
void show_lesson_dynamic(void)     { printf("\n=== Dynamic Memory ===\n"); show_lesson("dynamic"); }
void show_lesson_common(void)      { printf("\n=== Common Pointer Bugs ===\n"); show_lesson("common"); }

void show_all_lessons(void) {
    printf("\n-- Full Pointer Lessons (comprehensive) --\n");
    show_lesson_intro();
    show_lesson_arithmetic();
    show_lesson_arrays();
    show_lesson_functions();
    show_lesson_dynamic();
    show_lesson_common();
    printf("\nExercises:\n");
    show_lesson("exercises"); 
}
