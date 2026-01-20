export module bitmaptexture;
import pixel;
import <vector>;

export class BitmapTexture {
    public:
    std::vector<Pixel> pixels;
    void addPixel(Pixel pixel);

    //iterators so that the view can draw all the pixels
    using iterator = std::vector<Pixel>::iterator;
    using const_iterator = std::vector<Pixel>::const_iterator;
    
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};
