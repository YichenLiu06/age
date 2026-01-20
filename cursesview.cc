export module cursesview;
import view;
import sprite;
import <vector>;
import <string>;

export class CursesView: public View {
    int height, width, maxLines;
    public:
    CursesView(int width, int height, int maxLines = 3);
    bool isInView(int x, int y) override;
    bool isInView(double x, double y, Sprite* sprite) override;
    void drawSprite(double x, double y, Sprite* sprite) override;
    void drawText(int line, const std::string &msg) override;
    void clearSprites() override;
    void clearText() override;
};
