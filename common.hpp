#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <cstring>
using namespace std;

// shared structs, enums, and constants used by all modules
// do not use STL containers anywhere in the project

// max sizes for string fields
const int MAX_ID_LENGTH       = 20;
const int MAX_NAME_LENGTH     = 50;
const int MAX_LOCATION_LENGTH = 100;
const int MAX_ROUTE_STEPS     = 100;
const int MAX_ROBOTS          = 10;

// possible states for an order
enum OrderStatus {
    ORDER_PENDING,
    ORDER_ASSIGNED,
    ORDER_COMPLETED
};

// possible states for a robot
enum RobotStatus {
    ROBOT_AVAILABLE,
    ROBOT_BUSY,
    ROBOT_MAINTENANCE
};

// holds all the info for one order
struct Order {
    int orderId;
    char customerName[MAX_NAME_LENGTH];
    char itemId[MAX_ID_LENGTH];
    OrderStatus status;
    int assignedRobotId;
};

// holds robot info and its current state
struct Robot {
    int robotId;
    RobotStatus status;
    int assignedOrderId;
};

// represents one item stored in the warehouse
struct Item {
    char itemId[MAX_ID_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
};

// stores a generated route as an array of location names
struct Route {
    char steps[MAX_ROUTE_STEPS][MAX_LOCATION_LENGTH];
    int stepCount;
};

// safe string copy that avoids buffer overflow
inline void copyText(char destination[], const char source[], int maxLength) {
    strncpy(destination, source, maxLength - 1);
    destination[maxLength - 1] = '\0';
}

// convert OrderStatus enum to a readable string
inline const char* orderStatusToText(OrderStatus status) {
    if (status == ORDER_PENDING)   return "Pending";
    if (status == ORDER_ASSIGNED)  return "Assigned";
    if (status == ORDER_COMPLETED) return "Completed";
    return "Unknown";
}

// convert RobotStatus enum to a readable string
inline const char* robotStatusToText(RobotStatus status) {
    if (status == ROBOT_AVAILABLE)    return "Available";
    if (status == ROBOT_BUSY)         return "Busy";
    if (status == ROBOT_MAINTENANCE)  return "Maintenance";
    return "Unknown";
}

#endif
