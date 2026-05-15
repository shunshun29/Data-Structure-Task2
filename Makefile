CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = dstr-task2

SRCS = main.cpp \
			 OrderQueue.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)