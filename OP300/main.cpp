#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include "Cannonball.h"
#include "Paint.h"
#include "pKalmanFilter.h"

using namespace cv; // all the new API is put into "cv" namespace. Export its content
using namespace std;

void a(Mat m)
{
	if (m.empty())
	{
		cout << "TRUE";
	}
	else
	{
		cout << "FALSE";
	}
}

int main()
{

	//Mat result_Matrix = Mat(4, 2, CV_32FC1);
	//randn(result_Matrix, Scalar::all(0), Scalar::all(0.1));
	//cout << result_Matrix;
	//while (1)
	//waitKey(0);

	/*
	cv::Mat resultMatrix;//目标值向量
	cv::Mat *A_Matrix = NULL;//状态转移矩阵
	cv::Mat *B_Matrix = NULL;//控制矩阵
	cv::Mat Z_Matrix;//观测向量，存有观测得到的数据
	cv::Mat *H_Matrix = NULL;//控制输入矩阵，用于将观测数据转化为计算所需的格式
	cv::Mat *Q_Matrix = NULL;//过程噪音向量
	cv::Mat *R_Matrix;//测量噪音向量
	cv::Mat P_Matrix;//协方差矩阵
	cv::Mat Kg_Matrix;//增益矩阵差矩阵
	cv::Mat U_Matrix;//控制矩阵
	*/
	float delat_time = 1;
	Mat x_vector = Mat(4, 1, CV_32FC1,Scalar::all(1));
	Mat z_vector = Mat(4, 1, CV_32FC1);
	Mat u_vector = Mat(1, 1, CV_32FC1);
	Mat A_Matrix = (Mat_<float>(4, 4) << 1, 0, delat_time, 0, 0, 1, 0, delat_time, 0, 0, 1, 0, 0, 0, 0, 1);
	//cout << "A\n"<<A_Matrix;
	Mat B_Matrix = (Mat_<float>(4, 1) << 0, 0.5*delat_time*delat_time, 0, -delat_time);
	Mat H_Matrix = (Mat_<float>(2, 4) << 1, 0, 0, 0, 0, 1, 0, 0);
	vector<float> err_x;
	vector<float> err_y;
	
	pKalmanFilter kalmanFiter(4, 1, 2);
	kalmanFiter.setBasicMatrix(A_Matrix, B_Matrix, H_Matrix, Mat(), Mat());

	Cannonball cannonBall(20, 30, 0, -2);

	Paint paint(600,400);
	Paint k_paint(600, 400);

	bool isFinish = true;
	Point temp_point = Point(0, 0);
	while (isFinish)
	{
		err_x.push_back(abs(cannonBall.getCurrentPosition().x - x_vector.at<float>(0, 0)));
		err_y.push_back(abs(cannonBall.getCurrentPosition().y - x_vector.at<float>(1, 0)));

		isFinish = paint.PaintPoint(cannonBall.getCurrentPosition(), Scalar(255, 0, 0), 4, true);

		temp_point = Point(x_vector.at<float>(0, 0), x_vector.at<float>(1, 0));
		//cout << "x: " << x_vector<<"\n";
		k_paint.PaintPoint(temp_point, Scalar(0, 0, 255), 4, true);

		z_vector.at<float>(0, 0) = cannonBall.getCurrentPosition().x;
		z_vector.at<float>(1, 0) = cannonBall.getCurrentPosition().y;
		z_vector.at<float>(2, 0) = 0;
		z_vector.at<float>(3, 0) = 0;
		u_vector.at<float>(0, 0) = cannonBall.getAccelerationSpeedY();
		
		isFinish = cannonBall.update_position();
		kalmanFiter.update(x_vector, x_vector, z_vector, u_vector);
		
		waitKey(100);
	}
	paint.paintBar(err_x, "X_ERR", 4, Scalar(70, 140, 210));
	paint.paintBar(err_y, "Y_ERR", 4, Scalar(210, 140, 70));
	cout << "the program is finsh";
	//while (1);
	waitKey(0);
}