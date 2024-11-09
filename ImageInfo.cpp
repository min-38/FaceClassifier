#include "ImageInfo.h"

ImageInfo::ImageInfo(const std::string &name, const cv::Mat &image, uintmax_t size): face(nullptr) {
    this->name = name;
    this->image = image;
    this->size = size;
}

const cv::Mat *ImageInfo::getImage() const {
    return &image;
}
const std::string ImageInfo::getFileName() {
    return name;
}
void ImageInfo::setFace(cv::Rect_<int> *face) {
    this->face = face;
}