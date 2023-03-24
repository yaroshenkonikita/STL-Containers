#-fsanitize=address
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic
TFLAGS = -lgtest -lgtest_main
CORE = s21_vector
TEST = s21_vector_test
COVEREGE = --coverage

all: clean gcov_report

test:
	$(CC) $(CFLAGS) Tests/*/*.cc $(TFLAGS) -o test
	@./test

gcov_report: test
	@lcov -t test -o test.info --no-external -c -d .
	@genhtml -o report test.info
	@open report/index.html

clean:
	@-rm -rf *.o *.a test Report/* *.info *.gc* core/*.a report

