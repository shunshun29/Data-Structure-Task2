#include "OrderQueue.hpp"

// start with an empty queue
OrderQueue::OrderQueue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

// walk through all nodes and delete them to avoid memory leak
OrderQueue::~OrderQueue() {
    Node* current = frontPtr;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

bool OrderQueue::isEmpty() const {
    return count == 0;
}

int OrderQueue::size() const {
    return count;
}

// add a new order to the back of the queue
void OrderQueue::enqueue(const Order& order) {
    Node* newNode = new Node;
    newNode->data = order;
    newNode->next = nullptr;

    if (rearPtr == nullptr) {
        // queue was empty, new node is both front and back
        frontPtr = newNode;
        rearPtr  = newNode;
    } else {
        rearPtr->next = newNode;
        rearPtr       = newNode;
    }
    count++;
}

// remove the front order and return it
bool OrderQueue::dequeue(Order& order) {
    if (isEmpty()) return false;

    Node* temp = frontPtr;
    order      = frontPtr->data;
    frontPtr   = frontPtr->next;

    // if the queue is now empty, reset the rear pointer too
    if (frontPtr == nullptr) {
        rearPtr = nullptr;
    }

    delete temp;
    count--;
    return true;
}

// return the front order without removing it from the queue
bool OrderQueue::peek(Order& order) const {
    if (isEmpty()) return false;
    order = frontPtr->data;
    return true;
}

// print all orders currently in the queue
void OrderQueue::displayPendingOrders() const {
    if (isEmpty()) {
        cout << "[OrderQueue] No pending orders." << endl;
        return;
    }

    cout << "\n===== Pending Orders (" << count << " total) =====" << endl;
    cout << "------------------------------------------------------" << endl;

    Node* current = frontPtr;
    int pos = 1;
    while (current != nullptr) {
        const Order& o = current->data;
        cout << "#" << pos++
             << " | Order ID: "  << o.orderId
             << " | Customer: "  << o.customerName
             << " | Item ID: "   << o.itemId
             << " | Status: "    << orderStatusToText(o.status)
             << endl;
        current = current->next;
    }

    cout << "------------------------------------------------------" << endl;
}

// scan through the whole queue to check if the order ID already exists
bool OrderQueue::containsOrderId(int orderId) const {
    Node* current = frontPtr;
    while (current != nullptr) {
        if (current->data.orderId == orderId) return true;
        current = current->next;
    }
    return false;
}
