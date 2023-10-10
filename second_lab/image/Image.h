//
// Created by k4r3l1ns on 10/9/23.
//

#ifndef UNTITLED3_IMAGE_H
#define UNTITLED3_IMAGE_H

#include <memory>
#include <string>

class Image {

public:
    Image();
    Image(int width, int height, int hChannels);
    Image(const Image&);
    Image(Image&&) noexcept;
    explicit Image(const std::string &path);
    ~Image();

    Image& operator=(const Image&);
    Image& operator=(Image&&) noexcept;

    bool isRead(const std::string &path);
    bool isWrite(const std::string &path);

    void setPixel(int row, int col, int r, int g, int b, int a);
    void getPixel(int row, int col, int& r, int& g, int& b, int& a);
//    void applyFilter(int filter[3][3]);
//    void applyGaussianFilter(int size, double sigma);
//    void applyMedianFilter(int size);
    int getMWidth() const;
    int getMHeight() const;


private:
    int m_width;
    int m_height;
    int m_nChannels;
    int m_size;
    std::unique_ptr<uint8_t[]>m_data;
};


#endif //UNTITLED3_IMAGE_H
