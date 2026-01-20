export module view;
import sprite;
import <string>;

export class View {
    public:
    virtual bool isInView(int x, int y) = 0;
    virtual bool isInView(double x, double y, Sprite *sprite) = 0;
    virtual void drawSprite(double x, double y, Sprite* sprite) = 0;
    virtual void drawText(int line, const std::string &msg) = 0;
    virtual void clearSprites() = 0;
    virtual void clearText() = 0;
    virtual ~View() = default;
};
