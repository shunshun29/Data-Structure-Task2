#include "common.hpp"
#include "OrderQueue.hpp"
#include "RobotCircularQueue.hpp"
#include "MovementStack.hpp"
#include "ItemBST.hpp"
#include "WarehouseTree.hpp"

// returns true if the user entered nothing (just pressed Enter)
static bool isEmptyInput(const char str[]) {
    return str[0] == '\0';
}

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

int main() {
    OrderQueue         orderQueue;
    RobotCircularQueue robotQueue(MAX_ROBOTS);
    MovementStack      movementStack;
    ItemBST            itemBST;
    WarehouseTree      warehouseTree;

    // set up default data on startup
    cout << "=======================================================" << endl;
    cout << "  Warehouse Robot Navigation System  -  Initializing" << endl;
    cout << "=======================================================" << endl;

    // register 3 robots at the start
    for (int i = 1; i <= 3; i++) {
        Robot r;
        r.robotId         = i;
        r.status          = ROBOT_AVAILABLE;
        r.assignedOrderId = -1;
        robotQueue.addRobot(r);
    }
    cout << "Robots registered : R-1, R-2, R-3 (all Available)" << endl;

    // build the warehouse layout so routes and location checks work right away
    warehouseTree.buildLayout();

    // load a few sample items so the system is not completely empty
    {
        const int N = 5;
        const char ids  [N][MAX_ID_LENGTH]      = {"ITEM001","ITEM002","ITEM003","ITEM004","ITEM005"};
        const char names[N][MAX_NAME_LENGTH]     = {"Widget A","Gadget B","Component C","Module D","Part E"};
        const char locs [N][MAX_LOCATION_LENGTH] = {"ShelfA1-1","ShelfA2-1","ShelfB1-2","ShelfB2-3","ShelfC1-1"};
        for (int i = 0; i < N; i++) {
            Item item;
            copyText(item.itemId,   ids[i],   MAX_ID_LENGTH);
            copyText(item.itemName, names[i],  MAX_NAME_LENGTH);
            copyText(item.location, locs[i],   MAX_LOCATION_LENGTH);
            itemBST.insert(item);
        }
    }
    cout << "Sample items loaded: ITEM001 - ITEM005" << endl;
    cout << "=======================================================" << endl;

    int choice;

    do {
        showMainMenu();

        // handle non-integer input gracefully
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Error] Invalid input. Please enter a number (0-11)." << endl;
            continue;
        }
        cin.ignore(1000, '\n');

        switch (choice) {

            // add a new order to the queue
            case 1: {
                Order order;
                cout << "\n--- Add New Order ---" << endl;

                // order ID must be an integer
                cout << "Enter Order ID       : ";
                if (!(cin >> order.orderId)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "[Error] Order ID must be an integer." << endl;
                    break;
                }
                cin.ignore(1000, '\n');

                // order ID must be positive
                if (order.orderId <= 0) {
                    cout << "[Error] Order ID must be greater than 0." << endl;
                    break;
                }

                // no duplicate order IDs allowed in the queue
                if (orderQueue.containsOrderId(order.orderId)) {
                    cout << "[Error] Order ID #" << order.orderId
                         << " already exists in the queue. Use a different ID." << endl;
                    break;
                }

                // customer name cannot be blank
                cout << "Enter Customer Name  : ";
                cin.getline(order.customerName, MAX_NAME_LENGTH);
                if (isEmptyInput(order.customerName)) {
                    cout << "[Error] Customer name cannot be empty." << endl;
                    break;
                }

                // item ID cannot be blank
                cout << "Enter Item ID        : ";
                cin.getline(order.itemId, MAX_ID_LENGTH);
                if (isEmptyInput(order.itemId)) {
                    cout << "[Error] Item ID cannot be empty." << endl;
                    break;
                }

                // the item must already exist in the inventory before ordering it
                Item dummy;
                if (!itemBST.search(order.itemId, dummy)) {
                    cout << "[Error] Item '" << order.itemId
                         << "' does not exist in the inventory." << endl;
                    cout << "        Add the item first using Menu 6." << endl;
                    break;
                }

                order.status          = ORDER_PENDING;
                order.assignedRobotId = -1;
                orderQueue.enqueue(order);
                cout << "Order #" << order.orderId
                     << " added to queue successfully." << endl;
                break;
            }

            // show all orders currently waiting in the queue
            case 2:
                orderQueue.displayPendingOrders();
                break;

            // remove and show the next order from the front of the queue
            case 3: {
                Order processed;
                if (orderQueue.dequeue(processed)) {
                    cout << "\n--- Order Processed ---" << endl;
                    cout << "  Order ID   : " << processed.orderId       << endl;
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

            // show all registered robots and their status
            case 4:
                robotQueue.displayRobots();
                break;

            // assign the next available robot to the front order in the queue
            case 5: {
                cout << "\n--- Assign Robot to Order ---" << endl;

                if (orderQueue.isEmpty()) {
                    cout << "[Error] No pending orders in queue." << endl;
                    break;
                }

                // peek at the next order so we know what we are assigning to
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
                    cout << "(Use Menu 3 to dequeue the order when complete." << endl;
                    cout << " Use Menu 4 to mark the robot Available again.)" << endl;
                }
                break;
            }

            // add a new item to the inventory
            case 6: {
                Item item;
                cout << "\n--- Add Item ---" << endl;

                // item ID cannot be blank
                cout << "Enter Item ID    : ";
                cin.getline(item.itemId, MAX_ID_LENGTH);
                if (isEmptyInput(item.itemId)) {
                    cout << "[Error] Item ID cannot be empty." << endl;
                    break;
                }

                // item name cannot be blank
                cout << "Enter Item Name  : ";
                cin.getline(item.itemName, MAX_NAME_LENGTH);
                if (isEmptyInput(item.itemName)) {
                    cout << "[Error] Item name cannot be empty." << endl;
                    break;
                }

                // location cannot be blank
                cout << "Enter Location   : ";
                cin.getline(item.location, MAX_LOCATION_LENGTH);
                if (isEmptyInput(item.location)) {
                    cout << "[Error] Location cannot be empty." << endl;
                    break;
                }

                // the location must actually exist in the warehouse layout
                if (!warehouseTree.locationExists(item.location)) {
                    cout << "[Error] Location '" << item.location
                         << "' does not exist in the warehouse layout." << endl;
                    cout << "        Use Menu 8 to view all valid locations." << endl;
                    break;
                }

                itemBST.insert(item);
                cout << "Item '" << item.itemName
                     << "' added to inventory." << endl;
                break;
            }

            // search for an item by ID, name, or display everything
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
                    cout << "[Error] Invalid input. Enter 1, 2, or 3." << endl;
                    break;
                }
                cin.ignore(1000, '\n');

                if (searchChoice < 1 || searchChoice > 3) {
                    cout << "[Error] Invalid option. Enter 1, 2, or 3." << endl;
                    break;
                }

                Item result;

                if (searchChoice == 1) {
                    char itemId[MAX_ID_LENGTH];
                    cout << "Enter Item ID: ";
                    cin.getline(itemId, MAX_ID_LENGTH);

                    // search keyword cannot be blank
                    if (isEmptyInput(itemId)) {
                        cout << "[Error] Item ID cannot be empty." << endl;
                        break;
                    }
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

                    // search keyword cannot be blank
                    if (isEmptyInput(itemName)) {
                        cout << "[Error] Item name cannot be empty." << endl;
                        break;
                    }
                    if (itemBST.searchByName(itemName, result)) {
                        cout << "\nItem Found:" << endl;
                        cout << "  ID       : " << result.itemId   << endl;
                        cout << "  Name     : " << result.itemName << endl;
                        cout << "  Location : " << result.location << endl;
                    } else {
                        cout << "Item '" << itemName << "' not found." << endl;
                    }

                } else {
                    itemBST.displayInOrder();
                }
                break;
            }

            // print the tree structure of the warehouse
            case 8:
                warehouseTree.displayLayout();
                break;

            // generate a route between two locations
            case 9: {
                char from[MAX_LOCATION_LENGTH];
                char to[MAX_LOCATION_LENGTH];
                cout << "\n--- Generate Route ---" << endl;
                cout << "Zones  : Warehouse, ZoneA, ZoneB, ZoneC" << endl;
                cout << "Aisles : AisleA1, AisleA2, AisleB1, AisleB2, AisleC1, AisleC2" << endl;
                cout << "Shelves: ShelfA1-1..3, ShelfA2-1..2, ShelfB1-1..2," << endl;
                cout << "         ShelfB2-1..3, ShelfC1-1..2, ShelfC2-1" << endl;

                // starting location cannot be blank
                cout << "Enter starting location  : ";
                cin.getline(from, MAX_LOCATION_LENGTH);
                if (isEmptyInput(from)) {
                    cout << "[Error] Starting location cannot be empty." << endl;
                    break;
                }

                // destination cannot be blank
                cout << "Enter destination        : ";
                cin.getline(to, MAX_LOCATION_LENGTH);
                if (isEmptyInput(to)) {
                    cout << "[Error] Destination cannot be empty." << endl;
                    break;
                }

                Route route;
                if (warehouseTree.generateRoute(from, to, route)) {
                    warehouseTree.displayRoute(route);
                }
                break;
            }

            // record one movement step for a robot
            case 10: {
                char step[MAX_LOCATION_LENGTH];
                cout << "\n--- Record Robot Movement ---" << endl;
                cout << "Enter step (e.g. ZoneA, AisleB1, ShelfA1-1): ";
                cin.getline(step, MAX_LOCATION_LENGTH);

                // step name cannot be blank
                if (isEmptyInput(step)) {
                    cout << "[Error] Step cannot be empty." << endl;
                    break;
                }

                // step must be a real location in the warehouse
                if (!warehouseTree.locationExists(step)) {
                    cout << "[Error] '" << step
                         << "' is not a valid warehouse location." << endl;
                    cout << "        Use Menu 8 to see all valid locations." << endl;
                    break;
                }

                movementStack.push(step);
                movementStack.displayPath();
                break;
            }

            // retrace the robot's path by popping all steps in reverse
            case 11:
                movementStack.returnPath();
                break;

            case 0:
                cout << "Exiting system. Goodbye!" << endl;
                break;

            default:
                cout << "[Error] Invalid choice. Please enter a number between 0 and 11." << endl;
        }

    } while (choice != 0);

    return 0;
}
