CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = warehouse

SRCS = main.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)