export module pixel;

// Used in BitmapTexture
export class Pixel {
    public:
    int x, y;
    char fill;
    Pixel(const Pixel&) = default;
    Pixel(Pixel&&) = default;
    Pixel& operator=(const Pixel&) = default;
    Pixel& operator=(Pixel&&) = default;
    Pixel(int x, int y, char fill);
};
