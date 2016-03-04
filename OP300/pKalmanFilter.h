#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>

using namespace std;

class pKalmanFilter
{
private:
	cv::Mat result_Matrix;//Ŀ��ֵ����
	cv::Mat *A_Matrix = NULL;//״̬ת�ƾ���
	cv::Mat *B_Matrix = NULL;//���ƾ���
	cv::Mat Z_Matrix;//�۲����������й۲�õ�������
	cv::Mat *H_Matrix = NULL;//��������������ڽ��۲�����ת��Ϊ��������ĸ�ʽ
	cv::Mat *Q_Matrix = NULL;//������������
	cv::Mat *R_Matrix = NULL;//������������
	cv::Mat P_Matrix;//Э�������
	cv::Mat Kg_Matrix;//�����������
	cv::Mat U_Matrix;//���ƾ���
	int num_status;
	int num_control;
	int num_observe;

public:
	pKalmanFilter(int num_status, int num_control, int num_observe);
	bool setBasicMatrix(cv::Mat& A, cv::Mat& B, cv::Mat& H, cv::Mat& Q, cv::Mat& R);

	bool update(cv::Mat &input, cv::Mat &output, cv::Mat &measurement, cv::Mat &control);
	~pKalmanFilter();
};

