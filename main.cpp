#include "common.hpp"
#include "OrderQueue.hpp"
#include "RobotCircularQueue.hpp"
#include "MovementStack.hpp"
#include "ItemBST.hpp"
#include "WarehouseTree.hpp"

// ─────────────────────────────────────────────────────────────────────────────

void showMainMenu() {
    cout << "\n========== Warehouse Robot Navigation System ==========" << endl;
    cout << "1.  Add New Order" << endl;
    cout << "2.  Display Pending Orders" << endl;
    cout << "3.  Process Next Order" << endl;
    cout << "4.  Display Robots" << endl;
    cout << "5.  Assign Robot to Order" << endl;
    cout << "6.  Add Item" << endl;
    cout << "7.  Search Item" << endl;
    cout << "8.  Display Warehouse Layout" << endl;
    cout << "9.  Generate Route" << endl;
    cout << "10. Record Robot Movement" << endl;
    cout << "11. Return Robot Using Reverse Path" << endl;
    cout << "0.  Exit" << endl;
    cout << "=======================================================" << endl;
    cout << "Enter your choice: ";
}

// ─────────────────────────────────────────────────────────────────────────────

int main() {
    OrderQueue       orderQueue;
    RobotCircularQueue robotQueue(MAX_ROBOTS);
    MovementStack    movementStack;
    ItemBST          itemBST;
    WarehouseTree    warehouseTree;

    // ── Startup: pre-register robots ────────────────────────────────────────
    cout << "=======================================================" << endl;
    cout << "  Warehouse Robot Navigation System  —  Initializing" << endl;
    cout << "=======================================================" << endl;

    for (int i = 1; i <= 3; i++) {
        Robot r;
        r.robotId        = i;
        r.status         = ROBOT_AVAILABLE;
        r.assignedOrderId = -1;
        robotQueue.addRobot(r);
    }
    cout << "Robots registered : R-1, R-2, R-3 (all Available)" << endl;

    // ── Startup: build warehouse layout ─────────────────────────────────────
    warehouseTree.buildLayout();

    // ── Startup: pre-load sample items ──────────────────────────────────────
    {
        const int SAMPLE_COUNT = 5;
        const char sampleIds  [SAMPLE_COUNT][MAX_ID_LENGTH]       = {"ITEM001","ITEM002","ITEM003","ITEM004","ITEM005"};
        const char sampleNames[SAMPLE_COUNT][MAX_NAME_LENGTH]      = {"Widget A","Gadget B","Component C","Module D","Part E"};
        const char sampleLocs [SAMPLE_COUNT][MAX_LOCATION_LENGTH]  = {"ShelfA1-1","ShelfA2-1","ShelfB1-2","ShelfB2-3","ShelfC1-1"};

        for (int i = 0; i < SAMPLE_COUNT; i++) {
            Item item;
            copyText(item.itemId,   sampleIds[i],   MAX_ID_LENGTH);
            copyText(item.itemName, sampleNames[i],  MAX_NAME_LENGTH);
            copyText(item.location, sampleLocs[i],   MAX_LOCATION_LENGTH);
            itemBST.insert(item);
        }
    }
    cout << "Sample items loaded: ITEM001 – ITEM005" << endl;
    cout << "=======================================================" << endl;

    // ── Main loop ────────────────────────────────────────────────────────────
    int choice;

    do {
        showMainMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number (0-11)." << endl;
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice) {

            // ─────────────────────────────────────────────────────────────────
            // 1. Add New Order  (OrderQueue::enqueue)
            // ─────────────────────────────────────────────────────────────────
            case 1: {
                Order order;
                cout << "\n--- Add New Order ---" << endl;

                cout << "Enter Order ID       : ";
                if (!(cin >> order.orderId)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Order ID. Returning to menu." << endl;
                    break;
                }
                cin.ignore(1000, '\n');

                cout << "Enter Customer Name  : ";
                cin.getline(order.customerName, MAX_NAME_LENGTH);

                cout << "Enter Item ID        : ";
                cin.getline(order.itemId, MAX_ID_LENGTH);

                order.status          = ORDER_PENDING;
                order.assignedRobotId = -1;

                orderQueue.enqueue(order);
                cout << "Order #" << order.orderId
                     << " added to queue successfully." << endl;
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 2. Display Pending Orders  (OrderQueue::displayPendingOrders)
            // ─────────────────────────────────────────────────────────────────
            case 2:
                orderQueue.displayPendingOrders();
                break;

            // ─────────────────────────────────────────────────────────────────
            // 3. Process Next Order  (OrderQueue::dequeue)
            // ─────────────────────────────────────────────────────────────────
            case 3: {
                Order processed;
                if (orderQueue.dequeue(processed)) {
                    cout << "\n--- Order Processed ---" << endl;
                    cout << "  Order ID   : " << processed.orderId      << endl;
                    cout << "  Customer   : " << processed.customerName  << endl;
                    cout << "  Item ID    : " << processed.itemId        << endl;
                    cout << "  Status     : " << orderStatusToText(processed.status) << endl;
                    cout << "Order #" << processed.orderId
                         << " removed from queue." << endl;
                } else {
                    cout << "No pending orders to process." << endl;
                }
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 4. Display Robots  (RobotCircularQueue::displayRobots)
            // ─────────────────────────────────────────────────────────────────
            case 4:
                robotQueue.displayRobots();
                break;

            // ─────────────────────────────────────────────────────────────────
            // 5. Assign Robot to Order  (RobotCircularQueue::getNextAvailableRobot)
            // ─────────────────────────────────────────────────────────────────
            case 5: {
                cout << "\n--- Assign Robot to Order ---" << endl;

                if (orderQueue.isEmpty()) {
                    cout << "No pending orders in queue." << endl;
                    break;
                }

                Order nextOrder;
                orderQueue.peek(nextOrder);
                cout << "Next pending order : #" << nextOrder.orderId
                     << "  (Customer: " << nextOrder.customerName
                     << ", Item: "      << nextOrder.itemId << ")" << endl;

                Robot assigned;
                if (robotQueue.getNextAvailableRobot(assigned)) {
                    cout << "Robot R-" << assigned.robotId
                         << " assigned to Order #" << nextOrder.orderId
                         << "." << endl;
                    cout << "Robot R-" << assigned.robotId
                         << " status is now: Busy" << endl;
                    cout << "(Use option 3 to dequeue the order when complete.)" << endl;
                }
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 6. Add Item  (ItemBST::insert)
            // ─────────────────────────────────────────────────────────────────
            case 6: {
                Item item;
                cout << "\n--- Add Item ---" << endl;

                cout << "Enter Item ID    : ";
                cin.getline(item.itemId, MAX_ID_LENGTH);

                cout << "Enter Item Name  : ";
                cin.getline(item.itemName, MAX_NAME_LENGTH);

                cout << "Enter Location   : ";
                cin.getline(item.location, MAX_LOCATION_LENGTH);

                itemBST.insert(item);
                cout << "Item '" << item.itemName
                     << "' added to inventory." << endl;
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 7. Search Item  (ItemBST::search / searchByName)
            // ─────────────────────────────────────────────────────────────────
            case 7: {
                cout << "\n--- Search Item ---" << endl;
                cout << "Search by:" << endl;
                cout << "  1) Item ID" << endl;
                cout << "  2) Item Name" << endl;
                cout << "  3) Display All Items" << endl;
                cout << "Enter choice: ";

                int searchChoice;
                if (!(cin >> searchChoice)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input." << endl;
                    break;
                }
                cin.ignore(1000, '\n');

                Item result;

                if (searchChoice == 1) {
                    char itemId[MAX_ID_LENGTH];
                    cout << "Enter Item ID: ";
                    cin.getline(itemId, MAX_ID_LENGTH);

                    if (itemBST.search(itemId, result)) {
                        cout << "\nItem Found:" << endl;
                        cout << "  ID       : " << result.itemId   << endl;
                        cout << "  Name     : " << result.itemName << endl;
                        cout << "  Location : " << result.location << endl;
                    } else {
                        cout << "Item with ID '" << itemId << "' not found." << endl;
                    }

                } else if (searchChoice == 2) {
                    char itemName[MAX_NAME_LENGTH];
                    cout << "Enter Item Name: ";
                    cin.getline(itemName, MAX_NAME_LENGTH);

                    if (itemBST.searchByName(itemName, result)) {
                        cout << "\nItem Found:" << endl;
                        cout << "  ID       : " << result.itemId   << endl;
                        cout << "  Name     : " << result.itemName << endl;
                        cout << "  Location : " << result.location << endl;
                    } else {
                        cout << "Item '" << itemName << "' not found." << endl;
                    }

                } else if (searchChoice == 3) {
                    itemBST.displayInOrder();

                } else {
                    cout << "Invalid search option." << endl;
                }
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 8. Display Warehouse Layout  (WarehouseTree::displayLayout)
            // ─────────────────────────────────────────────────────────────────
            case 8:
                warehouseTree.displayLayout();
                break;

            // ─────────────────────────────────────────────────────────────────
            // 9. Generate Route  (WarehouseTree::generateRoute)
            // ─────────────────────────────────────────────────────────────────
            case 9: {
                char from[MAX_LOCATION_LENGTH];
                char to[MAX_LOCATION_LENGTH];
                cout << "\n--- Generate Route ---" << endl;
                cout << "Available zones: Warehouse, ZoneA, ZoneB, ZoneC" << endl;
                cout << "Aisles: AisleA1, AisleA2, AisleB1, AisleB2, AisleC1, AisleC2" << endl;
                cout << "Shelves: ShelfA1-1..3, ShelfA2-1..2, ShelfB1-1..2," << endl;
                cout << "         ShelfB2-1..3, ShelfC1-1..2, ShelfC2-1" << endl;
                cout << "Enter starting location  : ";
                cin.getline(from, MAX_LOCATION_LENGTH);
                cout << "Enter destination        : ";
                cin.getline(to, MAX_LOCATION_LENGTH);

                Route route;
                if (warehouseTree.generateRoute(from, to, route)) {
                    warehouseTree.displayRoute(route);
                }
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 10. Record Robot Movement  (MovementStack::push / displayPath)
            // ─────────────────────────────────────────────────────────────────
            case 10: {
                char step[MAX_LOCATION_LENGTH];
                cout << "\n--- Record Robot Movement ---" << endl;
                cout << "Enter step (e.g. ZoneA, AisleB1, ShelfA1-1): ";
                cin.getline(step, MAX_LOCATION_LENGTH);
                movementStack.push(step);
                movementStack.displayPath();
                break;
            }

            // ─────────────────────────────────────────────────────────────────
            // 11. Return Robot Using Reverse Path  (MovementStack::returnPath)
            // ─────────────────────────────────────────────────────────────────
            case 11:
                movementStack.returnPath();
                break;

            // ─────────────────────────────────────────────────────────────────
            case 0:
                cout << "Exiting system. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a number between 0 and 11." << endl;
        }

    } while (choice != 0);

    return 0;
}
