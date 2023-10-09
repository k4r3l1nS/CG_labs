#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"
#include <vector>
#include <stdexcept>

Image::Image()
{
    this->m_height = 0;
    this->m_width = 0;
    this->m_size = 0;
    this->m_nChannels = 0;
    this->m_data = nullptr;
}

Image::Image(const int width, const int height, const int m_nChannels)

{
    this->m_height = height;
    this->m_width = width;
    this->m_nChannels = m_nChannels;
    m_data = std::make_unique<uint8_t[]>(m_size);
}

Image::Image(const Image & obj)
{
    this->m_height = obj.m_height;
    this->m_width = obj.m_width;
    this->m_size = obj.m_size;
    this->m_nChannels = obj.m_nChannels;

    this->m_data = std::make_unique<uint8_t[]>(m_size);
    for (int i = 0; i < m_size; i++) {
        m_data[i] = obj.m_data[i];
    }
}

Image::Image(Image && obj) noexcept
{
    m_height = obj.m_height;
    m_width = obj.m_width;
    m_size = obj.m_size;
    m_nChannels = obj.m_nChannels;
    m_data = std::move(obj.m_data);

    obj.m_data = nullptr;
}

Image::Image(const std::string &path) : Image()
{
    if (!isRead(path))
        throw std::runtime_error("Ошибка считывания фотографии");
}

Image::~Image()
{
}

Image &Image::operator=(const Image & obj)
{
    this->m_height = obj.m_height;
    this->m_width = obj.m_width;
    this->m_size = obj.m_size;
    this->m_nChannels = obj.m_nChannels;

    this->m_data = std::make_unique<uint8_t[]>(m_size);
    for (int i = 0; i < m_size; i++) {
        m_data[i] = obj.m_data[i];
    }
    return *this;
}

Image & Image::operator=(Image && obj) noexcept
{
    if (&obj == this)
        return *this;

    m_height = obj.m_height;
    m_width = obj.m_width;
    m_size = obj.m_size;
    m_nChannels = obj.m_nChannels;
    m_data = std::move(obj.m_data);

    obj.m_data = nullptr;

    return *this;
}

bool Image::isRead(const std::string & path)
{
    m_data.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_nChannels, 0));
    if (m_data)
        m_size = m_width * m_height*m_nChannels;
    return true;
}

bool Image::isWrite(const std::string & path)
{
    return stbi_write_png(path.c_str(),m_width,m_height,m_nChannels,m_data.get(),0);
}

void Image::setPixel(const int row, const int col, const int r, const int g, const int b, const int a)
{
    int index = (row * m_width + col) * m_nChannels;

    m_data[index] = static_cast<uint8_t>(r);
    m_data[index + 1] = static_cast<uint8_t>(g);
    m_data[index + 2] = static_cast<uint8_t>(b);
    if (m_nChannels == 4)
        m_data[index + 3] = static_cast<uint8_t>(a);
}

void Image::getPixel(const int row, const int col, int & r, int & g, int & b, int & a)
{
    int index = (row * m_width + col) * m_nChannels;

    r = m_data[index];
    g = m_data[index + 1];
    b = m_data[index + 2];
    if (m_nChannels == 4)
        a = m_data[index + 3];
    else
        a = 255;
}

int Image::getMWidth() const {
    return m_width;
}

int Image::getMHeight() const {
    return m_height;
}

//void Image::applyFilter(int filter[3][3]) {
//    Image copy(*this);
//    int filterDivisor = 16; // ����������� ��� �������� � ������������ � ����� ��������
//
//    for (int y = 1; y < m_height - 1; y++) {
//        for (int x = 1; x < m_width - 1; x++) {
//            int r = 0, g = 0, b = 0, a = 0;
//
//            for (int dy = -1; dy <= 1; dy++) {
//                for (int dx = -1; dx <= 1; dx++) {
//                    int rr, gg, bb, aa;
//                    copy.getPixel(y + dy, x + dx, rr, gg, bb, aa);
//                    int filterValue = filter[dy + 1][dx + 1];
//
//                    r += rr * filterValue;
//                    g += gg * filterValue;
//                    b += bb * filterValue;
//                    a += aa * filterValue;
//                }
//            }
//
//            r /= filterDivisor;
//            g /= filterDivisor;
//            b /= filterDivisor;
//            a /= filterDivisor;
//
//            setPixel(y, x, r, g, b, a);
//        }
//    }
//}

//void Image::applyGaussianFilter(int size, double sigma) {
//    // ������� ���� �������
//    std::vector<std::vector<double>> filter(size, std::vector<double>(size));
//    double sum = 0.0;
//    int start = size / 2;
//    for (int x = -start; x <= start; x++) {
//        for (int y = -start; y <= start; y++) {
//            filter[x + start][y + start] = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * 3.14159265 * sigma * sigma);
//            sum += filter[x + start][y + start];
//        }
//    }
//    // ����������� ����
//    for (int i = 0; i < size; ++i)
//        for (int j = 0; j < size; ++j)
//            filter[i][j] /= sum;
//
//    // ��������� ������ � �����������
//    Image copy(*this);
//    for (int y = start; y < m_height - start; y++) {
//        for (int x = start; x < m_width - start; x++) {
//            double r = 0, g = 0, b = 0, a = 0;
//            for (int i = -start; i <= start; ++i) {
//                for (int j = -start; j <= start; ++j) {
//                    int rr, gg, bb, aa;
//                    copy.getPixel(y + i, x + j, rr, gg, bb, aa);
//                    r += rr * filter[i + start][j + start];
//                    g += gg * filter[i + start][j + start];
//                    b += bb * filter[i + start][j + start];
//                    a += aa * filter[i + start][j + start];
//                }
//            }
//            setPixel(y, x, static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
//        }
//    }
//}

//void Image::applyMedianFilter(int size) {
//    Image copy(*this);
//    std::vector<int> rValues, gValues, bValues, aValues;
//
//    for (int y = size / 2; y < m_height - size / 2; y++) {
//        for (int x = size / 2; x < m_width - size / 2; x++) {
//            rValues.clear();
//            gValues.clear();
//            bValues.clear();
//            aValues.clear();
//
//            for (int i = -size / 2; i <= size / 2; ++i) {
//                for (int j = -size / 2; j <= size / 2; ++j) {
//                    int rr, gg, bb, aa;
//                    copy.getPixel(y + i, x + j, rr, gg, bb, aa);
//                    rValues.push_back(rr);
//                    gValues.push_back(gg);
//                    bValues.push_back(bb);
//                    aValues.push_back(aa);
//                }
//            }
//
//            std::sort(rValues.begin(), rValues.end());
//            std::sort(gValues.begin(), gValues.end());
//            std::sort(bValues.begin(), bValues.end());
//            std::sort(aValues.begin(), aValues.end());
//
//            setPixel(y, x, rValues[rValues.size() / 2], gValues[gValues.size() / 2], bValues[bValues.size() / 2], aValues[aValues.size() / 2]);
//        }
//    }
//}
