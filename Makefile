
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
OBJS = main.o lessons.o quiz.o planner.o fileio.o utils.o


pointer_learning: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)


main.o: main.c lessons.h quiz.h planner.h fileio.h utils.h
	$(CC) $(CFLAGS) -c main.c


lessons.o: lessons.c lessons.h
	$(CC) $(CFLAGS) -c lessons.c -o lessons.o


quiz.o: quiz.c quiz.h
	$(CC) $(CFLAGS) -c quiz.c -o quiz.o


planner.o: planner.c planner.h
	$(CC) $(CFLAGS) -c planner.c -o planner.o


fileio.o: fileio.c fileio.h quiz.h
	$(CC) $(CFLAGS) -c fileio.c -o fileio.o


utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c -o utils.o


clean:
	rm -f *.o pointer_learning