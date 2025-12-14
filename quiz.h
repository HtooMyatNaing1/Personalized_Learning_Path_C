#ifndef QUIZ_H
#define QUIZ_H

typedef struct {
    int total;
    int score;
    int incorrect_ids[16];
    int incorrect_count;
} QuizResult;


QuizResult take_quiz(void);

void quiz_cleanup(void);

#endif /* QUIZ_H */
