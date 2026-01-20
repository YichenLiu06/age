module state;

import <string>;
import <map>;
import <initializer_list>;

State::State(std::initializer_list<std::string> ids){
    for(const std::string &id : ids){
        setData(id, 0);
    }
}

int State::getData(const std::string &id){
    return state.at(id);
}

void State::setData(const std::string &id, int val){
    state[id] = val;
}
