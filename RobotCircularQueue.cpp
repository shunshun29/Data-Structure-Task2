#include "RobotCircularQueue.hpp"

// allocate the robot array and set up the starting values
RobotCircularQueue::RobotCircularQueue(int capacity) {
    this->capacity = capacity;
    this->count    = 0;
    this->cursor   = 0;
    this->robots   = new Robot[capacity];
}

// release the array when the queue is destroyed
RobotCircularQueue::~RobotCircularQueue() {
    delete[] robots;
}

bool RobotCircularQueue::isEmpty() const {
    return count == 0;
}

bool RobotCircularQueue::isFull() const {
    return count == capacity;
}

int RobotCircularQueue::size() const {
    return count;
}

// add a robot to the next free slot in the array
bool RobotCircularQueue::addRobot(const Robot& robot) {
    if (isFull()) {
        cout << "[RobotCircularQueue] Cannot add robot — queue is full (capacity: "
             << capacity << ")." << endl;
        return false;
    }
    robots[count] = robot;
    count++;
    return true;
}

// starting from cursor, look for the next available robot
// wraps around to the beginning using the modulo trick
// once a robot is found, mark it busy and advance the cursor so
// the next search starts from a different robot (fair rotation)
bool RobotCircularQueue::getNextAvailableRobot(Robot& robot) {
    if (isEmpty()) {
        cout << "[RobotCircularQueue] No robots registered." << endl;
        return false;
    }

    // try each slot at most count times before giving up
    for (int attempts = 0; attempts < count; attempts++) {
        int index = (cursor + attempts) % count;  // wrap around if we reach the end

        if (robots[index].status == ROBOT_AVAILABLE) {
            robots[index].status = ROBOT_BUSY;

            // move cursor past this robot so next call starts from a different one
            cursor = (index + 1) % count;

            robot = robots[index];
            return true;
        }
    }

    // all robots are busy or under maintenance
    cout << "[RobotCircularQueue] No available robot found." << endl;
    return false;
}

// search for a robot by ID and change its status
bool RobotCircularQueue::updateRobotStatus(int robotId, RobotStatus status) {
    for (int i = 0; i < count; i++) {
        if (robots[i].robotId == robotId) {
            robots[i].status = status;

            // when a robot becomes available again, clear its assigned order
            if (status == ROBOT_AVAILABLE) {
                robots[i].assignedOrderId = -1;
            }
            return true;
        }
    }

    cout << "[RobotCircularQueue] Robot ID " << robotId << " not found." << endl;
    return false;
}

// print all robots with their current status in a table
void RobotCircularQueue::displayRobots() const {
    cout << "\n========== All Robots ==========" << endl;

    if (isEmpty()) {
        cout << "  (no robots registered)" << endl;
        cout << "=================================" << endl;
        return;
    }

    cout << "  Index | Robot ID | Status       | Assigned Order" << endl;
    cout << "  ------|----------|--------------|---------------" << endl;

    for (int i = 0; i < count; i++) {
        // mark cursor position so the user can see where next search starts
        const char* marker = (i == cursor % count) ? " <--" : "    ";

        cout << "  [" << i << "]   | "
             << "R-" << robots[i].robotId << "     | "
             << robotStatusToText(robots[i].status);

        // pad the status string so columns stay aligned
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
