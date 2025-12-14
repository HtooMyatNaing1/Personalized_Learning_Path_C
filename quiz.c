#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "quiz.h"

#define DEFAULT_QFILE "questions.txt"
#define DEFAULT_AFILE "answers.txt"
#define INITIAL_CAP 32
#define MAX_LINE 1024
#define QUIZ_QUESTIONS_PER_RUN 5

static char **g_questions = NULL;
static char *g_answers = NULL;
static int g_qcount = 0;

static void free_quiz_data(void) {
    if (g_questions) {
        for (int i = 0; i < g_qcount; ++i) free(g_questions[i]);
        free(g_questions);
        g_questions = NULL;
    }
    if (g_answers) {
        free(g_answers);
        g_answers = NULL;
    }
    g_qcount = 0;
}

static char *strdup_safe(const char *s) {
    if (!s) return NULL;
    size_t n = strlen(s) + 1;
    char *d = malloc(n);
    if (d) memcpy(d, s, n);
    return d;
}

static void trim_trailing_newline(char *s) {
    if (!s) return;
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[n-1] = '\0';
        --n;
    }
}

static int load_lines(const char *filename, char ***out_lines) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    int cap = INITIAL_CAP;
    int count = 0;
    char **lines = malloc(sizeof(char*) * cap);
    if (!lines) { fclose(f); return -1; }

    char buf[MAX_LINE];
    while (fgets(buf, sizeof(buf), f)) {
        trim_trailing_newline(buf);

        int allspace = 1;
        for (size_t i = 0; buf[i]; ++i) if (!isspace((unsigned char)buf[i])) { allspace = 0; break; }
        if (allspace) continue;

        if (count >= cap) {
            int ncap = cap * 2;
            char **tmp = realloc(lines, sizeof(char*) * ncap);
            if (!tmp) {
                for (int i = 0; i < count; ++i) free(lines[i]);
                free(lines);
                fclose(f);
                return -1;
            }
            lines = tmp;
            cap = ncap;
        }
        lines[count++] = strdup_safe(buf);
        if (!lines[count-1]) {
            for (int i = 0; i < count-1; ++i) free(lines[i]);
            free(lines);
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    *out_lines = lines;
    return count;
}

static int load_quiz_files(const char *qfile, const char *afile) {
    free_quiz_data();

    char **q_lines = NULL;
    int qn = load_lines(qfile, &q_lines);
    if (qn <= 0) {
        if (qn == 0) { 
            free(q_lines);
        }
        return -1;
    }

    char **a_lines = NULL;
    int an = load_lines(afile, &a_lines);
    if (an <= 0) {
        for (int i = 0; i < qn; ++i) free(q_lines[i]);
        free(q_lines);
        if (an == 0) free(a_lines);
        return -1;
    }

    if (qn != an) {
        for (int i = 0; i < qn; ++i) free(q_lines[i]);
        for (int i = 0; i < an; ++i) free(a_lines[i]);
        free(q_lines);
        free(a_lines);
        return -1;
    }

    g_questions = q_lines;
    g_qcount = qn;
    g_answers = malloc(g_qcount + 1);
    if (!g_answers) {
        free_quiz_data();
        return -1;
    }

    for (int i = 0; i < g_qcount; ++i) {
        char *al = a_lines[i];
        char ch = '\0';
        for (size_t j = 0; al && al[j]; ++j) {
            if (!isspace((unsigned char)al[j])) { ch = (char)tolower((unsigned char)al[j]); break; }
        }
        if (ch == '\0') ch = '?';
        g_answers[i] = ch;
    }
    g_answers[g_qcount] = '\0';

    for (int i = 0; i < an; ++i) free(a_lines[i]);
    free(a_lines);

    return 0;
}

static void shuffle_indices(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

QuizResult take_quiz(void) {
    QuizResult res;
    res.total = 0;
    res.score = 0;
    res.incorrect_count = 0;
    memset(res.incorrect_ids, 0, sizeof(res.incorrect_ids));

    if (g_qcount == 0) {
        if (load_quiz_files(DEFAULT_QFILE, DEFAULT_AFILE) != 0) {
            fprintf(stderr, "Failed to load quiz files.\n");
            return res;
        }
    }

    /* Seed randomness once */
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    /* Create index list */
    int *indices = malloc(sizeof(int) * g_qcount);
    if (!indices) {
        fprintf(stderr, "Memory allocation failed.\n");
        return res;
    }

    for (int i = 0; i < g_qcount; i++)
        indices[i] = i;

    shuffle_indices(indices, g_qcount);

    int ask_count = QUIZ_QUESTIONS_PER_RUN;
    if (ask_count > g_qcount)
        ask_count = g_qcount;

    char buf[128];

    for (int k = 0; k < ask_count; k++) {
        int qi = indices[k];        /* actual question index */
        int qid = qi + 1;           /* original question ID */

        printf("\n%s\n", g_questions[qi]);
        printf("Your answer: ");

        if (!fgets(buf, sizeof(buf), stdin)) {
            printf("Input error; counted as incorrect.\n");
            res.incorrect_ids[res.incorrect_count++] = qid;
            continue;
        }

        int p = 0;
        while (buf[p] && isspace((unsigned char)buf[p])) p++;
        char ans = tolower((unsigned char)buf[p]);

        if (ans == '\n' || ans == '\0') {
            k--;   /* retry same question */
            continue;
        }

        if (ans == g_answers[qi]) {
            res.score++;
        } else {
            res.incorrect_ids[res.incorrect_count++] = qid;
        }

        res.total++;
    }

    free(indices);

    return res;
}


void quiz_cleanup(void) {
    free_quiz_data();
}
