#include <stdio.h>
#include <string.h>
#include "quiz.h"

static const char *questions[] = {
    "1) What operator gives the address of a variable?\n a) * b) & c) -> d) %\n",
    "2) If int *p; what is *p?\n a) address b) value at that address c) pointer size d) type\n",
    "3) Which expression equals a[3]?\n a) *(a+3) b) *a+3 c) a+3 d) &a[3]\n",
    "4) Which function is used to allocate memory in C?\n a) malloc b) alloc c) new d) create\n",
    "5) What bug: using free() twice on same pointer?\n a) dangling b) double free c) leak d) overflow\n",
    "6) In function void f(int *p) { *p = 5; } what happens?\n a) nothing b) caller's value set to 5 c) memory freed d) compile error\n"
};

static const char answers[] = {'b','b','a','a','b','b'};
static const int QCOUNT = 6;


QuizResult take_quiz(void) {
    QuizResult res = {0};
    res.total = QCOUNT; res.score = 0; res.incorrect_count = 0;
    char buf[16];
    for (int i=0;i<QCOUNT;i++) {
        printf("\n%s", questions[i]);
        printf("Your answer: ");
        if (!fgets(buf, sizeof(buf), stdin)) { buf[0]='\n'; }
            char ans = buf[0];
            if (ans == '\n') { i--; continue; }
            if (ans == answers[i]) { res.score++; }
            else { res.incorrect_ids[res.incorrect_count++] = i+1; }
        }
    return res;
}