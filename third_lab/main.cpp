#include "Image.h"
#include <cmath>
#include <string>

void writeCmyImages();
void writeCmykImages();
void writeLabImages();
void writeYcbcrImages();

const static int m_width = 200;
const static int m_height = 200;

int main() {

    writeCmyImages();
    writeCmykImages();
    writeLabImages();
    writeYcbcrImages();

    return 0;
}

void writeCmyImages() {

    Image image(m_width, m_height);
    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmy();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmy/image_cmy.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmy();
    image.showFirstChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmy/first_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmy();
    image.showSecondChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmy/second_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmy();
    image.showThirdChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmy/third_channel.bmp");
}

void writeCmykImages() {

    Image image(m_width, m_height);
    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmyk();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmyk/image_cmyk.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmyk();
    image.showFirstChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmyk/first_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmyk();
    image.showSecondChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmyk/second_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToCmyk();
    image.showThirdChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/cmyk/third_channel.bmp");
}

void writeLabImages() {

    Image image(m_width, m_height);
    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToLab();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/lab/image_lab.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToLab();
    image.showFirstChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/lab/first_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToLab();
    image.showSecondChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/lab/second_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToLab();
    image.showThirdChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/lab/third_channel.bmp");
}

void writeYcbcrImages() {

    Image image(m_width, m_height);
    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToYCbCr();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/ycbcr/image_ycbcr.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToYCbCr();
    image.showFirstChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/ycbcr/first_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToYCbCr();
    image.showSecondChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/ycbcr/second_channel.bmp");

    image.read("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/image.bmp");
    image.rgbToYCbCr();
    image.showThirdChannel();
    image.write("/home/k4r3l1ns/Desktop/CG_labs/third_lab/resources/ycbcr/third_channel.bmp");
}


