#ifndef MOVEMENTSTACK_HPP
#define MOVEMENTSTACK_HPP

#include "common.hpp"

const int MAX_STEPS = 100;

const int STEP_SIZE = 50;

class MovementStack {

    private:
        //internal fixed-size array to store movement steps
        char steps[MAX_STEPS][STEP_SIZE];

        //index of the top element 
        int top;

    public:

        MovementStack();

        ~MovementStack();

        //returns true if stack has no steps recorded
        bool isEmpty() const;

        //returns num of steps in current stack
        int size() const;

        //push a new movement step onto top of the stack
        //returns false if stack full
        bool push(const char step[]);

        //removes the top step and copies it into the provided buffer
        //returns false if stack empty
        bool pop(char step[]);

        //copies top step into provided buffer without removing it
        //returns false if stack empty
        bool peek(char step[]) const;

        void displayPath() const;

        void returnPath();

        void clearPath();
};

#endif