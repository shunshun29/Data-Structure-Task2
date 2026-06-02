#include "OrderQueue.hpp"

// ─── Constructor & Destructor ────────────────────────────────────────────────

OrderQueue::OrderQueue() : frontPtr(nullptr), rearPtr(nullptr), count(0) {}

OrderQueue::~OrderQueue() {
    Node* current = frontPtr;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// ─── Status Checks ────────────────────────────────────────────────────────────

bool OrderQueue::isEmpty() const {
    return count == 0;
}

int OrderQueue::size() const {
    return count;
}

// ─── Enqueue ──────────────────────────────────────────────────────────────────

void OrderQueue::enqueue(const Order& order) {
    Node* newNode = new Node;
    newNode->data = order;
    newNode->next = nullptr;

    if (rearPtr == nullptr) {
        frontPtr = newNode;
        rearPtr  = newNode;
    } else {
        rearPtr->next = newNode;
        rearPtr       = newNode;
    }
    count++;
}

// ─── Dequeue ──────────────────────────────────────────────────────────────────

bool OrderQueue::dequeue(Order& order) {
    if (isEmpty()) return false;

    Node* temp   = frontPtr;
    order        = frontPtr->data;
    frontPtr     = frontPtr->next;

    if (frontPtr == nullptr) {
        rearPtr = nullptr;
    }

    delete temp;
    count--;
    return true;
}

// ─── Peek ─────────────────────────────────────────────────────────────────────

bool OrderQueue::peek(Order& order) const {
    if (isEmpty()) return false;
    order = frontPtr->data;
    return true;
}

// ─── Display ─────────────────────────────────────────────────────────────────

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
