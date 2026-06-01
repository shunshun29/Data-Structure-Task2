// =============================================================================
// RobotCircularQueue.cpp
// Robot Assignment Module — Member 2
//
// Implementation of a custom Circular Queue for managing warehouse robots.
//
// Data Structure choice — Circular Queue (fixed-size array):
//   A circular queue lets the "cursor" advance indefinitely without ever
//   needing to shift elements or reallocate memory. When the cursor reaches
//   the end of the array it wraps back to index 0, creating a continuous
//   rotation over all robots. This perfectly matches the requirement of
//   distributing tasks "in a continuous rotation" without restarting.
//
//   Time complexity:
//     addRobot            — O(1)
//     getNextAvailableRobot — O(n) worst case (all robots busy/maintenance)
//     updateRobotStatus   — O(n) linear scan by robotId
//     displayRobots       — O(n)
//   Space complexity: O(capacity) — fixed, allocated once in the constructor.
// =============================================================================

#include "RobotCircularQueue.hpp"

// -----------------------------------------------------------------------------
// Constructor
// Allocate the internal array and initialise bookkeeping variables.
// -----------------------------------------------------------------------------
RobotCircularQueue::RobotCircularQueue(int capacity) {
    this->capacity = capacity;
    this->count    = 0;
    this->cursor   = 0;
    this->robots   = new Robot[capacity];  // Heap allocation — no STL
}

// -----------------------------------------------------------------------------
// Destructor
// Release the heap-allocated array to avoid memory leaks.
// -----------------------------------------------------------------------------
RobotCircularQueue::~RobotCircularQueue() {
    delete[] robots;
}

// -----------------------------------------------------------------------------
// isEmpty
// Returns true when no robots have been registered yet.
// -----------------------------------------------------------------------------
bool RobotCircularQueue::isEmpty() const {
    return count == 0;
}

// -----------------------------------------------------------------------------
// isFull
// Returns true when the queue already holds 'capacity' robots.
// -----------------------------------------------------------------------------
bool RobotCircularQueue::isFull() const {
    return count == capacity;
}

// -----------------------------------------------------------------------------
// size
// Returns the number of robots currently registered.
// -----------------------------------------------------------------------------
int RobotCircularQueue::size() const {
    return count;
}

// -----------------------------------------------------------------------------
// addRobot
// Append a new robot to the next free slot.
// The array is used as a simple sequential store (not a sliding-window queue);
// robots are added at index 'count' and never removed, so the circular
// behaviour applies only to the rotation cursor used during assignment.
// Returns false if the queue is already full.
// -----------------------------------------------------------------------------
bool RobotCircularQueue::addRobot(const Robot& robot) {
    if (isFull()) {
        cout << "[RobotCircularQueue] Cannot add robot — queue is full (capacity: "
             << capacity << ")." << endl;
        return false;
    }

    robots[count] = robot;  // Copy the Robot struct into the array
    count++;
    return true;
}

// -----------------------------------------------------------------------------
// getNextAvailableRobot
// Starting from 'cursor', walk through every robot (at most 'count' steps)
// and return the first one whose status is ROBOT_AVAILABLE.
//
// On success:
//   - The found robot's status is changed to ROBOT_BUSY.
//   - 'cursor' advances to the slot after the chosen robot so the next call
//     begins its search from a different position (fair rotation).
//   - The updated Robot struct is copied into the 'robot' out-parameter.
//   - Returns true.
//
// On failure (no available robot found):
//   - Returns false without modifying any stored robot.
// -----------------------------------------------------------------------------
bool RobotCircularQueue::getNextAvailableRobot(Robot& robot) {
    if (isEmpty()) {
        cout << "[RobotCircularQueue] No robots registered." << endl;
        return false;
    }

    // Try each slot at most 'count' times before giving up
    for (int attempts = 0; attempts < count; attempts++) {
        int index = (cursor + attempts) % count;  // Wrap-around index

        if (robots[index].status == ROBOT_AVAILABLE) {
            // Mark as busy so the same robot is not handed out twice in a row
            robots[index].status = ROBOT_BUSY;

            // Advance cursor past this robot for the next assignment
            cursor = (index + 1) % count;

            // Return a copy of the selected robot
            robot = robots[index];
            return true;
        }
    }

    // All robots are busy or under maintenance
    cout << "[RobotCircularQueue] No available robot found." << endl;
    return false;
}

// -----------------------------------------------------------------------------
// updateRobotStatus
// Locate the robot by its robotId (linear scan) and change its status.
// Also resets assignedOrderId to -1 when the robot becomes available again,
// since a robot returning to available state is no longer on an order.
// Returns false if no robot with the given ID exists.
// -----------------------------------------------------------------------------
bool RobotCircularQueue::updateRobotStatus(int robotId, RobotStatus status) {
    for (int i = 0; i < count; i++) {
        if (robots[i].robotId == robotId) {
            robots[i].status = status;

            // If the robot is being made available, clear its order link
            if (status == ROBOT_AVAILABLE) {
                robots[i].assignedOrderId = -1;
            }
            return true;
        }
    }

    cout << "[RobotCircularQueue] Robot ID " << robotId << " not found." << endl;
    return false;
}

// -----------------------------------------------------------------------------
// displayRobots
// Print a formatted table of all registered robots and their current status.
// The cursor position is also shown so the rotation progress is visible.
// -----------------------------------------------------------------------------
void RobotCircularQueue::displayRobots() const {
    cout << "\n========== All Robots ==========" << endl;

    if (isEmpty()) {
        cout << "  (no robots registered)" << endl;
        cout << "=================================" << endl;
        return;
    }

    // Column header
    cout << "  Index | Robot ID | Status       | Assigned Order" << endl;
    cout << "  ------|----------|--------------|---------------" << endl;

    for (int i = 0; i < count; i++) {
        // Mark the current cursor position with an arrow so it is easy to
        // see where the next assignment search will begin
        const char* marker = (i == cursor % count) ? " <--" : "    ";

        cout << "  [" << i << "]   | "
             << "R-" << robots[i].robotId   << "     | "
             << robotStatusToText(robots[i].status);

        // Pad status string to a fixed width for alignment
        int statusLen = 0;
        const char* s = robotStatusToText(robots[i].status);
        while (s[statusLen] != '\0') statusLen++;
        for (int sp = statusLen; sp < 12; sp++) cout << ' ';

        cout << "| ";
        if (robots[i].assignedOrderId == -1) {
            cout << "None";
        } else {
            cout << "Order #" << robots[i].assignedOrderId;
        }
        cout << marker << endl;
    }

    cout << "=================================" << endl;
    cout << "  Total robots : " << count << " / " << capacity << endl;
    cout << "  Next search  : index [" << cursor % count << "]" << endl;
    cout << "=================================" << endl;
}
