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

	//产生0-length数据
	mt19937 ge(time(NULL));
	uniform_int_distribution<int> u(0,length-1);
	return u(ge);
}
vector<int>  splict(const char* array)
{
	/*
	字符数组按照逗号分隔,取出数据,换成数值，返回一个数组的起始地址
	*/
	string ss(array);
	/*
	开始分隔
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
	/*将字符串转化为对应数字*/
	return stoi(str);
}
