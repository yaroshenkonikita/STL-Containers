.PHONY: all clean test $(SOURCENAME).a gcov_report style

CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest
RFLAGS = -fprofile-arcs -ftest-coverage
SOURCENAME = s21_stack

all: test

test: tests_stack.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) tests_stack.cc -o test $(TFLAGS)
	@./test

clean:
	@-rm -rf *.o *.a *gcda *gcno *info report test

leaks:
	leaks -atExit -- ./test
