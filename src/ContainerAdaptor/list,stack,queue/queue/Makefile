.PHONY: all clean test $(SOURCENAME).a gcov_report style

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest
RFLAGS = -fprofile-arcs -ftest-coverage
SOURCENAME = s21_queue

all: test

test: tests_queue.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(RFLAGS) tests_queue.cc -o test $(TFLAGS)
	@./test

clean:
	@-rm -rf *.o *.a *gcda *gcno *info report test

leaks:
	leaks -atExit -- ./test

gcov_report: test
	@lcov -t test -o rep.info -c -d . --no-external
	@genhtml -o report rep.info
	@open ./report/index.html

style:
	@clang-format -style=google -n s21_queue.h tests_queue.cc
	@clang-format -style=google -i s21_queue.h tests_queue.cc