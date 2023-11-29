#include "Image.h"

#include <iostream>
#include <fstream>
#include <cmath>

Color::Color(float r, float g, float b, float channel) : r(r), g(g), b(b), channel(channel) {}

Color::Color() : r(0), g(0), b(0), channel(0) {}

Color::~Color() {}

Image::Image(int width, int height) : m_width(width), m_height(height),
                                      m_colors(vector<Color>(width * height)) {}

Image::~Image() {}

Color Image::getColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::setColor(const Color &color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}


void Image::read(const char *path) {
    std::ifstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Файл не найден или не может быть прочитан" << std::endl;
        return;
    }

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;

    unsigned char fileHeader[fileHeaderSize];
    f.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

    if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
        std::cout << "Файл не соответствует формату .bmp\n";
        f.close();
        return;
    }

    unsigned char informationHeader[informationHeaderSize];
    f.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    m_width = informationHeader[4] + (informationHeader[5] << 8) + (
            informationHeader[6] << 16) + (informationHeader[7] << 24);
    m_height = informationHeader[8] + (informationHeader[9] << 8) +
               (informationHeader[10] << 16) + (informationHeader[11] << 24);

    m_colors.resize(m_width * m_height);

    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(paddingAmount);
    }

    f.close();

    std::cout << "Файл успешно считан\n";
}

void Image::write(const char* path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "Файл не найден или не может быть открыт\n";
        return;
    }

    unsigned char bmpPad[3] = { 0, 0, 0};
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int informationHeaderSize = 40;
    const int fileSize = fileHeaderSize + informationHeaderSize +
                         m_width * m_height * 3 + paddingAmount * m_width;

    unsigned char fileHeader[fileHeaderSize];

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    fileHeader[6] = 0;
    fileHeader[7] = 0;

    fileHeader[8] = 0;
    fileHeader[9] = 0;

    fileHeader[10] = fileHeaderSize + informationHeaderSize;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[informationHeaderSize];

    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;

    informationHeader[12] = 1;
    informationHeader[13] = 0;

    informationHeader[14] = 24;
    informationHeader[15] = 0;

    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            unsigned char r = static_cast<unsigned char>(getColor(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(getColor(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(getColor(x, y).b * 255.0f);

            unsigned char color[] = { b, g, r };

            f.write(reinterpret_cast<char*>(color), 3);
        }

        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }

    f.close();

    std::cout << "Файл успешно создан\n";
}

float findMin(Color color) {

    float min = color.r < color.b ? color.r : color.b;
    return min < color.g ? min : color.g;
}

void Image::rgbToCmy() {
    for (int column =0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color col = getColor(row, column);

            float c = 1 - col.r;
            float m = 1 - col.g;
            float y = 1 - col.b;

            setColor(Color(c, m, y), row, column);
        }
    }
}

void Image::cmyToRgb() {
    for (int column =0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color col = getColor(row, column);

            float r = 1 - col.r;
            float g = 1 - col.g;
            float b = 1 - col.b;

            setColor(Color(r, g, b), row, column);
        }
    }
}

void Image::rgbToCmyk() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float c = 1 - color.r;
            float m = 1 - color.g;
            float y = 1 - color.b;

            float k = findMin(color);

            c -= k;
            m -= k;
            y -= k;

            setColor(Color(c, m, y, k), row, column);
        }
    }
}

void Image::cmykToRgb() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float r = (1 - color.r) * (1 - color.channel);
            float g = (1 - color.g) * (1 - color.channel);
            float b = (1 - color.b) * (1 - color.channel);

            setColor(Color(r, g, b), row, column);
        }
    }
}

void Image::rgbToYCbCr() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float y = 0.2989 * color.r + 0.5866 * color.g + 0.1145 * color.b;
            float cb = 0.5*color.r - 0.4184*color.g - 0.0816*color.b;
            float cr = -0.1688*color.r - 0.3312*color.g + 0.5*color.b;

            setColor(Color(y, cr, cb), row, column);
        }
    }
}

void Image::ycbcrToRgb() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float r = color.r + 1.402 * color.b;
            float g = color.r - 0.3441363 * color.b - 0.71413636 * color.b;
            float b = color.r + 1.772 * color.b;

            setColor(Color(r, g, b), row, column);
        }
    }
}

void Image::rgbToLab() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float l = 0.3811 * color.r + 0.5783 * color.g + 0.0402 * color.b;
            float m = 0.1967 * color.r + 0.7244 * color.g + 0.0782 * color.b;
            float s = 0.02461 * color.r + 0.1288 * color.g + 0.844 * color.b;

            setColor(Color(l, m, s), row, column);
        }
    }

    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float l = 0.57741 * (log10f(color.r) + log10f(color.g) + log10f(color.b));
            float alpha = 0.40821 * (log10f(color.r) + log10f(color.g)) - 0.8164 * log10f(color.b);
            float beta = 0.7071 * (log10f(color.r) - log10f(color.g));

            //std::cout << l << " " << alpha << " " << beta << '\n';
            l = l < 0 ? 0 : l;

            setColor(Color(l, alpha, beta), row, column);
        }
    }
}

void Image::labToRgb() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float l = pow(10, 0.5771 * color.r + 0.4082 * color.g + 0.7071 * color.b);
            float m = pow(10, 0.5774 * color.r + 0.4082 * color.g - 0.7071 * color.b);
            float s = pow(10, 0.5774 * color.r - 0.8164 * color.g);

            setColor(Color(l, m, s), row, column);
        }
    }

    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float r = 4.4679 * color.r - 3.5873 * color.g + 0.1193 * color.b;
            float g = -1.2186 * color.r + 2.3809 * color.g - 0.1624 * color.b;
            float b = 0.0497 * color.r - 0.2439 * color.g + 1.2004 * color.b;

            setColor(Color(r, g, b), row, column);
        }
    }
}

void Image::showFirstChannel() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float firstChannel = color.r;
            float secondChannel = color.r;
            float thirdChannel = color.r;

            setColor(Color(firstChannel, secondChannel, thirdChannel), row, column);
        }
    }
}

void Image::showSecondChannel() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float firstChannel = color.g;
            float secondChannel = color.g;
            float thirdChannel = color.g;

            setColor(Color(firstChannel, secondChannel, thirdChannel), row, column);
        }
    }
}

void Image::showThirdChannel() {
    for (int column = 0; column < m_height; column++) {
        for (int row = 0; row < m_width; row++) {
            Color color = getColor(row, column);

            float firstChannel = color.b;
            float secondChannel = color.b;
            float thirdChannel = color.b;

            setColor(Color(firstChannel, secondChannel, thirdChannel), row, column);
        }
    }
}
