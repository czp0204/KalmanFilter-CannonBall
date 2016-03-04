#include "pKalmanFilter.h"
#include <iostream>

using namespace std;
using namespace cv;

//pKalmanFilter::pKalmanFilter()
//{
//}

//cv::Mat resultMatrix;//Ŀ��ֵ����
//cv::Mat *A_Matrix = NULL;//״̬ת�ƾ���
//cv::Mat *B_Matrix = NULL;//���ƾ���
//cv::Mat Z_Matrix;//�۲����������й۲�õ�������
//cv::Mat *H_Matrix = NULL;//��������������ڽ��۲�����ת��Ϊ��������ĸ�ʽ
//cv::Mat *Q_Matrix = NULL;//������������
//cv::Mat *R_Matrix;//������������
//cv::Mat P_Matrix;//Ԥ���Э�������
//cv::Mat Kg_Matrix;//�����������
//cv::Mat U_Matrix;//���ƾ���

//��ʼ����������
pKalmanFilter::pKalmanFilter(int num_status, int num_control,int num_observe)
{
	this->num_status = num_status;
	this->num_control = num_control;
	this->num_observe = num_observe;
	result_Matrix = Mat(num_status, 1,CV_32FC1);
	randn(result_Matrix, Scalar::all(0), Scalar::all(0.1));
	P_Matrix = Mat::zeros(num_status, num_status, CV_32FC1);//Э�����
	setIdentity(P_Matrix, Scalar::all(1e-5));

	//Z_Matrix = Mat::zeros(num_observe, 1, CV_32FC1);
	//Kg_Matrix=Mat::zeros(num_control, 0, CV_32FC1);//�����������

}

//�Ը����������и�ֵ���������Ϊ�գ���ʹ��Ĭ��ֵ���и�ֵ
//return ������������չ
bool pKalmanFilter::setBasicMatrix(cv::Mat& A, cv::Mat& B,cv::Mat& H, cv::Mat& Q, cv::Mat& R)
{
	if (A.empty())
	{
		cout << "Matrix A must be define";
		return false;
	}

	A_Matrix = &A;

	if (B.empty())
	{
		B_Matrix = new Mat(num_status, num_control, CV_32FC1, Scalar::all(0));
		//U_Matrix =Mat(num_control, 1, CV_32FC1, Scalar::all(0));
	}
	else
	{
		B_Matrix = &B;
		//U_Matrix = U;
	}

	if (H.empty())
	{
		H_Matrix = new Mat(num_observe,num_status , CV_32FC1, Scalar::all(1));
	}
	else
	{
		H_Matrix = &H;
	}
	//Q��R�ı�ֵ�Խ����Ӱ��ϴ󣬴���Ӧ�ø������ĸ������
	//ͬʱ������Ѿ�֪��ʵ���������������ʵ����Ȼ����),��ʼֵԽ�����õ������ҲԽ��
	if (Q.empty())
	{
		Q_Matrix = new Mat(num_status, num_status, CV_32FC1, Scalar::all(0));
		setIdentity(*Q_Matrix, Scalar::all(5.));//�������Ԥ����̵Ŀ��Ŷȣ�����Խ�󣬿��Ŷ�Խ��
	}
	else
	{
		Q_Matrix = &Q;
	}

	if (R.empty())
	{
		R_Matrix = new Mat(num_observe, num_observe, CV_32FC1, Scalar::all(0));
		setIdentity(*R_Matrix, Scalar::all(5.));//�������������̵Ŀ��Ŷȣ�����Խ�󣬿��Ŷ�Խ��
	}
	else
	{
		R_Matrix = &R;
	}

}

//��Ԥ����и���
//ע��ú�����ı���������
//input ��������  output �������  measurement ��������������ֵΪδ�������ԭʼֵ��  control ��������
//return ������������չ
bool pKalmanFilter::update(cv::Mat &input, cv::Mat &output,cv::Mat &measurement,Mat &control)
{
	//����Q��R����ģ��������������
	Mat temp_processNoise(num_status, 1, CV_32FC1);
	for (int i = 0; i < num_status; i++)
	{
		randn(temp_processNoise, Scalar::all(0), Scalar::all((*Q_Matrix).at<float>(i, i)));
	}

	Mat temp_measurementNoise(num_observe, 1, CV_32FC1);
	for (int i = 0; i < num_observe; i++)
	{
		randn(temp_measurementNoise, Scalar::all(0), Scalar::all((*R_Matrix).at<float>(i, i)));
	}

	result_Matrix = input;
	if (!U_Matrix.empty())
		U_Matrix = control;
	else
		U_Matrix = Mat(num_control, 1, CV_32FC1, Scalar::all(0));

	//���ڸ��µ�������ʽ
	result_Matrix = (*A_Matrix)*input + (*B_Matrix)*U_Matrix+temp_processNoise;//1 ģ���������
	
	P_Matrix = (*A_Matrix)*P_Matrix*((*A_Matrix).t())+(*Q_Matrix);//2

	Kg_Matrix = P_Matrix*((*H_Matrix).t())*((((*H_Matrix)*P_Matrix*((*H_Matrix).t()) + *R_Matrix)).inv());//3

	Z_Matrix = (*H_Matrix)*measurement +temp_measurementNoise;//�Բ���ֵ�������������ֵΪδ�������ԭʼֵ��
	result_Matrix = result_Matrix + Kg_Matrix*(Z_Matrix - (*H_Matrix)*result_Matrix);//4

	P_Matrix = P_Matrix - Kg_Matrix*(*H_Matrix)*P_Matrix;//5
	output=result_Matrix ;

	return true;
}

pKalmanFilter::~pKalmanFilter()
{
	delete A_Matrix;
	delete B_Matrix;
	delete H_Matrix;
	delete Q_Matrix;
	delete R_Matrix;
}
