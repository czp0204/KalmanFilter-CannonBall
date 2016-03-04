#include "Paint.h"

using namespace std;
using namespace cv;

//Paint::Paint()
//{
//}
string Paint::name_window = "Cannonball Image";
cv::Mat Paint::drawing_board;

//在屏幕绘制点的位置
//p 点的现时位置  color 点的颜色  r 点的半径  isTrace 是否绘制轨迹
//return 是否成功绘制
bool Paint::PaintPoint(cv::Point p, cv::Scalar color = cv::Scalar(255, 0, 0),int r=4,bool isTrace=false)
{
	Point temp_point=Point(0,0);//用于将实际点上下反过来（（0,0）点原来在左上角），使展示更直观
	//若x的位置超出屏幕，则停止程序
	if (p.x > drawing_board.cols)
		return false;
	else
	{
		//不绘制轨迹
		if (!isTrace)
		{
			drawing_board.setTo(0);
			temp_point.y = drawing_board.rows - p.y;
			temp_point.x = p.x;
			circle(drawing_board, temp_point, r, color, -1);
			imshow(name_window, drawing_board);
		}
		//绘制轨迹
		else
		{
			temp_point.y = drawing_board.rows - p.y;
			temp_point.x = p.x;
			circle(drawing_board, temp_point, r, color, -1);
			//判断是否第一点，第一点没有与上一点的连线
			if (!isFirst)
			{
				line(drawing_board, previous_point, temp_point, color, 1);
			}
			else
			{
				isFirst = false;
			}
			previous_point = temp_point;
			imshow(name_window, drawing_board);
		}
	}
	return true;
}

//绘制柱状图
//data 绘制柱状图的数据  name_board 画板的名称  w 柱状图中柱的宽度 color 柱的颜色
bool Paint::paintBar(std::vector<float> data, string name_board,int w=4,cv::Scalar color=Scalar(0,255,0))
{
	int num_data = data.size();
	//pair<float,float> hight_board(0,0);
	float interal=0.;
	auto height_board = std::minmax_element(data.begin(), data.end());
	interal = *(height_board.second) - *(height_board.first);

	if (num_data*w > 800)
	{
		cout << "too many data with this width to display" << endl;
		return false;
	}

	Mat bar_board(250, num_data*w+4, CV_8UC3, Scalar::all(0));

	for (auto ii = data.begin(); ii < data.end(); ii++)
	{
		*ii = (*ii - *(height_board.first)) / interal*200 + 10;
	}

	int num_bar=0;
	for (auto ii = data.begin(); ii < data.end(); ii++)
	{
		rectangle(bar_board, Rect(num_bar*w+2,bar_board.rows - *ii, w, *ii), color, -1);
		num_bar++;
	}	
	imshow(name_board,bar_board);
	return true;
}

Paint::~Paint()
{

}
