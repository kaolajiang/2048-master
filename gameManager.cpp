#include<iostream>
#include"gameManager.h"

using namespace std;

void game::Show_menu() {
	cout << "***************************************" << endl;
	cout << "********* ��ӭʹ��������2048С��Ϸ ***" << endl;
	cout << "*************  0.����Ϸ  *************" << endl;
	cout << "*************  1.��  ��  *************" << endl;
	cout << "*************  2.��  ��  *************" << endl;
	cout << "*************  3.��  ��  *************" << endl;
	cout << "*************  4.��  ��  *************" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}
void game::exitGame() {
	char input;
	if (!this->is_saved)
	{
		cout << "��ǰ���Ȼ�û�б��棬�Ƿ񱣴棿";
		cout << "����y���棬�������ཡֱ���˳�";
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
	
	cout << "��Ϸ�Ѿ��˳�" << endl;
	system("pause");
	exit(0);

}
void game::new_game() {
	
	system("cls");
	this->game_score = 0;
	bool choose_flag = false;
	while (!choose_flag)
	{
		cout << "������ѡ�����Ϸ�ȼ�" << endl;
		cout << "1 ��4*4" << endl;
		cout << "2 ��8*8" << endl;
		cout << "3 ��16*16" << endl;
		cin >> this->game_rank;
		char choice;
		cout << "��ѡ�����Ϸ�ȼ�Ϊ:" << this->game_rank << "   ȷ��/y" << "   ����/n" << endl;
		cin >> choice;
		if (choice == 'y') {
			system("cls");
			cout << " ��Ϸ�ȼ�Ϊ" << this->game_rank << endl;
			cout << "������ʼ��Ϸ" << endl;
			choose_flag = true;
		
		}
	}
	/*
	�����Ϸ�ȼ�����ֱ�������Ϸ�ȼ��������¿�ʼ
	*/

	/*
	��������
	*/
	
	cout << "�������������" << endl;

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
		cout << "����ȼ�����" << endl;
		break;
	}
	
	this->show_map();
	/*
	   ��ʼ����
	   ���������ǵȴ�������Ϸ����ȡ����ֵ���룬�����������Ҳ�����Ȼ��ÿһ���ж��Ƿ�GG
	
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
	//�ó�����ʾ2048��Ϸ�ĵ�ͼ
	//�������
	system("cls");
	cout << "--------------------------------------" << endl;
	//ȷ��ѭ���Ĵ�С
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

	cout <<this->name <<"��ǰ�ķ���Ϊ: " << this->game_score << endl;
	cout << "Plase Move Map(��:w ��:s ��:a ��:d): ";
	cout << "���浱ǰ��Ϸ�����밴��  l" << endl;
	cout << "                   ������Ϸ�밴:   b"<<endl;
	
	

}
void game::generate() {

	//��д24���ɳ��� �ȶ���һ�����������洢����Ϊ�յ㣬Ȼ�������ѡ������2��4
	//ͳ��0��,Ҫ�ǲ�����û��0����һ��GG,���Ըó���ĵ���
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
	//�������ѡ��һ��λ����������2��4
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
	//�ó���ʵ�ֵ������Ϻϲ�����,��������һά���飬���ȵ��жϸúϲ��ĺϲ������úϲ��Ĳ��ϲ���һ��һ�в���
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
	//�Ծ����һ�в�����Ҫ�������²���
	int* col = new int[length]();
	bool change = false;
	for ( int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[i + j * length];
		}
		//ȡ��0 �����е����鿿��һ��
		this->deleteZero(col, length);
		//�ϲ�������ͬ��ֵ
		this->merge(col, length);
		this->deleteZero(col, length);
		//������ֵ�Ż�ԭ�����飬ͬʱ�ж϶�Ӧֵ�Ƿ�ı䣬���δ�ı䣬������������
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
	//����ȡ��������������ƶ�������Ҫ�Ӹߵ���ȡ��������˳���������
	/*
	������Ӧ��ϵ����ʹ�����·�ʽ�ҵ�
	
	
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
		//�ϲ�������ͬ��ֵ
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
	����ʵ��2048��Ϸ��������Ʋ���
	��ʱi�������������ĵ������ҵ���Ӧ��ϵ
	*/
	while (i < length)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[i*length+j];
		}

		this->deleteZero(col, length);
		//�ϲ�������ͬ��ֵ
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
	����ʵ��2048��Ϸ��������Ʋ���
	��ʱi�������������ĵ������ҵ���Ӧ��ϵ
	*/
	while (i < length)
	{
		for (int j = 0; j < length; j++)
		{
			col[j] = this->game_map[length*length-1-i*length-j];
		}

		this->deleteZero(col, length);
		//�ϲ�������ͬ��ֵ
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
	�ó���ʱ�临�Ӷ�Ϊo(N)
	�ռ临�Ӷ�Ϊo(1)
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
	  ���㷨ʵ��2048��Ϸ�ĺ��������Ԫ����ͣ�˫ָ�������
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
	��δ����������浱ǰ����Ϸ���ȡ�����Ķ�����������Ϸ����
	��ǰ��Ϸ�����ļ�Ϊ"./game_save/game_record.txt";
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
	����ǰ�������������Ϊ���а��ļ�,ע��������Ϸ�ȼ�1��2��3
	*/
	

	this->is_saved = true;
	cout << "�ļ�����ɹ�" << endl;
}
void game::save_rank(string &patch) {

	ofstream outrank(patch, ios::out | ios::ate);
	outrank << this->name << ":";
	outrank << this->game_score << endl;

}
void game:: load_game() {
/*
���γ���������Ǽ�����Ϸ����,�ص����ڶ�ȡ��Ϸ���Ⱥ���Ϸ�ȼ�
*/
	ifstream ifs;
	ifs.open(this->save_path,ios::in);
	if (!ifs.is_open())
	{
		cout << "û�д浵�������Զ���ʼ����Ϸ" << endl;
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
		cout << "�ȼ�����" << endl;
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
	����Ҫ��ѯ�ĸ��ȼ���Ϸ�İ�
	*/
	cout << "������Ҫ�鿴��һ���ķ�����" << endl;
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
	����Ҫ��ѯ�ĸ��ȼ���Ϸ�İ�
	*/
	cout << "������Ҫ�����һ���ķ�����" << endl;
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
	cout << "��ճɹ�" << endl;
	system("pause");
}
void game::load_rank(string& patch) {
	ifstream readrank(patch, ios::in);
	/*
	��Ҫ�ж��ļ��Ƿ�Ϊ��
	*/
	

	if (!readrank.is_open())
	{
		cout << "�񵥲������뿪ʼ��Ϸ���½���" << endl;
		system("pause");
		return;
	}
	if (readrank.peek()==EOF)
	{
		cout << "�񵥲������뿪ʼ��Ϸ���½���" << endl;
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
		cout << "������" << i->second << "        �ɼ�" << i->first << endl;
	}
	system("pause");
}
void game::re_rank(string& patch) {
/*
��OFSɾ���ļ����¼���
*/
	ofstream rerank(patch, ios::out|ios::trunc);
	rerank.close();

}