#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "../lib/stb_image.h"
#include "../lib/stb_image_write.h"
#include <vector>
#include <stdexcept>
#include <iostream>

Image::Image()
{
    this->m_height = 0;
    this->m_width = 0;
    this->m_size = 0;
    this->m_nChannels = 0;
    this->m_data = nullptr;
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

[[maybe_unused]] Image::Image(Image && obj) noexcept
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
    if (!read(path))
        throw std::runtime_error("Ошибка считывания фотографии");
}

Image::~Image() = default;

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

bool Image::read(const std::string & path)
{
    try {
        m_data.reset(stbi_load(path.c_str(), &m_width, &m_height, &m_nChannels, 0));
        if (m_data)
            m_size = m_width * m_height * m_nChannels;
        return true;
    } catch (const std::exception& ex) {
        std::cerr << ex.what();
        return false;
    }
}

bool Image::save(const std::string & path)
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
