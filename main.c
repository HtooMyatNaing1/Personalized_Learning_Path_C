#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "lessons.h"
#include "quiz.h"
#include "fileio.h"
#include "planner.h"

#define DATAFILE "user_results.csv"

int main(void) {
    char username[50];

    printf("Welcome to C pointers Learning Path!\n");
    printf("-----------------------------------\n");
    printf("Enter your username: ");
    if (!fgets(username, sizeof(username), stdin)) return 1;
    trim_newline(username);
    if (strlen(username)==0) strcpy(username, "guest");

    int choice = 0;
    while (1) {
        printf("\nHello, %s! Please choose an option:\n", username);
        printf("1. Learn about Pointers\n");
        printf("2. Take Quiz on Pointers\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        
        if (scanf("%d", &choice) != 1) { clear_stdin(); continue; }
        clear_stdin();

        if (choice == 1) {
            show_all_lessons();
            printf("\nFinished lessons. You should take the quiz now to get a personalized plan.\n");
        } else if (choice == 2) {
            QuizResult result = take_quiz();
            /* use the variable name 'result' consistently */
            printf("You scored %d/%d\n", result.score, result.total);
            save_user_result(DATAFILE, username, &result);
            generate_plan_from_result(&result);
        } else if (choice == 3) {
            printf("Goodbye %s... keep poking pointers!\n", username);
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
