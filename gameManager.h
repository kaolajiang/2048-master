#pragma once
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>
#include<map>
#include"Support_func.h"
using namespace std;

class game 
{
public:
	void Show_menu();
	void new_game();
	void exitGame();
	void load_game();
	void show_rank();
	void clear_rank();
private:
	void save_game();
	void is_over();
	void show_map();
	void deleteZero(int array[],int size);
	void merge(int array[], int size);
	void up_map();
	void down_map();
	void left_map();
	void right_map();
	void generate();
	void save_rank(string& patch);
	int game_rank;
	int *game_map;
	int game_score;
	void load_rank(string& patch);
	string save_path = "./game_record.txt";
	string save_rank_1 = "./game_rank_1.txt";
	string save_rank_2 = "./game_rank_2.txt";
	string save_rank_3 = "./game_rank_3.txt";
	string name;
	void re_rank(string& patch);
	void opreat_game();
	bool is_saved = true;
	bool game_over=false;
};