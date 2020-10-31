#include<iostream>
#include"gameManager.h"

using namespace std;

void game::Show_menu() {
	cout << "***************************************" << endl;
	cout << "********* 欢迎使用命令行2048小游戏 ***" << endl;
	cout << "*************  0.新游戏  *************" << endl;
	cout << "*************  1.榜  单  *************" << endl;
	cout << "*************  2.继  续  *************" << endl;
	cout << "*************  3.清  空  *************" << endl;
	cout << "*************  4.退  出  *************" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}
void game::exitGame() {
	char input;
	if (!this->is_saved)
	{
		cout << "当前进度还没有保存，是否保存？";
		cout << "输入y保存，输入其余健直接退出";
		cin >> input;
		switch (input)
		{
		case 'y':
			this->save_game();
		case 'n':
			break;
		default:
			break;
		}
	}
	
	cout << "游戏已经退出" << endl;
	system("pause");
	exit(0);

}
void game::new_game() {
	
	system("cls");
	this->game_score = 0;
	bool choose_flag = false;
	while (!choose_flag)
	{
		cout << "请输入选择的游戏等级" << endl;
		cout << "1 ：4*4" << endl;
		cout << "2 ：8*8" << endl;
		cout << "3 ：16*16" << endl;
		cin >> this->game_rank;
		char choice;
		cout << "您选择的游戏等级为:" << this->game_rank << "   确认/y" << "   撤销/n" << endl;
		cin >> choice;
		if (choice == 'y') {
			system("cls");
			cout << " 游戏等级为" << this->game_rank << endl;
			cout << "即将开始游戏" << endl;
			choose_flag = true;
		
		}
	}
	/*
	如果游戏等级有误直接输出游戏等级有误重新开始
	*/

	/*
	输入名字
	*/
	
	cout << "请输入你的名字" << endl;

	cin >> this->name;

	switch (this->game_rank)
	{
	case 1:
		this->game_map = new int[4*4]();
		this->generate();
		break;
	case 2:
		this->game_map = new int[8*8]();
		this->generate();
		break;
	case 3:
		this->game_map = new int[16*16]();
		this->generate();
		break;
	default:
		cout << "输入等级有误" << endl;
		break;
	}
	
	this->show_map();
	/*
	   开始操作
	   程序流程是等待操作游戏，读取按键值输入，进行上下左右操作，然后每一步判断是否GG
	
	*/
	this->opreat_game();
	system("pause");
}
void game::opreat_game() {

	char input_key;
	while (!this->game_over)
	{
		cin >> input_key;
		switch (input_key)
		{
		case 'w':
			this->up_map();
			this->show_map();
			break;
		case 'a':
			this->left_map();
			this->show_map();
			break;
		case 's':
			this->down_map();
			this->show_map();
			break;
		case 'd':
			this->right_map();
			this->show_map();
			break;
		case 'b':
			this->exitGame();
			break;
		case 'l':
			this->save_game();
			break;
		default:
			break;
		}
	}
}
void game::show_map() {
	//该程序显示2048游戏的地图
	//暴力输出
	system("cls");
	cout << "--------------------------------------" << endl;
	//确定循环的大小
	int lenth=0 ;
	switch (this->game_rank)
	{
	case 1:
		lenth = 4;
		break;
	case 2:
		lenth = 8;
		break;
	case 3:
		lenth = 16;
		break;
	default:
		break;
	}
	
	//
	for (int i = 0; i < lenth; i++) {

		for (int j = 0; j <lenth; j++) {
			
			cout << this->game_map[i*lenth+j]<<"   |   ";
		}
		cout << endl;
	}
	cout << "--------------------------------------" << endl;

	cout <<this->name <<"当前的分数为: " << this->game_score << endl;
	cout << "Plase Move Map(上:w 下:s 左:a 右:d): ";
	cout << "保存当前游戏进度请按：  l" << endl;
	cout << "                   结束游戏请按:   b"<<endl;
	
	

}
void game::generate() {

	//编写24生成程序 先定义一个数组用来存储哪里为空点，然后再随机选择生成2或4
	//统计0点,要是操作后没有0点则一定GG,所以该程序的调用
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	vector<int> NoZeroPos;
	for (int i = 0; i < length*length; i++) {
	
		if (this->game_map[i]==0)
		{
			NoZeroPos.push_back(i);
		}

	}
	//下面随机选出一个位置让其生成2或4
	double prob24 = rand1();
	if (NoZeroPos.size()==0)
	{
		this->game_over = true;
		return;
	}
	int choose_pos = randpos(NoZeroPos.size());

	if (prob24<0.5)
	{
		this->game_map[NoZeroPos[choose_pos]] = 2;
	}
	else
	{
		this->game_map[NoZeroPos[choose_pos]] = 4;
	}
	
}
void game::up_map() {
	//该程序实现的是向上合并数组,本程序是一维数组，首先得判断该合并的合并，不该合并的不合并，一列一列操作
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	//对具体的一列操作需要进行如下操作
	int* col = new int[length]();
	bool change = false;
	for ( int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[i + j * length];
		}
		//取出0 让所有的数组靠在一起
		this->deleteZero(col, length);
		//合并两两相同的值
		this->merge(col, length);
		this->deleteZero(col, length);
		//将现有值放回原有数组，同时判断对应值是否改变，如果未改变，则不生成新数据
		for (int j = 0; j < length; j++)
		{
			if (this->game_map[i + j * length] != col[j]) {
				this->game_map[i + j * length] = col[j];
				change = true;
			}
		}
	}
	if (change)
	{
		this->generate();
		this->is_saved = false;
	}
	this->is_over();
	delete[] col;
	
}
void game::down_map() {
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	//按列取出，相比于向上移动，其需要从高到低取出，按按顺序放入数组
	/*
	上述对应关系可以使用以下方式找到
	
	
	*/
	int* col = new int[length]();
	bool change = false;
	int i = 0;
	while (i<length)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[length*length-1-i-j*length];
		}

		this->deleteZero(col, length);
		//合并两两相同的值
		this->merge(col, length);
		this->deleteZero(col, length);
		for (int j = 0; j < length; j++)
		{
			if (this->game_map[length*length-1-i-j*length] != col[j]) {
				this->game_map[length * length - 1 - i - j * length] = col[j];
				change = true;
			}
		}
		i++;
	}
	if (change)
	{
		this->generate();
		this->is_saved = false;
	}
	this->is_over();
	delete[] col;
	
}

