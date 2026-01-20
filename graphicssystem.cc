export module graphicssystem;
import view;
import sprite;
import gameobjectcomponent;
import textstatus;
import <vector>;
import <string>;
import <memory>;

export class GraphicsSystem {
    std::vector<std::unique_ptr<View>> views;
    const TextStatus &textStatus;
    public:
    GraphicsSystem(TextStatus &textStatus);
    void addView(std::unique_ptr<View> view);
    void removeView(View *view);
    void update(const std::vector<std::unique_ptr<GameObject>> &gameObjects);
};
