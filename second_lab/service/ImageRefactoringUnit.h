//
// Created by k4r3l1ns on 10/9/23.
//

#ifndef SECOND_LAB_IMAGEREFACTORINGUNIT_H
#define SECOND_LAB_IMAGEREFACTORINGUNIT_H

#include "../image/Image.h"

class ImageRefactoringUnit {

public:
    static void applyGaussianFilter(Image& image, int size, double sigma);
    static void applyMedianFilter(Image& image, int size);
};


#endif //SECOND_LAB_IMAGEREFACTORINGUNIT_H