void game::left_map() {
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	int* col = new int[length]();
	bool change = false;
	int i = 0;
	/*
	程序实现2048游戏数组的左移操作
	这时i代表行数，核心点在于找到对应关系
	*/
	while (i < length)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[i*length+j];
		}

		this->deleteZero(col, length);
		//合并两两相同的值
		this->merge(col, length);
		this->deleteZero(col, length);
		for (int j = 0; j < length; j++)
		{
			if (this->game_map[i * length + j] != col[j]) {
				this->game_map[i * length + j] = col[j];
				change = true;
			}
		}
		i++;
	}
	if (change)
	{
		this->generate();
		this->is_saved = false;
	}
	this->is_over();
	delete[] col;

}

void game::right_map() {
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	int* col = new int[length]();
	bool change = false;
	int i = 0;
	/*
	程序实现2048游戏数组的右移操作
	这时i代表行数，核心点在于找到对应关系
	*/
	while (i < length)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[length*length-1-i*length-j];
		}

		this->deleteZero(col, length);
		//合并两两相同的值
		this->merge(col, length);
		this->deleteZero(col, length);
		for (int j = 0; j < length; j++)
		{
			if (this->game_map[length * length - 1 - i * length - j] != col[j]) {
				this->game_map[length * length - 1 - i * length - j] = col[j];
				change = true;
			}
		}
		i++;
	}
	if (change)
	{
		this->generate();
		this->is_saved = false;
	}
	this->is_over();
	delete[] col;

}
void game::is_over() {
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		break;
	case 2:
		length = 8;
		break;
	case 3:
		length = 16;
		break;
	default:
		break;
	}
	vector<int> NoZeroPos;
	for (int i = 0; i < length * length; i++) {

		if (this->game_map[i] == 0)
		{
			NoZeroPos.push_back(i);
			return;
		}

	}
	if (NoZeroPos.size() == 0)
	{
		this->game_over = true;
	}
}

