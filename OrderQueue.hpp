#ifndef ORDER_QUEUE_HPP
#define ORDER_QUEUE_HPP

#include "common.hpp"

// custom linked list queue for managing pending orders
// orders are added at the back and removed from the front (FIFO)
class OrderQueue {
private:
    // each node holds one order and a pointer to the next
    struct Node {
        Order data;
        Node* next;
    };

    Node* frontPtr;  // points to the front of the queue
    Node* rearPtr;   // points to the back of the queue
    int count;       // keeps track of how many orders are in the queue

    Order completedOrders[MAX_COMPLETED_ORDERS];
    int   completedCount;

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(const Order& order);
    bool dequeue(Order& order);
    bool peek(Order& order) const;

    bool updateOrderAssignment(int orderId, int robotId);  // set assignedRobotId + ORDER_ASSIGNED

    bool peekFirstPending(Order& order) const;  // return the first PENDING order without removing it

    void displayPendingOrders() const;
    bool containsOrderId(int orderId) const;    // checks both active queue and completed history

    void addToCompleted(const Order& order);
    void displayCompletedOrders() const;
};

#endif
