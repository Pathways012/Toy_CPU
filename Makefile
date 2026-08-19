CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic -g


cpu: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o cpu


run: cpu
	./cpu

clean:
	rm -f cpu

.PHONY: run clean
