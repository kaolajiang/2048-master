#include<iostream>
#include<ctime>
#include<sstream>

#include"Support_func.h"
using namespace std;

double rand1() {
	mt19937 ge(time(NULL));
	uniform_real_distribution<double> u(0, 1);
	return u(ge);
}
int randpos(int length) {

	//����0-length����
	mt19937 ge(time(NULL));
	uniform_int_distribution<int> u(0,length-1);
	return u(ge);
}
vector<int>  splict(const char* array)
{
	/*
	�ַ����鰴�ն��ŷָ�,ȡ������,������ֵ������һ���������ʼ��ַ
	*/
	string ss(array);
	/*
	��ʼ�ָ�
	*/
	vector<int> num_array;
	string temp="";
	for (int i = 0; i<ss.size(); i++) {
		if (ss[i]!=',')
		{
			temp += ss[i];
		}
		else
		{
			num_array.push_back(str2num(temp));
			temp = "";
		}
	
	}
	return num_array;
}
int str2num(const string & str) 
{
	/*���ַ���ת��Ϊ��Ӧ����*/
	return stoi(str);
}
