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

## File Creation Rules

Each member must create their own `.hpp` and `.cpp` files.

For example:

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

Examples:

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

For the next task, create a new branch from the latest `main`.

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
□ My code compiles successfully.
□ My commit message is clear.
```

---

## Standard GitHub Workflow

All members must follow this workflow when working on their assigned module.

---

### 1. Open VS Code terminal and move to the project folder

Open the terminal in VS Code and move to the local project folder.

```bash
cd path/to/your/project-folder
```

Example:

```bash
cd "C:\Users\Shunto's Device\OneDrive - Asia Pacific University of Technology And Innovation (APU)\APU CYB One Drive\D2-2 One Drive\Data Structures\Data-Structure-Task2"
```

Check that you are inside the correct Git project:

```bash
git status
```

---

### 2. Check GitHub remote connection

Before starting work, check that the local repository is connected to GitHub.

```bash
git remote -v
```

Expected result:

```text
origin  https://github.com/shunshun29/Data-Structure-task2.git (fetch)
origin  https://github.com/shunshun29/Data-Structure-task2.git (push)
```

If no remote is shown, run:

```bash
git remote add origin https://github.com/shunshun29/Data-Structure-task2.git
```

---

### 3. Move to the main branch

Before starting new work, always move to the `main` branch.

```bash
git checkout main
```

---

### 4. Pull the latest code from GitHub main branch

Get the newest version of the project from GitHub.

```bash
git pull origin main
```

This makes sure your local `main` branch is up to date.

---

### 5. Create your own working branch

Create a new feature branch for your task.

```bash
git checkout -b feature/your-task-name
```

Examples:

```bash
git checkout -b feature/order-management
```

```bash
git checkout -b feature/robot-assignment
```

```bash
git checkout -b feature/navigation-stack
```

```bash
git checkout -b feature/item-management
```

```bash
git checkout -b feature/warehouse-layout
```

Check that you are on the correct branch:

```bash
git branch
```

Example result:

```text
  main
* feature/order-management
```

The branch with `*` is your current branch.

---

### 6. Coding

Work only on your assigned `.hpp` and `.cpp` files.

Examples:

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

Do not edit `main.cpp`, `common.hpp`, or `Makefile` without the leader's permission.

---

### 7. Check changed files

After coding, check which files were changed.

```bash
git status
```

You can also check the detailed changes:

```bash
git diff
```

---

### 8. Add changed files

Add only the files that you intentionally changed.

```bash
git add file-name
```

Example:

```bash
git add OrderQueue.hpp OrderQueue.cpp
```

Avoid using this unless you are sure:

```bash
git add .
```

`git add .` adds all changed files, including files you may not want to commit.

---

### 9. Commit your changes

Commit the added files with a clear message.

```bash
git commit -m "Clear commit message"
```

Examples:

```bash
git commit -m "Implement order queue module"
```

---

### 10. Push your working branch to GitHub

Push your feature branch to GitHub.

```bash
git push -u origin feature/your-task-name
```

Example:

```bash
git push -u origin feature/order-management
```

After the first push, you can usually use:

```bash
git push
```

---

### 11. Move to the browser and create a Pull Request

After pushing, open the GitHub repository in your browser.

Steps:

```text
GitHub repository
↓
Compare & pull request
↓
Write Pull Request title and description
↓
Create pull request
```

Pull Request title example:

```text
Implement order queue module
```

Pull Request description example:

```md
## Summary

Implemented the Order Management module using a custom Queue.

## Changes

- Added OrderQueue.hpp
- Added OrderQueue.cpp
- Implemented enqueue, dequeue, peek, and display functions

## Data Structure

- Custom Queue using linked nodes

## Checklist

- [x] I worked on my own feature branch
- [x] I did not edit main directly
- [x] I did not change common.hpp without permission
- [x] I did not use STL containers
- [x] I did not define another main() function
- [x] My code compiles
```

---

### 12. Leader checks and approves the Pull Request

The team leader checks the Pull Request.

The leader checks:

```text
- The member worked on the correct files
- The code does not use banned STL containers
- The code includes common.hpp
- The code does not contain another main() function
- The code compiles successfully
- The data structure is implemented manually
- The member can explain their data structure choice
```

Members must not merge their own Pull Requests.

Only the leader is allowed to approve and merge Pull Requests.

---

### 13. Leader merges the Pull Request

If there are no problems, the leader merges the Pull Request into `main`.

Steps on GitHub:

```text
Pull Request page
↓
Check Files changed
↓
Check if there are conflicts
↓
Merge pull request
↓
Confirm merge
```

After merging, delete the feature branch on GitHub if it is no longer needed.

---

### 14. After the Pull Request is merged

Each member should update their local `main` branch.

```bash
git checkout main
git pull origin main
```

Then delete the local feature branch everytime the task is finished.

```bash
git branch -d feature/your-task-name
```

Example:

```bash
git branch -d feature/order-management
```

---

## Git Commands to Remember

### 1. Check current branch

```bash
git branch
```

This shows all local branches.

The branch with `*` is the branch you are currently using.

Example:

```text
  main
