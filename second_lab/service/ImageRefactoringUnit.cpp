//
// Created by k4r3l1ns on 10/9/23.
//

#include "ImageRefactoringUnit.h"
#include <vector>
#include <cmath>
#include <algorithm>

void ImageRefactoringUnit::applyGaussianFilter(Image& image, int size, double sigma)
{
    sigma = std::abs(sigma) > 2.0 ? 2.0 : sigma;

    std::vector<std::vector<double>> filter(size, std::vector<double>(size));
    double sum = 0.0;
    int start = size / 2;
    for (int x = -start; x <= start; x++) {
        for (int y = -start; y <= start; y++) {
            filter[x + start][y + start] =
                    exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += filter[x + start][y + start];
        }
    }
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            filter[i][j] /= sum;

    Image copy(image);
    int m_height = image.getMHeight();
    int m_width = image.getMWidth();
    for (int y = start; y < m_height - start; y++) {
        for (int x = start; x < m_width - start; x++) {
            double r = 0, g = 0, b = 0, a = 0;
            for (int i = -start; i <= start; ++i) {
                for (int j = -start; j <= start; ++j) {
                    int rr, gg, bb, aa;
                    copy.getPixel(y + i, x + j, rr, gg, bb, aa);
                    r += rr * filter[i + start][j + start];
                    g += gg * filter[i + start][j + start];
                    b += bb * filter[i + start][j + start];
                    a += aa * filter[i + start][j + start];
                }
            }
            image.setPixel(y, x, static_cast<int>(r), static_cast<int>(g), static_cast<int>(b), static_cast<int>(a));
        }
    }
}

void ImageRefactoringUnit::applyMedianFilter(Image& image, int size)
{
    Image copy(image);
    std::vector<int> rValues, gValues, bValues, aValues;

    int m_height = image.getMHeight();
    int m_width = image.getMWidth();
    for (int y = size / 2; y < m_height - size / 2; y++) {
        for (int x = size / 2; x < m_width - size / 2; x++) {
            rValues.clear();
            gValues.clear();
            bValues.clear();
            aValues.clear();

            for (int i = -size / 2; i <= size / 2; ++i) {
                for (int j = -size / 2; j <= size / 2; ++j) {
                    int rr, gg, bb, aa;
                    copy.getPixel(y + i, x + j, rr, gg, bb, aa);
                    rValues.push_back(rr);
                    gValues.push_back(gg);
                    bValues.push_back(bb);
                    aValues.push_back(aa);
                }
            }

            std::sort(rValues.begin(), rValues.end());
            std::sort(gValues.begin(), gValues.end());
            std::sort(bValues.begin(), bValues.end());
            std::sort(aValues.begin(), aValues.end());

            image.setPixel(y, x, rValues[rValues.size() / 2], gValues[gValues.size() / 2],
                           bValues[bValues.size() / 2], aValues[aValues.size() / 2]);
        }
    }
}