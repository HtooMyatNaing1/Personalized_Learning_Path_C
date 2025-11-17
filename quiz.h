#ifndef QUIZ_H
#define QUIZ_H

typedef struct {
    int total;
    int score;
    int incorrect_ids[16];
    int incorrect_count;
} QuizResult;

/* function prototype */
QuizResult take_quiz(void);

#endif /* QUIZ_H */
