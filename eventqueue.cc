export module eventqueue;

import <queue>;
import <string>;

export class EventQueue {
    std::queue<std::string> queue;
    public:
    void pushEvent(const std::string &event);
    void popEvent();
    std::string getNextEvent();
    bool isEmpty();
};
