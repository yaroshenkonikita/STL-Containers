cmake_minimum_required(VERSION 3.24)
project(CPP2_s21_containers_0)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SortedContainer)
include_directories(src/SortedContainer/AssociativeContainer)
include_directories(src/SortedContainer/SetContainer)
include_directories(src/Tests)
include_directories(src/Tests/SortedContainer)
include_directories(src/Tests/SortedContainer/Map)
include_directories(src/Tests/SortedContainer/Multiset)
include_directories(src/Tests/SortedContainer/Set)

add_executable(CPP2_s21_containers_0
        src/SortedContainer/AssociativeContainer/s21_map.h
        src/SortedContainer/SetContainer/s21_multiset.h
        src/SortedContainer/SetContainer/s21_set.h
        src/SortedContainer/BinaryTree.h
        src/Tests/SortedContainer/Map/test_map.cc
        src/Tests/SortedContainer/Multiset/test_multuset.cc
        src/Tests/SortedContainer/Set/test_set.cc
        src/s21_containers.h
        src/s21_containersplus.h)
