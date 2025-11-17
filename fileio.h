#ifndef FILEIO_H
#define FILEIO_H
#include "quiz.h"

int save_user_result(const char *filename, const char *username, const QuizResult *res);

#endif