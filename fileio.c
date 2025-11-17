#include <stdio.h>
#include <string.h>
#include "fileio.h"

int save_user_result(const char *filename, const char *username, const QuizResult *res) {
    FILE *f = fopen(filename, "a");
    if (!f) return -1;
    /* CSV: username,score,total,incorrect_count,incorrect_ids(semi-colon separated) */
    fprintf(f, "%s,%d,%d,%d,", username, res->score, res->total, res->incorrect_count);
    for (int i=0;i<res->incorrect_count;i++) {
        fprintf(f, "%d", res->incorrect_ids[i]);
        if (i+1<res->incorrect_count) fprintf(f, ";");
    }
    fprintf(f, "\n");
    fclose(f);
    printf("User result saved to %s\n", filename);
    return 0;
}