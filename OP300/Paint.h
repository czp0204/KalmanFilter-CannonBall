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
	cv::Point previous_point;//记录前一个点，用于绘制轨迹

	//注意画板与窗口是各个对象公有的，所以定义为静态（即一个程序只有一块画板与一个窗口）
	static string name_window;//窗口
	static cv::Mat drawing_board;//画板
	bool isFirst = true;

	//string  err_analysics_window = "Error Analysics";
	//cv::Mat analysics_board;

public:
	Paint(int w=500,int h=400) :previous_point(cv::Point(0, 0))
	{
		drawing_board.create(h,w,CV_8UC3);
		drawing_board.setTo(0);//默认背景为黑色
		cv::namedWindow(name_window);
		
		//cv::imshow(name_window, drawing_board);
	}

	bool PaintPoint(cv::Point p, cv::Scalar color, int r,bool isTrace);
	bool paintBar(std::vector<float>, string, int, cv::Scalar);

	~Paint();
};

