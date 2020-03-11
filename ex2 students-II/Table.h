#ifndef TABLE_H
#define TABLE_H
#include<string>
#include<iostream>
#include<conio.h>
#include<iomanip>
#include<windows.h>
#include<fstream>
#include<vector>
#include<unordered_map>
//Table stores students' information and the information operation functions
//student info is stored in stuTable.txt 
class Table
{
public:
	Table();
	~Table();
	//file io
	void readFile(std::string filename);
	void printFile(std::string filename);
	//interation with users
	void query();
	//table managements
	void addStudent();
	void addCourse();
	void delStudent();
	void delCourse();
	void changeScore();
	//update min,max,avg
	void updateStat();
	//table visualization
	void showTable();
	void SetCursorPosition(const int x, const int y); //set the position of cursor on screen
private:
	struct student {
		std::string name;
		std::unordered_map<std::string, int> scores;
		int scoreSum;
		student();
	};
	std::vector<student> studentList;
	std::vector<std::string> courseList;
	std::vector<int> courseTaker;
	std::vector<int> sumList;
	std::vector<int> maxList;
	std::vector<int> minList;
};
#endif
