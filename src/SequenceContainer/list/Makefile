.PHONY: all clean test $(SOURCENAME).a gcov_report style

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -fsanitize=address
TFLAGS = -lgtest
RFLAGS = -fprofile-arcs -ftest-coverage
SOURCENAME = s21_list

all: test

test: tests_list.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) $(RFLAGS) tests_list.cc -o test $(TFLAGS)
	@./test

debug: s21_list.h
	@$(CC) $(CFLAGS) debug.cc -o debug
	@./debug
	@rm debug

gcov_report: test
	@lcov -t test -o rep.info -c -d . --no-external
	@genhtml -o report rep.info
	@open ./report/index.html

clean:
	@-rm -rf *.o *.a *gcda *gcno *info report test debug a.out

leaks:
	leaks -atExit -- ./test
