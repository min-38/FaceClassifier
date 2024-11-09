#ifndef IMAGEINFO_H
#define IMAGEINFO_H

#include <string>
#include <opencv2/core/mat.hpp>

class ImageInfo {
private:
    std::string name; // 이미지 파일명
    cv::Mat image; // 이미지 2차원 행렬
    uintmax_t size; // 파일 크기
    cv::Rect_<int>* face; // 얼굴
public:
    ImageInfo(const std::string &name, const cv::Mat &image, uintmax_t size);
    // ~ImageInfo();

    // Getter
    const cv::Mat *getImage() const; // 이미지 리턴
    const std::string getFileName();

    // Setter
    void setFace(cv::Rect_<int> *face); // 얼굴 지정
};

#endif //IMAGEINFO_H
