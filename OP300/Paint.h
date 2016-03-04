#pragma once

#include <iostream>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
//#include <list>

using namespace std;

class Paint
{
private:
	cv::Point previous_point;//��¼ǰһ���㣬���ڻ��ƹ켣

	//ע�⻭���봰���Ǹ��������еģ����Զ���Ϊ��̬����һ������ֻ��һ�黭����һ�����ڣ�
	static string name_window;//����
	static cv::Mat drawing_board;//����
	bool isFirst = true;

	//string  err_analysics_window = "Error Analysics";
	//cv::Mat analysics_board;

public:
	Paint(int w=500,int h=400) :previous_point(cv::Point(0, 0))
	{
		drawing_board.create(h,w,CV_8UC3);
		drawing_board.setTo(0);//Ĭ�ϱ���Ϊ��ɫ
		cv::namedWindow(name_window);
		
		//cv::imshow(name_window, drawing_board);
	}

	bool PaintPoint(cv::Point p, cv::Scalar color, int r,bool isTrace);
	bool paintBar(std::vector<float>, string, int, cv::Scalar);

	~Paint();
};

