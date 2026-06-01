#include "MovementStack.hpp"
#include <iostream>
#include <cstring>

using namespace std;

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

bool MovementStack::push(const char step[])
{
    //check if stack full
    if (top >= MAX_STEPS - 1)
    {
        cout << "[MovementStack] Error: Stack is full. Cannot record step \""
            << step << "\"." << endl;
        return false;
    }

    //move top pointer up and copy the step string
    top++;
    strncpy(steps[top], step, STEP_SIZE - 1);
    steps[top][STEP_SIZE - 1] = '\0';

    cout << "[MovemenStack] Step recorded: \"" << steps[top] << "\"" << endl;
    return true;
}

bool MovementStack::pop(char step[])
{
    if (isEmpty())
    {
        cout << "[MovementStack] Error: Stack is empty. No step to remove." << endl;
        return false;
    }

    //copy top step into the output buffer, then decrement top
    strncpy(step, steps[top], STEP_SIZE -1);
    step[STEP_SIZE - 1] = '\0';
    top--;

    return true;
}

bool MovementStack::peek(char step[]) const
{
    if (isEmpty())
    {
        cout << "[MovementStack] Error: Stack is empty. Nothing to peek." << endl;
        return false;
    }

    //copy top step into output buffer
    strncpy(step, steps[top], STEP_SIZE -1);
    step[STEP_SIZE -1] = '\0';

    return true;
}

void MovementStack::displayPath() const 
{
    cout << "\n---Movement Path---" << endl;

    if(isEmpty())
    {
        cout << " (No steps recorded)" << endl;
        cout << "---------------------" << endl;
        return;
    }

    //print from bottom to top for chronological order
    for (int i = 0; i <= top; i++)
    {
        cout << "  Step " << (i + 1) << ": " << steps[i] << endl;
    }

    cout << "---------------------" << endl;
    cout << "Total steps: " << size() << endl;
}

void MovementStack::returnPath()
{
    cout << "\n---Returning---" << endl;

    if (isEmpty())
    {
        cout << "  (No steps to retrace)" << endl;
        cout << "-----------------" << endl;
        return;
    }

    //pop each step and display it as the return route
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

void MovementStack::clearPath()
{
    top = -1;
    cout << "[MovementStack] Path cleared. Stack reset." << endl;
}