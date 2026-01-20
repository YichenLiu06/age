module eventqueue;

import <queue>;
import <string>;

void EventQueue::pushEvent(const std::string &event){
    queue.push(event);
}

void EventQueue::popEvent(){
    queue.pop();
}

std::string EventQueue::getNextEvent(){
    return queue.front();
}

bool EventQueue::isEmpty(){
    return queue.empty();
}
