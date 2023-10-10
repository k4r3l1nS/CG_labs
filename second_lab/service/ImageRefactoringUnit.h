//
// Created by k4r3l1ns on 10/9/23.
//

#ifndef SECOND_LAB_IMAGEREFACTORINGUNIT_H
#define SECOND_LAB_IMAGEREFACTORINGUNIT_H

#include "../image/Image.h"

class ImageRefactoringUnit {

public:
    static void applyMedianBlur(Image& image, int size);
    static void applyGaussianBlur(Image& image, int size, double sigma);
};


#endif //SECOND_LAB_IMAGEREFACTORINGUNIT_H
