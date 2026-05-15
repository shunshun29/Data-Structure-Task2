#ifndef ORDER_QUEUE_HPP
#define ORDER_QUEUE_HPP

#include "common.hpp"

class OrderQueue {
private:
    struct Node {
        Order data;
        Node* next;
    };

    Node* frontPtr;
    Node* rearPtr;
    int count;

public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(const Order& order);
    bool dequeue(Order& order);
    bool peek(Order& order) const;

    void displayPendingOrders() const;
};

#endif