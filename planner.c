#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "planner.h"

#define RULES_FILE "planner_rules.txt"
#define MAX_LINE 512

typedef struct {
    int qid;
    char lesson[64];
    char message[256];
} PlannerRule;

static PlannerRule *rules = NULL;
static int rule_count = 0;

static void free_rules(void) {
    free(rules);
    rules = NULL;
    rule_count = 0;
}

static int load_rules(void) {
    FILE *f = fopen(RULES_FILE, "r");
    if (!f) return -1;

    free_rules();

    int cap = 16;
    rules = malloc(sizeof(PlannerRule) * cap);
    if (!rules) {
        fclose(f);
        return -1;
    }

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || strlen(line) < 3) continue;

        if (rule_count >= cap) {
            cap *= 2;
            PlannerRule *tmp = realloc(rules, sizeof(PlannerRule) * cap);
            if (!tmp) {
                free_rules();
                fclose(f);
                return -1;
            }
            rules = tmp;
        }

        PlannerRule *r = &rules[rule_count];
        if (sscanf(line, " %d | %63[^|] | %255[^\n]",
            &r->qid, r->lesson, r->message) == 3) {
            rule_count++;
        }
    }

    fclose(f);
    return 0;
}

static PlannerRule *find_rule(int qid) {
    for (int i = 0; i < rule_count; i++) {
        if (rules[i].qid == qid)
            return &rules[i];
    }
    return NULL;
}

void generate_plan_from_result(const QuizResult *res) {
    printf("\n=== Personalized Review Plan ===\n");

    if (load_rules() != 0) {
        printf("Planner rules file missing or invalid.\n");
        return;
    }

    if (res->score == res->total) {
        printf("Excellent! You answered all questions correctly.\n");
        printf("Suggested next steps:\n");
        printf("- Practice pointer-heavy exercises\n");
        printf("- Build a linked list or dynamic matrix\n");
        printf("- Use valgrind to hunt memory bugs\n");
        free_rules();
        return;
    }

    printf("You missed %d question(s):\n\n", res->incorrect_count);

    for (int i = 0; i < res->incorrect_count; i++) {
        int qid = res->incorrect_ids[i];
        PlannerRule *r = find_rule(qid);
        if (r) {
            printf("Q%d -> %s\n", qid, r->message);
            printf("   Review lesson: %s\n\n", r->lesson);
        } else {
            printf("Q%d → No rule defined yet.\n\n", qid);
        }
    }

    printf("Suggested 2-week plan:\n");
    printf("Week 1: Review listed lessons + redo quiz\n");
    printf("Week 2: Mini-project using dynamic memory and pointers\n");

    free_rules();
}
