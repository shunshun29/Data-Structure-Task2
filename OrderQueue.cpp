#include "OrderQueue.hpp"

// start with an empty queue
OrderQueue::OrderQueue() : frontPtr(nullptr), rearPtr(nullptr), count(0), completedCount(0) {}

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

// print all orders currently in the queue (includes both PENDING and ASSIGNED)
void OrderQueue::displayPendingOrders() const {
    if (isEmpty()) {
        cout << "[OrderQueue] No active orders." << endl;
        return;
    }

    cout << "\n===== Active Orders (" << count << " total) =====" << endl;
    cout << "--------------------------------------------------------------" << endl;

    Node* current = frontPtr;
    int pos = 1;
    while (current != nullptr) {
        const Order& o = current->data;
        cout << "#" << pos++
             << " | Order ID: "  << o.orderId
             << " | Customer: "  << o.customerName
             << " | Item ID: "   << o.itemId
             << " | Status: "    << orderStatusToText(o.status)
             << " | Robot: ";
        if (o.assignedRobotId == -1) cout << "None";
        else                         cout << "R-" << o.assignedRobotId;
        cout << endl;
        current = current->next;
    }

    cout << "--------------------------------------------------------------" << endl;
}

// return the first order in the queue that is still PENDING (no robot yet)
bool OrderQueue::peekFirstPending(Order& order) const {
    Node* current = frontPtr;
    while (current != nullptr) {
        if (current->data.status == ORDER_PENDING) {
            order = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}

// set assignedRobotId and change status to ORDER_ASSIGNED for the given order
bool OrderQueue::updateOrderAssignment(int orderId, int robotId) {
    Node* current = frontPtr;
    while (current != nullptr) {
        if (current->data.orderId == orderId) {
            current->data.assignedRobotId = robotId;
            current->data.status          = ORDER_ASSIGNED;
            return true;
        }
        current = current->next;
    }
    return false;
}

// check active queue AND completed history so order IDs are globally unique
bool OrderQueue::containsOrderId(int orderId) const {
    Node* current = frontPtr;
    while (current != nullptr) {
        if (current->data.orderId == orderId) return true;
        current = current->next;
    }
    for (int i = 0; i < completedCount; i++) {
        if (completedOrders[i].orderId == orderId) return true;
    }
    return false;
}

// save a completed order to the fixed-size history array
void OrderQueue::addToCompleted(const Order& order) {
    if (completedCount >= MAX_COMPLETED_ORDERS) {
        cout << "[OrderQueue] Completed history is full." << endl;
        return;
    }
    completedOrders[completedCount++] = order;
}

// print all completed orders
void OrderQueue::displayCompletedOrders() const {
    if (completedCount == 0) {
        cout << "[OrderQueue] No completed orders yet." << endl;
        return;
    }

    cout << "\n===== Completed Orders (" << completedCount << " total) =====" << endl;
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < completedCount; i++) {
        const Order& o = completedOrders[i];
        cout << "#" << (i + 1)
             << " | Order ID: " << o.orderId
             << " | Customer: " << o.customerName
             << " | Item ID: "  << o.itemId
             << " | Robot: R-"  << o.assignedRobotId
             << " | Status: "   << orderStatusToText(o.status)
             << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}
