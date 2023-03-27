.PHONY: test

CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TFLAGS = -lgtest -lgtest_main
CORE = $(shell ls Containers*/*.h)
TEST = $(shell ls Tests/*.cc)
COVERAGE = --coverage

all: clean gcov_report

test:
	@echo "Compiling tests binary executor..."
	@$(CC) $(CFLAGS) $(COVERAGE) $(TEST) -o test $(TFLAGS)
	@echo "Executor is done"
	@echo "Start tests..."
	@./test
	@mv *.gc* Tests
	@echo "Tests is complete"

gcov_report: test
	@echo "Compiling coverage files..."
	@lcov -t Tests/test -o test.info --no-external -c -d Tests -d Containers -d ContainersPlus -d ContainersDependence
	@echo "Compiling report html"
	@genhtml -o report test.info
	@echo "Report is done"
	@open report/index.html

style:
	@clang-format -style=google -n $(TEST) $(CORE) *.h


clean:
	@-rm -rf *.o *.a Report/* *.info Tests/*.gc* core/*.a report test *.gc*

