module timer;

import gameobjectcomponent;
import <string>;

Timer::Timer(int interval, const std::string &event): interval{interval}, count{interval}, event{event} {}

void Timer::tick(){
    count--;
    // When count reaches 0 emit an event
    if(count <= 0){
        reset();
        gameObject->emit(event);
    }
}

void Timer::reset(){
    count = interval;
}
