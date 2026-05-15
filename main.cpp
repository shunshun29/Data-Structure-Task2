#include "common.hpp"

void showMainMenu() {
    cout << "\n========== Warehouse Robot Navigation System ==========" << endl;
    cout << "1. Add New Order" << endl;
    cout << "2. Display Pending Orders" << endl;
    cout << "3. Process Next Order" << endl;
    cout << "4. Display Robots" << endl;
    cout << "5. Assign Robot to Order" << endl;
    cout << "6. Add Item" << endl;
    cout << "7. Search Item" << endl;
    cout << "8. Display Warehouse Layout" << endl;
    cout << "9. Generate Route" << endl;
    cout << "10. Record Robot Movement" << endl;
    cout << "11. Return Robot Using Reverse Path" << endl;
    cout << "0. Exit" << endl;
    cout << "=======================================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "[TODO] Connect Order Management Module: Add New Order" << endl;
                break;

            case 2:
                cout << "[TODO] Connect Order Management Module: Display Pending Orders" << endl;
                break;

            case 3:
                cout << "[TODO] Connect Order Management Module: Process Next Order" << endl;
                break;

            case 4:
                cout << "[TODO] Connect Robot Assignment Module: Display Robots" << endl;
                break;

            case 5:
                cout << "[TODO] Connect Robot Assignment Module: Assign Robot to Order" << endl;
                break;

            case 6:
                cout << "[TODO] Connect Item Search and Management Module: Add Item" << endl;
                break;

            case 7:
                cout << "[TODO] Connect Item Search and Management Module: Search Item" << endl;
                break;

            case 8:
                cout << "[TODO] Connect Warehouse Layout Module: Display Warehouse Layout" << endl;
                break;

            case 9:
                cout << "[TODO] Connect Warehouse Layout Module: Generate Route" << endl;
                break;

            case 10:
                cout << "[TODO] Connect Navigation Module: Record Robot Movement" << endl;
                break;

            case 11:
                cout << "[TODO] Connect Navigation Module: Return Robot Using Reverse Path" << endl;
                break;

            case 0:
                cout << "Exiting system..." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}