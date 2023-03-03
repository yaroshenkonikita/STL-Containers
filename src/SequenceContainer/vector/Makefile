.PHONY: all clean test s21_vector.a
#-fsanitize=address
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic
TFLAGS = -lgtest
CORE = s21_vector
TEST = s21_vector_test
COVEREGE = --coverage

all: s21_vector.a test

s21_vector.a: $(CORE).h
	$(CC) $(CFLAGS) -c $(CORE).cc
	ar rc $(CORE).a $(CORE).o
	rm $(CORE).o

test: $(CORE).h $(TEST).cc
	$(CC) $(CFLAGS) $(COVEREGE) $(TEST).cc -o test $(TFLAGS)
	./test

gcov_report: test
	lcov -t test -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	-rm -rf *.o *.a test object_files/./test object_files/*.gc* Report/* *.info *.gc* core/*.a
