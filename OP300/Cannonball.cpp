#include "Cannonball.h"
#include <iostream>

//Cannonball::Cannonball()
//{
//}

using namespace std;
using namespace cv;

//更新目标点的位置
//return 返回是否成功计算
bool Cannonball::update_position()
{
	//若现时点小于0，即结束计算
	if (current_position.x < 0 || current_position.y < 0 )
	{
		cout << "the position has reach the end"<<endl;
		return false;
	}
	else
	{
		last_time += delta_time;
		//按牛顿力学定律计算曲线
		current_position.x += (current_xSpeed*delta_time + 0.5*acceleration_x*delta_time*delta_time);
		current_position.y += (current_ySpeed*delta_time + 0.5*acceleration_y*delta_time*delta_time);
		current_xSpeed += acceleration_x*delta_time;
		current_ySpeed += acceleration_y*delta_time;
		return true;
	}
}

Cannonball::~Cannonball()
{
}
