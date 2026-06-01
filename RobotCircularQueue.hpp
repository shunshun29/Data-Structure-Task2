// =============================================================================
// RobotCircularQueue.hpp
// Robot Assignment Module — Member 2
//
// Manages robot task distribution using a custom Circular Queue implemented
// with a fixed-size array. Robots are selected in a rotating fashion so that
// workload is spread evenly. Robots marked ROBOT_BUSY or ROBOT_MAINTENANCE
// are automatically skipped during assignment.
//
// Rules:
//   - No STL containers (no <vector>, <queue>, <list>, etc.)
//   - No additional main() function
//   - Must include common.hpp
// =============================================================================

#ifndef ROBOTCIRCULARQUEUE_HPP
#define ROBOTCIRCULARQUEUE_HPP

#include "common.hpp"

// -----------------------------------------------------------------------------
// RobotCircularQueue
//
// Internal storage: a fixed-size array of Robot structs (size = capacity given
// in the constructor). Two indices — front and rear — advance modulo capacity
// to wrap around, giving the circular behaviour.
//
//   [ R0 | R1 | R2 | R3 | ... | R(cap-1) ]
//      ^front               ^rear
//
// getNextAvailableRobot() walks forward from the current position, skipping
// busy/maintenance robots, and returns the first available one. The internal
// "cursor" advances after each successful assignment so the next call starts
// searching from the robot after the one just assigned (rotation).
// -----------------------------------------------------------------------------
class RobotCircularQueue {
public:
    // Constructor — allocates internal array of given capacity
    RobotCircularQueue(int capacity);

    // Destructor — releases heap memory
    ~RobotCircularQueue();

    // Returns true when no robots have been added yet
    bool isEmpty() const;

    // Returns true when the queue holds 'capacity' robots
    bool isFull() const;

    // Returns the number of robots currently registered
    int size() const;

    // Register a new robot. Returns false if the queue is full.
    bool addRobot(const Robot& robot);

    // Rotate through the queue and return the next ROBOT_AVAILABLE robot.
    // The robot's status is changed to ROBOT_BUSY and its assignedOrderId is
    // set to -1 (the caller is expected to set the real order ID afterwards
    // via updateRobotStatus if needed).
    // Returns false if no available robot exists.
    bool getNextAvailableRobot(Robot& robot);

    // Update the status of the robot identified by robotId.
    // Returns false if no robot with that ID exists.
    bool updateRobotStatus(int robotId, RobotStatus status);

    // Print a formatted list of all registered robots and their current status.
    void displayRobots() const;

private:
    Robot* robots;      // Heap-allocated array of Robot structs
    int    capacity;    // Maximum number of robots the queue can hold
    int    count;       // Current number of registered robots
    int    cursor;      // Index from which the next search begins (rotation point)
};

#endif // ROBOTCIRCULARQUEUE_HPP
