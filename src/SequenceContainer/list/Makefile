.PHONY: all clean test $(SOURCENAME).a gcov_report style
#-pedantic -fsanitize=address
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAGS = -lgtest
RFLAGS = -fprofile-arcs -ftest-coverage
SOURCENAME = s21_list

all: test

test: tests_list.cc $(SOURCENAME).h
	@$(CC) $(CFLAGS) tests_list.cc -o test $(TFLAGS)
	@./test

debug: s21_list.h
	@$(CC) $(CFLAGS) debug.cc -o debug
	@./debug
	@rm debug

clean:
	@-rm -rf *.o *.a *gcda *gcno *info report test debug

leaks:
	leaks -atExit -- ./test
