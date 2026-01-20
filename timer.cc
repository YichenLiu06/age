export module timer;

import gameobjectcomponent;
import clonablecomponent;
import <string>;

// Used for implementing logic that executes based on a fixed time interval
export class Timer: public ClonableComponent<Component, Timer> {
    // Number of ticks that the timer waits for
    const int interval;
    // Number of ticks left before next event
    int count;
    // The event to emit when count reaches 0
    std::string event;
    public:
    Timer(int interval, const std::string &event);
    // Called on every tick
    void tick();
    // Resets count
    void reset();
};
