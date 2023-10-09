.PHONY: all test gcov_report style clean

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
	@mkdir -p coverage
	@mv `find . -name "*.gc*"` coverage
	@echo "tests is complete"

gcov_report: test
	@echo "Compiling coverage files..."
	@lcov -t tests/test -o test.info --no-external -c -d containers -d containers_plus -d containers_dependence -d containers_boost -d coverage
	@echo "Compiling report html"
	@genhtml -o report test.info
	@echo "report is done"
	@open report/index.html

style:
	@clang-format -style=google -n $(TEST) $(CORE) *.h

clean:
	@-rm -rf *.o *.a report/ *.info `find . -name "*.gc*"` test coverage
