export module sprite;
import gameobjectcomponent;
import bitmaptexture;
import boxtexture;
import clonablecomponent;
import <variant>;

export class Sprite: public ClonableComponent<Component, Sprite> {
    public:
    bool visible = true;
    // Raw pointer since textures can be reused
    std::variant<char, BoxTexture*, BitmapTexture*> texture;
    Sprite(char texture);
    Sprite(BitmapTexture *texture);
    Sprite(BoxTexture *texture);
    void setVisibility(bool visible);
    bool getVisibility();
};
