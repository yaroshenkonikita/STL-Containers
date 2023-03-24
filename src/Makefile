.PHONY: test

#-fsanitize=address
CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TFLAGS = -lgtest -lgtest_main
CORE = $(shell ls Containers*/*.h)
TEST = $(shell ls Tests/*.cc)
COVERAGE = --coverage

all: clean gcov_report

test:
	@echo "Please wait"
	@$(CC) $(CFLAGS) $(COVERAGE) $(TEST) -o test $(TFLAGS)
	@./test

gcov_report: test
	@lcov -t test -o test.info --no-external -c -d .
	@genhtml -o report test.info
	@open report/index.html

style:
	@clang-format -style=google -n $(TEST) $(CORE)


clean:
	@-rm -rf *.o *.a Report/* *.info *.gc* core/*.a report test

