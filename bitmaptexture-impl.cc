module bitmaptexture;
import pixel;
import <vector>;

using iterator = std::vector<Pixel>::iterator;
using const_iterator = std::vector<Pixel>::const_iterator;

void BitmapTexture::addPixel(Pixel pixel){
    pixels.push_back(pixel);
}

iterator BitmapTexture::begin(){
    return pixels.begin();
}

iterator BitmapTexture::end(){
    return pixels.end();
}

const_iterator BitmapTexture::begin() const{
    return pixels.begin();
}

const_iterator BitmapTexture::end() const{
    return pixels.end();
}
