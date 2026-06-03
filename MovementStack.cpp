#include "MovementStack.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// top = -1 means the stack is empty
MovementStack::MovementStack()
{
    top = -1;
}

MovementStack::~MovementStack(){}

bool MovementStack::isEmpty() const
{
    return top == -1;
}

int MovementStack::size() const
{
    return top + 1;
}

// add a step to the top of the stack
bool MovementStack::push(const char step[])
{
    if (top >= MAX_STEPS - 1)
    {
        cout << "[MovementStack] Error: Stack is full. Cannot record step \""
            << step << "\"." << endl;
        return false;
    }

    top++;
    strncpy(steps[top], step, STEP_SIZE - 1);
    steps[top][STEP_SIZE - 1] = '\0';

    cout << "[MovementStack] Step recorded: \"" << steps[top] << "\"" << endl;
    return true;
}

// remove the top step and copy it into the output buffer
bool MovementStack::pop(char step[])
{
    if (isEmpty())
    {
        cout << "[MovementStack] Error: Stack is empty. No step to remove." << endl;
        return false;
    }

    strncpy(step, steps[top], STEP_SIZE - 1);
    step[STEP_SIZE - 1] = '\0';
    top--;

    return true;
}

// copy the top step to the buffer without removing it
bool MovementStack::peek(char step[]) const
{
    if (isEmpty())
    {
        cout << "[MovementStack] Error: Stack is empty. Nothing to peek." << endl;
        return false;
    }

    strncpy(step, steps[top], STEP_SIZE - 1);
    step[STEP_SIZE - 1] = '\0';

    return true;
}

// print from bottom to top so it shows the path in the order it was travelled
void MovementStack::displayPath() const
{
    cout << "\n---Movement Path---" << endl;

    if(isEmpty())
    {
        cout << " (No steps recorded)" << endl;
        cout << "---------------------" << endl;
        return;
    }

    for (int i = 0; i <= top; i++)
    {
        cout << "  Step " << (i + 1) << ": " << steps[i] << endl;
    }

    cout << "---------------------" << endl;
    cout << "Total steps: " << size() << endl;
}

// pop each step one by one to print the return path in reverse
void MovementStack::returnPath()
{
    cout << "\n---Returning---" << endl;

    if (isEmpty())
    {
        cout << "  (No steps to retrace)" << endl;
        cout << "-----------------" << endl;
        return;
    }

    char currentStep[STEP_SIZE];
    int stepNumber = 1;

    while (!isEmpty())
    {
        pop(currentStep);
        cout << "  Step " << stepNumber << ": " << currentStep << endl;
        stepNumber++;
    }

     cout << "-----------------" << endl;
     cout << "Robot has returned to starting point." << endl;
}

// reset by moving top back to -1, no need to clear the array
void MovementStack::clearPath()
{
    top = -1;
    cout << "[MovementStack] Path cleared. Stack reset." << endl;
}
