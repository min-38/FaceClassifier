cmake_minimum_required(VERSION 3.29)
project(ImageClassifier)

set(CMAKE_CXX_STANDARD 20)

# OpenCV 패키지를 찾기
find_package(OpenCV REQUIRED)

add_executable(FaceSearch main.cpp)

# OpenCV 라이브러리 링크
target_link_libraries(FaceSearch ${OpenCV_LIBS})