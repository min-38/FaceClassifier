#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "opencv2/objdetect.hpp"
#include "ImageInfo.h"
#include <vector>

using namespace std;
namespace fs = std::filesystem;
using namespace cv;

bool check_file_valid(const fs::directory_entry &entry) {
    if(!entry.exists()) { // entry가 존재하지 않을 때
        cerr << "Image " << entry.path() << " does not exist" << endl;
        return false;
    }
    if(!entry.is_regular_file()) { // 파일이 아닐 때
        cerr << entry.path() << " is not a file" << endl;
        return false;
    }

    return true;
}

int main(int argc, char *argv[]) {
    fs::path image_dir_path = "../images";

    // 디렉터리가 존재하는지 확인
    if (!fs::exists(image_dir_path))
        cerr << "Image directory does not exist" << endl;

    vector<ImageInfo> images_vector;

    // 디렉터리의 모든 파일 나열하기
    for (const auto& entry : fs::directory_iterator(image_dir_path)) {
        if(!check_file_valid(entry))
            continue;
        Mat img = imread(entry.path());
        ImageInfo image(entry.path().filename().string(), img, entry.file_size());
        images_vector.push_back(image);
    }

    // face detection
    CascadeClassifier cascade, nestedCascade;
    double scale = 1;

    // Load classifiers from "opencv/data/haarcascades" directory
    nestedCascade.load("../xml/haarcascade_eye_tree_eyeglasses.xml");

    // Change path before execution
    cascade.load("../xml/haarcascade_frontalface_alt.xml");

    vector<Rect> faces;
    for (ImageInfo &imgInfo : images_vector) {
        const cv::Mat *image = imgInfo.getImage();
        cascade.detectMultiScale(*image, faces, 1.05, 4);
        for (int i = 0; i < faces.size(); i++) {
            rectangle(*const_cast<Mat*>(image), faces[i].tl(), faces[i].br(), Scalar(0, 0, 244));

            // 탐지된 얼굴 영역을 잘라내는 작업
            Mat processedFace;
            cvtColor(Mat(*image, faces[i]), processedFace, cv::IMREAD_COLOR);

            std::string windowName = imgInfo.getFileName() + " Face " + to_string(i);
            imshow(windowName , processedFace);

            waitKey(1000); // 사용자 입력 대기
            destroyWindow(windowName);
        }
        faces.clear();
    }

    return 0;
}
