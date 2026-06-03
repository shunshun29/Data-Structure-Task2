#ifndef MOVEMENTSTACK_HPP
#define MOVEMENTSTACK_HPP

#include "common.hpp"

const int MAX_STEPS = 100;                   // max number of steps the stack can hold
const int STEP_SIZE = MAX_LOCATION_LENGTH;   // must match warehouse location name limit

// custom stack for recording robot movement steps
// uses a fixed-size array, top starts at -1 (empty)
class MovementStack {

    private:
        char steps[MAX_STEPS][STEP_SIZE];  // stores each movement step
        int top;                            // index of the topmost step

    public:

        MovementStack();
        ~MovementStack();

        bool isEmpty() const;
        int size() const;

        bool push(const char step[]);  // add a step to the top, returns false if full
        bool pop(char step[]);         // remove the top step, returns false if empty
        bool peek(char step[]) const;  // view the top step without removing it

        void displayPath() const;  // print all steps from first to last
        void returnPath();         // pop and print steps in reverse to trace back
        void clearPath();          // reset the stack
};

#endif
