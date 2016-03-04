#include "Cannonball.h"
#include <iostream>

//Cannonball::Cannonball()
//{
//}

using namespace std;
using namespace cv;

//����Ŀ����λ��
//return �����Ƿ�ɹ�����
bool Cannonball::update_position()
{
	//����ʱ��С��0������������
	if (current_position.x < 0 || current_position.y < 0 )
	{
		cout << "the position has reach the end"<<endl;
		return false;
	}
	else
	{
		last_time += delta_time;
		//��ţ����ѧ���ɼ�������
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
