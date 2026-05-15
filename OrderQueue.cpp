#include "OrderQueue.hpp"

OrderQueue::OrderQueue() {
    frontPtr = nullptr;
    rearPtr = nullptr;
    count = 0;
}

OrderQueue::~OrderQueue() {
    Node* current = frontPtr;

    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    frontPtr = nullptr;
    rearPtr = nullptr;
    count = 0;
}

bool OrderQueue::isEmpty() const {
    return count == 0;
}

int OrderQueue::size() const {
    return count;
}

void OrderQueue::enqueue(const Order& order) {
    Node* newNode = new Node;
    newNode->data = order;
    newNode->next = nullptr;

    if (isEmpty()) {
        frontPtr = newNode;
        rearPtr = newNode;
    } else {
        rearPtr->next = newNode;
        rearPtr = newNode;
    }

    count++;

    cout << "Order added successfully. Order ID: " << order.orderId << endl;
}

bool OrderQueue::dequeue(Order& order) {
    if (isEmpty()) {
        cout << "No pending orders available." << endl;
        return false;
    }

    Node* temp = frontPtr;
    order = frontPtr->data;

    frontPtr = frontPtr->next;

    if (frontPtr == nullptr) {
        rearPtr = nullptr;
    }

    delete temp;
    count--;

    cout << "Order removed from queue. Order ID: " << order.orderId << endl;
    return true;
}

bool OrderQueue::peek(Order& order) const {
    if (isEmpty()) {
        return false;
    }

    order = frontPtr->data;
    return true;
}

void OrderQueue::displayPendingOrders() const {
    if (isEmpty()) {
        cout << "No pending orders." << endl;
        return;
    }

    cout << "\n--- Pending Orders ---" << endl;

    Node* current = frontPtr;

    while (current != nullptr) {
        cout << "Order ID: " << current->data.orderId
             << " | Customer: " << current->data.customerName
             << " | Item ID: " << current->data.itemId
             << " | Status: " << orderStatusToText(current->data.status)
             << " | Assigned Robot: " << current->data.assignedRobotId
             << endl;

        current = current->next;
    }
}