* feature/order-management
```

This means you are currently working on `feature/order-management`.

---

### 2. Move to main branch

```bash
git checkout main
```

This moves you to the `main` branch.

Use this before pulling the latest version or creating a new branch.

---

### 3. Get the latest main from GitHub

```bash
git pull origin main
```

This updates your local `main` branch with the latest version from GitHub.

Always do this before creating a new feature branch.

---

### 4. Create a new feature branch

```bash
git checkout -b feature/branch-name
```

Example:

```bash
git checkout -b feature/order-management
```

This creates a new branch and moves you into it.

---

### 5. Check changed files

```bash
git status
```

This shows which files have been changed, added, or deleted.

Use this before every commit.

---

### 6. Check detailed changes

```bash
git diff
```

This shows the exact changes made in the files.

Use this before adding files to commit. To exit, enter 'q'.

---

### 7. Add files to commit

```bash
git add file-name
```

Example:

```bash
git add OrderQueue.hpp OrderQueue.cpp
```

Avoid using this unless you are sure:

```bash
git add .
```

`git add .` adds all changed files, including files you may not want to commit.

---

### 8. Commit changes

```bash
git commit -m "message"
```

Example:

```bash
git commit -m "Implement order queue module"
```

A commit saves your changes locally.


### 9. Push branch to GitHub

```bash
git push -u origin feature/branch-name
```

Example:

```bash
git push -u origin feature/order-management
```

This sends your local branch to GitHub.

After pushing, create a Pull Request on GitHub.

---

### 10. Update your feature branch with latest main

If `main` has been updated while you are working, run:

```bash
git checkout main
git pull origin main
git checkout feature/branch-name
git merge main
```

Example:

```bash
git checkout main
git pull origin main
git checkout feature/order-management
git merge main
```

This reduces the risk of conflicts.

---

### 11. Delete a local branch after merge

After your Pull Request is merged, move to main:

```bash
git checkout main
git pull origin main
```

Then delete the local feature branch:

```bash
git branch -d feature/branch-name
```

Example:

```bash
git branch -d feature/order-management
```

If Git says the branch is not merged but you are sure it is no longer needed:

```bash
git branch -d feature/branch-name
```

Be careful: `-D` force deletes the branch.

---

### 12. Delete a remote branch on GitHub

```bash
git push origin --delete feature/branch-name
```

Example:

```bash
git push origin --delete feature/order-management
```

Usually, after merging a Pull Request, GitHub also shows a `Delete branch` button.  
Using that button is the easiest way.

---

## Standard Workflow for Members

Each member should follow this workflow:

```bash
git checkout main
git pull origin main
git checkout -b feature/your-task-name
```

Then work on your files.

After finishing:

```bash
git status
git add your-file.hpp your-file.cpp
git commit -m "Clear commit message"
git push -u origin feature/your-task-name
```

Then create a Pull Request on GitHub.

---

## Standard Workflow for the Leader

The leader reviews Pull Requests on GitHub.

Before merging, check:

```text
□ The PR only changes the correct files.
□ The code does not use banned STL containers.
□ The code includes common.hpp.
□ There is no extra main() function.
□ The code compiles.
□ The data structure is manually implemented.
□ The member can explain the data structure choice.
```

After checking, the leader merges the Pull Request into `main`.

---

## Things You Must Not Do

### 1. Do not push directly to main

Do not do this:

```bash
git checkout main
git push origin main
```

All changes must go through Pull Requests.

---

### 2. Do not edit other members' files without permission

Each member should only edit their own files.

Example:

```text
Order member:
- OrderQueue.hpp
- OrderQueue.cpp

Robot member:
- RobotCircularQueue.hpp
- RobotCircularQueue.cpp
```

Do not edit another member's files without discussing it first.

---

### 3. Do not change common.hpp without permission

`common.hpp` is shared by all modules.

Changing it can break everyone else's code.

Only the leader should manage this file.

---

### 4. Do not change Makefile without permission

`Makefile` controls compilation.

If it is changed incorrectly, the whole project may fail to compile.

Only the leader should manage this file.

---

### 5. Do not use banned STL containers

Do not use:

```cpp
vector
list
queue
stack
map
set
```

Each data structure must be implemented manually.

---

### 6. Do not create another main() function

Only `main.cpp` should contain:

```cpp
int main()
```

Module files should not contain `main()`.

---

### 7. Do not commit executable files

Do not commit files such as:

```text
warehouse
warehouse.exe
*.o
*.out
*.exe
```

These should be ignored by `.gitignore`.

---

### 8. Do not use force push

Do not use:

```bash
git push --force
```

This can overwrite other people's work.

---

### 9. Do not make huge commits

Avoid committing everything at once.

Bad:

```bash
git commit -m "finish everything"
```

Good:

```bash
git commit -m "Add queue node structure"
git commit -m "Implement enqueue function"
git commit -m "Implement dequeue function"
```

Small commits are easier to review and fix.

---

### 10. Do not merge your own PR without checking compilation

Before merging, always compile and test the project.

Example:

```bash
make
./warehouse
```

If `make` is not available:

```bash
g++ -std=c++17 main.cpp OrderQueue.cpp RobotCircularQueue.cpp MovementStack.cpp ItemBST.cpp WarehouseTree.cpp -o dstr-task2
./warehouse
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

Run:

```bash
./dstr-task2
```

or on Windows:

```powershell
.\dstr-task2.exe
```

---


