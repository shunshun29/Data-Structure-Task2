# Warehouse Robot Navigation System

## Project Overview

This project is a C++ prototype for a Warehouse Robot Navigation System.

The system manages warehouse orders, assigns robots, searches item locations, simulates robot movement, and allows robots to return using a reverse path.

This assignment focuses on implementing and explaining appropriate data structures and algorithms.

---

## Team Roles

| Member | Role | Module | Data Structure | Files to Create |
|---|---|---|---|---|
| Leader | Project setup, integration support, common file management | Order Management | Custom Queue | `OrderQueue.hpp`, `OrderQueue.cpp` |
| Member 2 | Module developer | Robot Assignment | Custom Circular Queue | `RobotCircularQueue.hpp`, `RobotCircularQueue.cpp` |
| Member 3 | Module developer | Robot Navigation / Path Tracking | Custom Stack | `MovementStack.hpp`, `MovementStack.cpp` |
| Member 4 | Module developer | Item Search / Management | Custom Binary Search Tree | `ItemBST.hpp`, `ItemBST.cpp` |
| Member 5 | Module developer | Warehouse Layout / Navigation | Custom Tree | `WarehouseTree.hpp`, `WarehouseTree.cpp` |

---

## Leader Responsibilities

The team leader is responsible for managing the following files:

- `common.hpp`
- `Makefile`
- `README.md`
- Final integration support

The leader also works as a member and is responsible for:

- `OrderQueue.hpp`
- `OrderQueue.cpp`

Important:

- `common.hpp` should not be changed without the leader's permission.
- `Makefile` should not be changed without the leader's permission.
- If a member needs to change a shared file, they must discuss it with the leader first.

---

## Main Menu Structure and Ownership

### Who Owns `main.cpp`

`main.cpp` is managed **exclusively by the leader**.

Members must **not edit `main.cpp` directly**. The leader is responsible for connecting each module's functions to the correct menu option after all Pull Requests have been merged.

