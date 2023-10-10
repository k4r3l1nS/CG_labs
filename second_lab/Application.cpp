#include <iostream>
#include "image/Image.h"
#include "service/ImageRefactoringUnit.h"
#include <string>

const static int SIZE = 5;
const static double SIGMA = 1.2;
const static std::string IMAGE_DIR_PATH = "../resources";


int main() {

    auto imageEven = Image(IMAGE_DIR_PATH + "/source/filtered/image_even.png");
    auto imageGaussian = Image(IMAGE_DIR_PATH + "/source/filtered/image_even.png");

    ImageRefactoringUnit::applyMedianFilter(imageEven, SIZE);
    ImageRefactoringUnit::applyGaussianFilter(imageGaussian, SIZE, SIGMA);

    imageEven.isWrite( IMAGE_DIR_PATH + "/refactored/refactored_image_even.png");
    imageGaussian.isWrite(IMAGE_DIR_PATH + "/refactored/refactored_image_gaussian.png");

    std::cout << "\nImage refactoring finished!" << std::endl;
    return 0;
}
