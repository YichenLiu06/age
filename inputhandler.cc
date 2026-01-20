export module inputhandler;

import gameobjectcomponent;
import clonablecomponent;

export class InputHandler: public Component {
    public:
    virtual void handleInput(char input) = 0;
};
