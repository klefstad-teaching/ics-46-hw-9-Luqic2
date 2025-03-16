CXX = g++
CXXFLAGS = -lgtest -lgtest_main -lpthread

tests: gtest/student_gtests.cpp src/ladder.cpp
	$(CXX) -o tests gtest/student_gtests.cpp src/ladder.cpp $(CXXFLAGS)