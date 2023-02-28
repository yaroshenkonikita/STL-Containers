.PHONY: test_set test_multiset test_map
# test:

test_set:
	g++ src/Tests/SortedContainer/Set/test_set.cc -lgtest -lgtest_main -o src/test -std=c++20
	./src/test

test_multiset:
	g++ src/Tests/SortedContainer/Multiset/test_multiset.cc -lgtest -lgtest_main -o src/test -std=c++20
	./src/test

test_map:
	g++ src/Tests/SortedContainer/Map/test_map.cc -lgtest -lgtest_main -o src/test -std=c++20
	./src/test