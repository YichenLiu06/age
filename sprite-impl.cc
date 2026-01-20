module sprite;
import gameobjectcomponent;
import boxtexture;
import bitmaptexture;
import <variant>;

Sprite::Sprite(char texture): texture{texture} {}
Sprite::Sprite(BoxTexture *texture): texture{texture} {}
Sprite::Sprite(BitmapTexture *texture): texture{texture} {}

void Sprite::setVisibility(bool visible){
    this->visible = visible;
}

bool Sprite::getVisibility(){
    return this->visible;
}
