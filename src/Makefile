.PHONY: test

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TFLAGS = -lgtest -lgtest_main
CORE = $(shell ls containers*/*.h)
TEST = $(shell ls tests/*.cc)
COVERAGE = --coverage

all: clean gcov_report

test:
	@echo "Compiling tests binary executor..."
	@$(CC) $(CFLAGS) $(COVERAGE) $(TEST) -I. -o test $(TFLAGS)
	@echo "Executor is done"
	@echo "Start tests..."
	@./test
	@mv *.gc* tests
	@echo "tests is complete"

gcov_report: test
	@echo "Compiling coverage files..."
	@lcov -t tests/test -o test.info --no-external -c -d tests -d containers -d containers_plus -d containers_dependence
	@echo "Compiling report html"
	@genhtml -o report test.info
	@echo "report is done"
	@open report/index.html

style:
	@clang-format -style=google -n $(TEST) $(CORE) *.h


clean:
	@-rm -rf *.o *.a report/* *.info tests/*.gc* core/*.a report test *.gc*

