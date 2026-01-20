export module boxtexture;

export class BoxTexture {
    public:
    // Dimensions of BoxTexture
    double top, bottom, right, left;
    // The ASCII character that fills the box when drawn in view
    char fill;
    BoxTexture(double left, double right, double top, double bottom, char fill);
};
