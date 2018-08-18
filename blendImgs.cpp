/**
 * @file AddingImages.cpp
 * @brief Simple linear blender ( dst = alpha*src1 + beta*src2 )
 * @author OpenCV team
 */
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <dirent.h>

using namespace cv;

// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using std::string;
/**
 * @function main
 * @brief Main function
 */

static void printImgsDir()
{
  struct dirent *ent;
  DIR *dir;
  if ((dir = opendir ("./images")) != NULL) {
    /* print all the files and directories within images directory */
    while ((ent = readdir (dir)) != NULL) { // iterate through files in dir
      string fileName = ent->d_name;
      if (fileName[0] != '.') { // ignore hidden files
        printf ("%s\n", fileName.c_str());
      } //endif
    } //endwhile
    cout << endl;
    closedir (dir); //end
  } else {
    /* could not open directory */
    perror ("couldn't open image directory");
  }
}

int main(void) {
  double alpha = 0.5;
  double beta;
  double input;
  string file1Src;
  string file2Src;
  string outputName;
  int min_x, min_y;
  Mat src1, src2, dst, out_image;

  /// Ask the user enter alpha
  cout << "* Simple Linear Blender " << endl;
  cout << "-----------------------" << endl;
  cout << "* Enter alpha [0.0-1.0]: ";
  cin >> input;

  // We use the alpha provided by the user if it is between 0 and 1
  if (input >= 0 && input <= 1) {
    alpha = input;
  }

  cout << "  Input first image name from selection below " << endl << endl;
  cout << "  ------------------------------------------- " << endl;

  printImgsDir();

  // input image names
  cout << "  -----------------------   " << endl;
  cin  >> file1Src;

  cout << "  Input second image name  " << endl;
  cout << "  -----------------------   " << endl;
  cin  >> file2Src;

  //![load]
  /// Read images and check user input
  src1 = imread("./images/" + file1Src);
  if (src1.empty()) {
    cout << "Error loading src1" << endl;
    return -1;
  }

  src2 = imread("./images/" + file2Src);
  if (src2.empty()) {
    cout << "Error loading src2" << endl;
    return -1;
  }
  // //![load]

  // Set Rectangles Of Interest for the selected sections of src1 and src2
  Rect roi = Rect(0, 0, src1.cols, src1.rows);
  Mat src1_roi = src1(roi);
  Mat src2_roi = src2(roi);

  out_image = src1_roi.clone();
  beta = (1.0 - alpha);
  // // Blend the ROI of A with B into the ROI of out_image
  addWeighted(src1_roi, alpha, src2_roi, beta, 0.0, out_image);

  // //![recieve output file name]
  cout << "  Input output image name WITHOUT file extension " << endl;
  cout << "  ---------------------------------------------- " << endl;
  cin  >> outputName;

  // //![blend_images]
  namedWindow(outputName, WINDOW_KEEPRATIO);
  imshow(outputName, out_image);
  imwrite("./outputImgs/" + outputName + ".jpg", out_image);
  // //![blend_images]

  waitKey(0);
  return 0;
}
