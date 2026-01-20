export module eventhandler;

import gameobjectcomponent;
import <string>;

export class EventHandler : public Component {
    public:
    virtual void handleEvent(const std::string &event) = 0;
};
