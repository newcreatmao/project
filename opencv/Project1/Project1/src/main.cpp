#include <opencv2\opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;
int main()
{
	VideoCapture capture;
	capture.open(0);

	Mat frame;
	while (true)
	{
		capture >> frame;
		imshow("Íâ½ÓÉãÏñÍ·", frame);
		if (waitKey(120) >= 0)
			break;
	}
	return 0;
}