#include<iostream>
#include"gameManager.h"
using namespace std;
int main() {
	/*
	首先实例化一个类
	*/
	game new_game;
	
	int choice;
	while (true)
	{
		system("cls");
		new_game.Show_menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			//新游戏
			new_game.new_game();
			break;
		case 1:
			//历史数据
			new_game.show_rank();
			break;
		case 2:
			new_game.load_game();
			//继续游戏
			break;
		case 3:
			new_game.clear_rank();
			//清空榜单
		case 4:
			new_game.exitGame();
			//退出游戏
		default:
			system("cls");
			break;
		}
	}

}