If you want to test menu-like behaviour locally, create your own `test_yourmodule.cpp` file. See the [Unit Testing with Dummy Data](#unit-testing-with-dummy-data) section below.

---

### Menu Number → Module Mapping

The main menu has 11 options. Each option belongs to a specific member's module.

```text
========== Warehouse Robot Navigation System ==========
1.  Add New Order                    → Leader        (OrderQueue)
2.  Display Pending Orders           → Leader        (OrderQueue)
3.  Process Next Order               → Leader        (OrderQueue)
4.  Display Robots                   → Member 2      (RobotCircularQueue)
5.  Assign Robot to Order            → Member 2      (RobotCircularQueue)
6.  Add Item                         → Member 4      (ItemBST)
7.  Search Item                      → Member 4      (ItemBST)
8.  Display Warehouse Layout         → Member 5      (WarehouseTree)
9.  Generate Route                   → Member 5      (WarehouseTree)
10. Record Robot Movement            → Member 3      (MovementStack)
11. Return Robot Using Reverse Path  → Member 3      (MovementStack)
0.  Exit
=======================================================
```

| Menu No. | Feature | Owner | Class | Key Function(s) |
|---|---|---|---|---|
| 1 | Add New Order | Leader | `OrderQueue` | `enqueue()` |
| 2 | Display Pending Orders | Leader | `OrderQueue` | `displayPendingOrders()` |
| 3 | Process Next Order | Leader | `OrderQueue` | `dequeue()` |
| 4 | Display Robots | Member 2 | `RobotCircularQueue` | `displayRobots()` |
| 5 | Assign Robot to Order | Member 2 | `RobotCircularQueue` | `getNextAvailableRobot()` |
| 6 | Add Item | Member 4 | `ItemBST` | `insert()` |
| 7 | Search Item | Member 4 | `ItemBST` | `search()` / `searchByName()` |
| 8 | Display Warehouse Layout | Member 5 | `WarehouseTree` | `displayLayout()` |
| 9 | Generate Route | Member 5 | `WarehouseTree` | `generateRoute()` |
| 10 | Record Robot Movement | Member 3 | `MovementStack` | `push()` / `displayPath()` |
| 11 | Return Robot Using Reverse Path | Member 3 | `MovementStack` | `returnPath()` |

---

### How the Leader Connects Your Module

Once your Pull Request is merged, the leader will update `main.cpp` like this:

```cpp
// Example: how the leader wires up Member 2's module in main.cpp
case 4:
    robotQueue.displayRobots();
    break;

case 5:
    Robot assigned;
    if (robotQueue.getNextAvailableRobot(assigned)) {
        cout << "Robot " << assigned.robotId << " assigned." << endl;
    }
    break;
```

You do not need to do this yourself. Just make sure your functions match the pre-defined interface exactly.

---

### Testing Your Menu Flow Locally (Without Touching `main.cpp`)

If you want to simulate what your menu option will look like when integrated, create a local `test_yourmodule.cpp` with a small `main()` that calls your functions directly.

Example for Member 3 (Navigation, menu options 10 and 11):

```cpp
// test_navigation.cpp  (local only — do not commit)
#include "MovementStack.hpp"
#include <iostream>
using namespace std;

int main() {
    MovementStack stack;

    // Simulate menu option 10: Record Robot Movement
    cout << "\n[Menu 10] Record Robot Movement" << endl;
    stack.push("Start");
    stack.push("ZoneA");
    stack.push("AisleB");
    stack.push("Shelf3");
    stack.displayPath();

    // Simulate menu option 11: Return Robot Using Reverse Path
    cout << "\n[Menu 11] Return Robot Using Reverse Path" << endl;
    stack.returnPath();

    return 0;
}
```

Compile and run:

```bash
g++ -std=c++17 test_navigation.cpp MovementStack.cpp -o test_nav
./test_nav
```

This lets you verify that your functions produce the correct output **before integration**, without ever touching `main.cpp`.

---

## Interface Pre-Definition by Leader

Before members start coding their `.cpp` files, the leader will define the **class structure and function signatures** in each `.hpp` file.

This is called **interface-first design**. It allows all members to work in parallel without waiting for each other, because everyone knows exactly what functions to implement.

### Why This Matters

- Members know the exact function names and parameter types they must implement.
- The leader can write `main.cpp` integration code in advance.
- Function name mismatches at integration time are avoided.
- Members can write dummy data tests against a known interface.

### Pre-Defined Interfaces

The leader defines the following interfaces. Members must implement exactly these functions in their `.cpp` files.

---

#### Order Management — `OrderQueue.hpp`

```cpp
class OrderQueue {
public:
    OrderQueue();
    ~OrderQueue();

    bool isEmpty() const;
    int size() const;

    void enqueue(const Order& order);   // Add new order to rear
    bool dequeue(Order& order);         // Remove order from front
    bool peek(Order& order) const;      // View front order without removing

    void displayPendingOrders() const;  // Print all pending orders
};
```

---

#### Robot Assignment — `RobotCircularQueue.hpp`

```cpp
class RobotCircularQueue {
public:
    RobotCircularQueue(int capacity);
    ~RobotCircularQueue();

    bool isEmpty() const;
    bool isFull() const;
    int size() const;

    bool addRobot(const Robot& robot);          // Register a robot
    bool getNextAvailableRobot(Robot& robot);   // Rotate and get next available robot
    bool updateRobotStatus(int robotId, RobotStatus status); // Update robot status
    void displayRobots() const;                 // Print all robots and status
};
```

---

#### Robot Navigation — `MovementStack.hpp`

```cpp
class MovementStack {
public:
    MovementStack();
    ~MovementStack();

    bool isEmpty() const;
    int size() const;

    void push(const char step[]);   // Record one movement step
    bool pop(char step[]);          // Remove last step (for backtracking)
    bool peek(char step[]) const;   // View last step without removing

    void displayPath() const;       // Print full forward path
    void returnPath();              // Pop and print each step in reverse
    void clearPath();               // Reset all recorded steps
};
```

---

#### Item Management — `ItemBST.hpp`

```cpp
class ItemBST {
public:
    ItemBST();
    ~ItemBST();

    void insert(const Item& item);              // Insert item into BST
    bool search(const char itemId[], Item& result) const;  // Search by ID
    bool searchByName(const char name[], Item& result) const; // Search by name
    void displayInOrder() const;                // Print all items sorted by ID
    bool remove(const char itemId[]);           // Delete an item by ID
};
```

---

#### Warehouse Layout — `WarehouseTree.hpp`

```cpp
class WarehouseTree {
public:
    WarehouseTree();
    ~WarehouseTree();

    void buildLayout();                         // Initialize default warehouse structure
    void displayLayout() const;                 // Print tree layout (zones/aisles/shelves)
    bool generateRoute(const char from[], const char to[], Route& route); // Find path
    void displayRoute(const Route& route) const; // Print generated route steps
};
```

---

### Member Checklist After Reading Pre-Defined Interfaces

Before writing your `.cpp` file, confirm:

```text
□ I have read my assigned .hpp file.
□ I understand the function names, return types, and parameters.
□ I will not rename or remove any pre-defined function.
□ I may add private helper functions inside my .cpp as needed.
□ I will not change the public interface without discussing with the leader.
```

---

## Unit Testing with Dummy Data

Each member can test their module independently **without waiting for other modules to be completed**.

The key idea: since all modules share the same struct definitions in `common.hpp`, you can create dummy data manually and pass it into your own functions.

### How to Test Your Module Independently

**Step 1 — Compile only your module**

You do not need the full project to compile your own files.

```bash
g++ -std=c++17 -c YourFile.cpp
```

If there are no errors, your file compiles correctly on its own.

---

**Step 2 — Write a simple local test**

Create a temporary `test_yourmodule.cpp` file **in your local environment only** (do not commit this file).

Use it to call your own functions with dummy data.

Example for Robot Assignment module:

```cpp
// test_robotqueue.cpp  (local test only, do not commit)
#include "RobotCircularQueue.hpp"

int main() {
    // Create dummy robots using the Robot struct from common.hpp
    Robot r1;
    r1.robotId = 1;
    r1.status = ROBOT_AVAILABLE;
    r1.assignedOrderId = -1;

    Robot r2;
    r2.robotId = 2;
    r2.status = ROBOT_BUSY;
    r2.assignedOrderId = 5;

    // Test your module functions
    RobotCircularQueue queue(5);
    queue.addRobot(r1);
    queue.addRobot(r2);
    queue.displayRobots();

    Robot assigned;
    if (queue.getNextAvailableRobot(assigned)) {
        cout << "Assigned Robot ID: " << assigned.robotId << endl;
    }

    return 0;
}
```

Compile and run the test:

```bash
g++ -std=c++17 test_robotqueue.cpp RobotCircularQueue.cpp -o test_robot
./test_robot
```

---

**Step 3 — Test examples for each module**

| Module | Dummy Data to Create | Key Functions to Test |
|---|---|---|
| Order Management | Create `Order` with orderId, customerName, itemId | `enqueue`, `dequeue`, `displayPendingOrders` |
| Robot Assignment | Create `Robot` with robotId, status | `addRobot`, `getNextAvailableRobot`, `displayRobots` |
| Navigation | Use plain strings like `"ZoneA"`, `"AisleB"` as steps | `push`, `displayPath`, `returnPath` |
| Item Management | Create `Item` with itemId, itemName, location | `insert`, `search`, `displayInOrder` |
| Warehouse Layout | No external data needed; `buildLayout()` sets it up | `buildLayout`, `displayLayout`, `generateRoute` |

---

**Step 4 — Expected output before integration**

Before submitting your Pull Request, you should be able to run your local test and see sensible output such as:

```text
--- Pending Orders ---
Order ID: 1 | Customer: Alice | Item ID: ITEM001 | Status: Pending

--- All Robots ---
Robot ID: 1 | Status: Available
Robot ID: 2 | Status: Busy

--- Movement Path ---
Step 1: Start
Step 2: ZoneA
Step 3: AisleB
Step 4: Shelf3
--- Returning ---
Step 4: Shelf3
Step 3: AisleB
Step 2: ZoneA
Step 1: Start
```

---

### Do Not Commit Local Test Files

Local test files such as `test_yourmodule.cpp` are for your own testing only.

Do not commit them to GitHub.

Add them to `.gitignore` if needed:

```text
test_*.cpp
```

---

## File Creation Rules

Each member must create their own `.hpp` and `.cpp` files.

```text
Order Management:
- OrderQueue.hpp
- OrderQueue.cpp

Robot Assignment:
- RobotCircularQueue.hpp
- RobotCircularQueue.cpp

Navigation:
- MovementStack.hpp
- MovementStack.cpp

Item Management:
- ItemBST.hpp
- ItemBST.cpp

Warehouse Layout:
- WarehouseTree.hpp
- WarehouseTree.cpp
```

Each `.hpp` file must include:

```cpp
#include "common.hpp"
```

Each member must design and implement their own data structure inside their own files.

Do not define another `main()` function in module files.  
Only `main.cpp` should contain the `main()` function.

---

## Important Programming Rules

Do not use STL containers such as:

```cpp
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
```

The assignment focuses on custom data structures, so each member must manually implement their own structure.

| Module | Correct Approach | Do Not Use |
|---|---|---|
| Order Management | Custom linked-node Queue | `std::queue` |
| Robot Assignment | Custom Circular Queue | `std::queue` |
| Navigation | Custom Stack | `std::stack` |
| Item Management | Custom BST | `std::map` |
| Warehouse Layout | Custom Tree | `std::vector` |

---

## Branch Rules

Do not work directly on the `main` branch.

Each member must create their own feature branch before working.

Recommended branch names:

```text
feature/order-management
feature/robot-assignment
feature/navigation-stack
feature/item-management
feature/warehouse-layout
```

Basic rule:

```text
1 feature branch = 1 Pull Request

After the Pull Request is merged, the feature branch should be deleted.

For the next task, create a new branch from the latest main.
```

---

## Pull Request Rules

All work must be submitted through a Pull Request.

Only the team leader is allowed to merge Pull Requests.

Members must not press the merge button by themselves.

## Pull Request Checklist

Before creating a Pull Request, check the following:

```text
□ I am working on my own feature branch.
□ I did not work directly on main.
□ I only edited my own module files.
□ I did not change common.hpp without permission.
□ I did not change Makefile without permission.
□ I did not use STL containers such as vector, list, queue, stack, map, or set.
□ I did not define another main() function.
□ My module includes common.hpp.
□ My data structure is implemented manually.
□ My code compiles successfully (tested with g++ -std=c++17 -c).
□ I ran a local dummy data test and confirmed output is sensible.
□ I did not commit local test files (test_*.cpp).
□ My commit message is clear.
```

---

## Standard GitHub Workflow

All members must follow this workflow when working on their assigned module.

### 1. Open VS Code terminal and move to the project folder

```bash
cd path/to/your/project-folder
git status
```

### 2. Check GitHub remote connection

```bash
git remote -v
```

Expected result:

```text
origin  https://github.com/shunshun29/Data-Structure-task2.git (fetch)
origin  https://github.com/shunshun29/Data-Structure-task2.git (push)
```

### 3. Move to the main branch

```bash
git checkout main
```

### 4. Pull the latest code from GitHub main branch

```bash
git pull origin main
```

### 5. Create your own working branch

```bash
git checkout -b feature/your-task-name
```

Examples:

```bash
git checkout -b feature/order-management
git checkout -b feature/robot-assignment
git checkout -b feature/navigation-stack
git checkout -b feature/item-management
git checkout -b feature/warehouse-layout
```

Check that you are on the correct branch:

```bash
git branch
```

### 6. Coding

Work only on your assigned `.hpp` and `.cpp` files.

Do not edit `main.cpp`, `common.hpp`, or `Makefile` without the leader's permission.

### 7. Check changed files

```bash
git status
git diff
```

### 8. Add changed files

```bash
git add YourFile.hpp YourFile.cpp
```

### 9. Commit your changes

```bash
git commit -m "Clear commit message"
```

### 10. Push your working branch to GitHub

```bash
git push -u origin feature/your-task-name
```

### 11. Create a Pull Request on GitHub

Pull Request title example:

```text
Implement robot assignment module
```

Pull Request description example:

```md
## Summary
Implemented the Robot Assignment module using a custom Circular Queue.

## Changes
- Added RobotCircularQueue.hpp
- Added RobotCircularQueue.cpp
- Implemented addRobot, getNextAvailableRobot, updateRobotStatus, displayRobots

## Data Structure
- Custom Circular Queue using fixed-size array

## Local Test
- Created test_robotqueue.cpp locally (not committed)
- Confirmed rotation skips ROBOT_BUSY and ROBOT_MAINTENANCE correctly

## Checklist
- [x] I worked on my own feature branch
- [x] I did not edit main directly
- [x] I did not change common.hpp without permission
- [x] I did not use STL containers
- [x] I did not define another main() function
- [x] My code compiles
- [x] I ran a local dummy data test
```

### 12. Leader checks and approves

Leader checks:

```text
- The member worked on the correct files
- The code does not use banned STL containers
- The code includes common.hpp
- The code does not contain another main() function
- The code compiles successfully
- The public interface matches the pre-defined .hpp
- The data structure is implemented manually
- The member can explain their data structure choice
```

### 13. After the Pull Request is merged

```bash
git checkout main
git pull origin main
git branch -d feature/your-task-name
```

---

## Build Instructions

Use Makefile:

```bash
make
./dstr-task2
```

For Windows PowerShell:

```powershell
.\dstr-task2.exe
```

If `make` is not available:

```bash
g++ -std=c++17 main.cpp OrderQueue.cpp RobotCircularQueue.cpp MovementStack.cpp ItemBST.cpp WarehouseTree.cpp -o dstr-task2
```

---

## Things You Must Not Do

1. Do not push directly to main
2. Do not edit other members' files without permission
3. Do not change `common.hpp` without permission
4. Do not change `Makefile` without permission
5. Do not use banned STL containers
6. Do not create another `main()` function
7. Do not commit executable files (`*.exe`, `*.o`, `*.out`)
8. Do not use force push (`git push --force`)
9. Do not make huge commits — commit small logical steps
10. Do not merge your own PR without checking compilation
11. Do not commit local test files (`test_*.cpp`)
