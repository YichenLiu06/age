export module state;

import clonablecomponent;
import gameobjectcomponent;
import <map>;
import <string>;
import <initializer_list>;

export class State: public ClonableComponent<Component, State> {
    std::map<std::string, int> state;
    public:
    State(std::initializer_list<std::string> ids);
    int getData(const std::string &id);
    void setData(const std::string &id, int value);
};
