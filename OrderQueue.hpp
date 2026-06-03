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

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(const Order& order);   // add a new order to the back
    bool dequeue(Order& order);         // remove and return the front order
    bool peek(Order& order) const;      // look at the front order without removing it

    void displayPendingOrders() const;
    bool containsOrderId(int orderId) const;  // check if an order ID already exists
};

#endif
