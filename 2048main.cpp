#include<iostream>
#include"gameManager.h"
using namespace std;
int main() {
	/*
	����ʵ����һ����
	*/
	game new_game;
	
	int choice;
	while (true)
	{
		system("cls");
		new_game.Show_menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			//����Ϸ
			new_game.new_game();
			break;
		case 1:
			//��ʷ����
			new_game.show_rank();
			break;
		case 2:
			new_game.load_game();
			//������Ϸ
			break;
		case 3:
			new_game.clear_rank();
			//��հ�
		case 4:
			new_game.exitGame();
			//�˳���Ϸ
		default:
			system("cls");
			break;
		}
	}

}
