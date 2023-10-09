#include <iostream>
#include "image/Image.h"
#include "service/ImageRefactoringUnit.h"

int main() {

    auto myImage = Image("../resources/image.png");

    ImageRefactoringUnit::applyMedianFilter(myImage, 6);
    myImage.isWrite("../resources/refactored_image.png");

    std::cout << "\nImage refactoring finished!" << std::endl;
    return 0;
}
