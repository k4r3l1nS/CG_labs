cmake_minimum_required(VERSION 3.26)
project(second_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        second_lab Application.cpp
        image/Image.cpp
        service/ImageRefactoringUnit.cpp
)
