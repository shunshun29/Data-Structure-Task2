#ifndef ROBOTCIRCULARQUEUE_HPP
#define ROBOTCIRCULARQUEUE_HPP

#include "common.hpp"

// circular queue for managing robot assignments
// uses a fixed-size array and a cursor that moves forward each time a robot is assigned
// this way robots are used in rotation instead of always picking the same one
class RobotCircularQueue {
public:
    RobotCircularQueue(int capacity);
    ~RobotCircularQueue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool addRobot(const Robot& robot);
    bool getNextAvailableRobot(Robot& robot);             // find next available robot using rotation
    bool updateRobotStatus(int robotId, RobotStatus status);
    void displayRobots() const;

private:
    Robot* robots;   // heap-allocated array to store all robots
    int    capacity; // max number of robots the queue can hold
    int    count;    // how many robots are currently registered
    int    cursor;   // index where the next search starts (rotates after each assignment)
};

#endif