void game::deleteZero(int array[], int size) {
	int i = 0;
	int zero_index = 0;
	/*
	该程序时间复杂度为o(N)
	空间复杂度为o(1)
	*/
	while (i<size)
	{
		if (array[i]!=0)
		{
			
			if (array[zero_index]!=0)
			{
				zero_index++;
				i++;
			}
			else
			{
				array[zero_index] = array[i];
				array[i] = 0;
				i++;
				zero_index++;
			}
			
		}
		else
		{
			if (array[zero_index] != 0)
			{
				zero_index = i;
				i++;
			}
			else
			{
				i++;
			}
		}
	}
}
void game::merge(int array[], int size) {

	/*
	  该算法实现2048游戏的核心数组的元素求和，双指针来求解
	*/
	int first = 1;
	int second = 0;
	while (first<size)
	{
		if (array[first]==array[second])
		{
			this->game_score += 2 * array[first];
			array[second] = array[first] + array[second];
			array[first] = 0;
			first += 2;
			second += 2;
		}
		else
		{
			first++;
			second++;
		}
	}

}
void game::save_game() {
	/*
	这段代码用来保存当前的游戏进度。保存的东西包括，游戏分数
	当前游戏保存文件为"./game_save/game_record.txt";
	*/
	int length = 0;
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		this->save_rank(this->save_rank_1);
		break;
	case 2:
		length = 8;
		this->save_rank(this->save_rank_2);
		break;
	case 3:
		length = 16;
		this->save_rank(this->save_rank_3);
		break;
	default:
		break;
	}
	ofstream ofs;
	ofs.open(this->save_path, ios::out|ios::ate|ios::trunc);
	ofs << this->game_score << ',';
	ofs << this->game_rank << ',';
	for (int i = 0; i < length * length; i++) {
		
		ofs << this->game_map[i]<<',';
	
	}
	ofs << endl;
	ofs << this->name;
	ofs.close();

	/*
	将当前姓名与分数保存为排行榜文件,注意区分游戏等级1，2，3
	*/
	

	this->is_saved = true;
	cout << "文件保存成功" << endl;
}
void game::save_rank(string &patch) {

	ofstream outrank(patch, ios::out | ios::ate);
	outrank << this->name << ":";
	outrank << this->game_score << endl;

}
void game:: load_game() {
/*
本段程序的作用是加载游戏进度,重点在于读取游戏进度和游戏等级
*/
	ifstream ifs;
	ifs.open(this->save_path,ios::in);
	if (!ifs.is_open())
	{
		cout << "没有存档，正在自动开始新游戏" << endl;
		this->new_game();
		return;
	}
	
	char buf[1024] = {0};
	ifs.getline(buf, sizeof(buf));
	
	getline(ifs, this->name);
	ifs.close();
	int length = 0;
	
	vector<int> num_array = splict(buf);
	this->game_score = num_array[0];
	this->game_rank =num_array[1];
	
	switch (this->game_rank)
	{
	case 1:
		length = 4;
		this->game_map = new int[4 * 4]();
		break;
	case 2:
		length = 8;
		this->game_map = new int[8* 8]();
		break;
	case 3:
		length = 16;
		this->game_map = new int[16 * 16]();
		break;
	default:
		cout << "等级错误" << endl;
		break;
	}

	for (int i = 0; i < length * length; i++) {
	
		this->game_map[i] = num_array[2+i];
	}
	
	this->show_map();
	this->opreat_game();
	return;
}
void game::show_rank() {
	system("cls");
	/*
	输入要查询哪个等级游戏的榜单
	*/
	cout << "请输入要查看哪一级的分数榜单" << endl;
	int rank;
	cin >> rank;
	switch (rank)
	{
	case 1:
		this->load_rank(this->save_rank_1);
		break;
	case 2:
		this->load_rank(this->save_rank_2);
		break;
	case 3:
		this->load_rank(this->save_rank_3);
		break;
	default:
		break;
	}

}
void game::clear_rank() {
	system("cls");
	/*
	输入要查询哪个等级游戏的榜单
	*/
	cout << "请输入要清空哪一级的分数榜单" << endl;
	int rank;
	cin >> rank;
	switch (rank)
	{
	case 1:
		this->re_rank(this->save_rank_1);
		break;
	case 2:
		this->re_rank(this->save_rank_2);
		break;
	case 3:
		this->re_rank(this->save_rank_3);
		break;
	default:
		break;
	}
	cout << "清空成功" << endl;
	system("pause");
}
void game::load_rank(string& patch) {
	ifstream readrank(patch, ios::in);
	/*
	需要判断文件是否为空
	*/
	

	if (!readrank.is_open())
	{
		cout << "榜单不存在请开始游戏以新建榜单" << endl;
		system("pause");
		return;
	}
	if (readrank.peek()==EOF)
	{
		cout << "榜单不存在请开始游戏以新建榜单" << endl;
		system("pause");
		return;
	}

	multimap< int,string> rank_list;
	string temp,name;
	string now = "";
	while (getline(readrank,temp))
	{
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] != ':') {
				
				now += temp[i];
			}
			else
			{
				 name= now;
				now = "";
			}
		}
	}
	
	rank_list.insert(pair< int,string>(str2num(now),name));
	for(multimap<int,string>::iterator i = rank_list.begin(); i!=rank_list.end();i++)
	{
		cout << "姓名：" << i->second << "        成绩" << i->first << endl;
	}
	system("pause");
}
void game::re_rank(string& patch) {
/*
用OFS删除文件重新简历
*/
	ofstream rerank(patch, ios::out|ios::trunc);
	rerank.close();

}