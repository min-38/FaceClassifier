#include <iostream>
#include <filesystem>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
namespace fs = std::filesystem;
using namespace cv;

int main(int argc, char *argv[]) {
    fs::path image_dir_path = "../images";

    // 디렉터리가 존재하는지 확인
    if (!fs::exists(image_dir_path))
        cerr << "Image directory does not exist" << endl;

    // 디렉터리의 모든 파일 나열하기
    for (const auto& entry : fs::directory_iterator(image_dir_path)) {
        imshow( entry.path(), imread( entry.path(), IMREAD_COLOR));
        waitKey(1000); // 1초마다 사진 띄우기
    }

    return 0;
}
