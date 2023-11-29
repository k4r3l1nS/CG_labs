//
// Created by k4r3l1ns on 29.11.23.
//

#ifndef CG_LAB_IMAGE_H
#define CG_LAB_IMAGE_H

#include <vector>

using std::vector;

struct Color {
    float r, g, b, channel;

    Color();
    Color(float r, float g, float b, float channel = 0);
    ~Color();
};



class Image {
private:
    int m_width;
    int m_height;
    vector<Color> m_colors;

public:
    Image(int width, int height);
    ~Image();

    [[nodiscard]] Color getColor(int x, int y) const;
    void setColor(const Color& color, int x, int y);

    void read(const char* path);
    void write(const char* path);

    void rgbToCmy();
    void cmyToRgb();

    void rgbToCmyk();
    void cmykToRgb();

    void rgbToLab();
    void labToRgb();

    void rgbToYCbCr();
    void ycbcrToRgb();

    void showFirstChannel();
    void showSecondChannel();
    void showThirdChannel();
};

#endif //CG_LAB_IMAGE_H
