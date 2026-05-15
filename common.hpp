#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <cstring>
using namespace std;

/*
    Common definitions for Warehouse Robot Navigation System.

    Important:
    Do not use STL containers such as vector, list, queue, stack, map, or set.
    Each member must implement their own data structure manually.
*/

const int MAX_ID_LENGTH = 20;
const int MAX_NAME_LENGTH = 50;
const int MAX_LOCATION_LENGTH = 100;
const int MAX_ROUTE_STEPS = 100;
const int MAX_ROBOTS = 10;

enum OrderStatus {
    ORDER_PENDING,
    ORDER_ASSIGNED,
    ORDER_COMPLETED
};

enum RobotStatus {
    ROBOT_AVAILABLE,
    ROBOT_BUSY,
    ROBOT_MAINTENANCE
};

struct Order {
    int orderId;
    char customerName[MAX_NAME_LENGTH];
    char itemId[MAX_ID_LENGTH];
    OrderStatus status;
    int assignedRobotId;
};

struct Robot {
    int robotId;
    RobotStatus status;
    int assignedOrderId;
};

struct Item {
    char itemId[MAX_ID_LENGTH];
    char itemName[MAX_NAME_LENGTH];
    char location[MAX_LOCATION_LENGTH];
};

struct Route {
    char steps[MAX_ROUTE_STEPS][MAX_LOCATION_LENGTH];
    int stepCount;
};

inline void copyText(char destination[], const char source[], int maxLength) {
    strncpy(destination, source, maxLength - 1);
    destination[maxLength - 1] = '\0';
}

inline const char* orderStatusToText(OrderStatus status) {
    if (status == ORDER_PENDING) return "Pending";
    if (status == ORDER_ASSIGNED) return "Assigned";
    if (status == ORDER_COMPLETED) return "Completed";
    return "Unknown";
}

inline const char* robotStatusToText(RobotStatus status) {
    if (status == ROBOT_AVAILABLE) return "Available";
    if (status == ROBOT_BUSY) return "Busy";
    if (status == ROBOT_MAINTENANCE) return "Maintenance";
    return "Unknown";
}

#endif