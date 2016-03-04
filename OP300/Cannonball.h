#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/utility.hpp>

class Cannonball
{
private:
	//cv::Point ball_position;
	float delta_time;//时间间隔
	cv::Point current_position;//现时点的位置
	cv::Point init_position;//初始点的位置，保留，用于扩展
	float init_xSpeed;//初始x方向的速度
	float init_ySpeed;
	float current_xSpeed;//现时x方向的速度
	float current_ySpeed;
	float acceleration_x;//x方向的加速度
	float acceleration_y;
	int last_time;//累计已经运行了多少个时间间隔
public:
	Cannonball(float init_xSpeed, float init_ySpeed, float acceleration_x, float acceleration_y,cv::Point init_position = cv::Point(0, 0), float delta_time = 1)
		:current_position(init_position), current_xSpeed(init_xSpeed), current_ySpeed(init_ySpeed)
	{
		last_time = 0;
		this->delta_time = delta_time;
		this->init_xSpeed = init_xSpeed;
		this->init_ySpeed = init_ySpeed;
		this->acceleration_x = acceleration_x;
		this->acceleration_y = acceleration_y;
		this->init_position = init_position;
	}

	void setInitSataus(float init_xSpeed, float init_ySpeed, float acceleration_x, float acceleration_y,
					cv::Point init_position = cv::Point(0, 0), float delta_time = 1)
	{
		last_time = 0;
		this->init_xSpeed = init_xSpeed;
		this->init_ySpeed = init_ySpeed;
		this->init_position = init_position;

		this->acceleration_x = acceleration_x;
		this->acceleration_y = acceleration_y;

		this->current_xSpeed = init_xSpeed;
		this->current_ySpeed = init_ySpeed;
		this->current_position = init_position;
	}

	cv::Point getCurrentPosition()
	{
		return this->current_position;
	}

	float getAccelerationSpeedY()
	{
		return this->acceleration_y;
	}

	bool update_position();
	~Cannonball();
};

