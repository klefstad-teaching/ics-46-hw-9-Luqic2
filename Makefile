CXX = g++
# CXXFLAGS= -ggdb -std=c++20 -Wall -Werror -Wextra -Wfatal-errors -pedantic

# main: src/ladder_main.cpp src/ladder.cpp
# 	$(CXX) src/ladder_main.cpp src/ladder.cpp -o ladder


CXXFLAGS = -lgtest -lgtest_main -lpthread

tests: gtest/student_gtests.cpp src/ladder.cpp
	$(CXX) -o tests gtest/student_gtests.cpp src/ladder.cpp $(CXXFLAGS)