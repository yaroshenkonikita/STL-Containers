.PHONY: test
test:
	g++ src/Tests/SortedContainer/*/*.cc -lgtest -lgtest_main -o src/test -std=c++17
	./src/test
