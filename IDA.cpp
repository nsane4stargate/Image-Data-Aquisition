#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

void contrast(Mat*, Mat&, int*, ostringstream*);
void smoothing(Mat*, Mat&, int*, ostringstream*);
void edgeDetection(Mat *, int*, ostringstream*);

int main() {
	int contrast_value = 5, median_filter_kernel = 9, edge_detection_frame_counts = 5;

	/* Loading video file */
	VideoCapture cap("C:/Users/nsane/Documents/Spring '19/CSC528 Computer Vision/Pictures/street.mp4");

	/* Check to see if file opened */
	if (!cap.isOpened()) {
		printf("Error opening video stream or file");
	}
	
	while(true) {
		Mat frame, edited_image;
		ostringstream numstr;
		/* Capture frame-by-frame */
		cap >> frame;

		/* Condition to break when frame is empty */
		if (frame.empty()) {
			break;
		}


		if (contrast_value > 0) {
			contrast(&frame, edited_image, &contrast_value,&numstr);
			contrast_value--;
			numstr.str("");
			numstr.clear();
		}
		if (median_filter_kernel > 0) {
			smoothing(&frame, edited_image, &median_filter_kernel,&numstr);
			median_filter_kernel--;
			if (median_filter_kernel % 2 == 0) {
				median_filter_kernel --;
			}
			numstr.str("");
			numstr.clear();
		}
		if (edge_detection_frame_counts > 0) {
			edgeDetection(&frame, &edge_detection_frame_counts, &numstr);
			edge_detection_frame_counts--;
			numstr.str("");
			numstr.clear();
		}
			
		/* Display window and frame */
		String window_name = "Street";
		namedWindow(window_name, WINDOW_NORMAL);
		imshow(window_name, frame);

		/* Condition to break if ESC key is pressed */
		char c = (char)waitKey(25);
		if(c == 27){
			printf("Stopping video by user's request ");
				break;
		}

	}
	/* Release video capture */
	cap.release();

	/* Close frames */
	destroyAllWindows();
	return(0);
}

void contrast(Mat *original, Mat& contrast_image, int* contrast_value, ostringstream* numstr) {
	String writeout_name = "C:/Users/nsane/Documents/Spring '19/CSC528 Computer Vision/Pictures/Assignment_2/";
	original->convertTo(contrast_image, -1, *contrast_value, 0);
	*numstr << *contrast_value;
	writeout_name += "Contrast value of "; writeout_name += numstr->str(); writeout_name += ".jpg";
	imwrite(writeout_name.c_str(), contrast_image);
}

void smoothing(Mat *original, Mat& smoothing_image, int *kernal_size, ostringstream* numstr){
	medianBlur(*original, smoothing_image, *kernal_size);
	String writeout_name = "C:/Users/nsane/Documents/Spring '19/CSC528 Computer Vision/Pictures/Assignment_2/";
	*numstr << *kernal_size;
	writeout_name += "Median Filter Smoothing with Kernal Size of "; writeout_name += numstr->str(); writeout_name += ".jpg";
	imwrite(writeout_name.c_str(), smoothing_image);
}

void edgeDetection(Mat *original, int *count, ostringstream* numstr) {
	Mat greyscale, canny_image;
	cvtColor(*original, greyscale, CV_BGR2GRAY);
	blur(greyscale, canny_image, Size(3,3));
	Canny(canny_image, canny_image, 10.0, 30.0);
	String writeout_name = "C:/Users/nsane/Documents/Spring '19/CSC528 Computer Vision/Pictures/Assignment_2/";
	*numstr << *count;
	writeout_name += "EdgeDetectionFrame_"; writeout_name += numstr->str(); writeout_name += ".jpg";
	imwrite(writeout_name.c_str(), canny_image);
}