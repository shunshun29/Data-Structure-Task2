CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = dstr-task2

# Add each member's .cpp here once their module is merged
SRCS = main.cpp \
       OrderQueue.cpp \
       RobotCircularQueue.cpp \
       MovementStack.cpp \
       ItemBST.cpp \
       WarehouseTree.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
