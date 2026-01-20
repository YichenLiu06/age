export module controller;

export class Controller {
    public:
    virtual char getInput() = 0;
    virtual ~Controller() = default;
};
