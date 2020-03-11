#pragma once
#ifndef STUSYSTEM_H
#define STUSYSTEM_H
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
struct student {
	string name;
	int score_1;
	int score_2;
	int score_3;
	float average;
	student() : score_1(0), score_2(0), score_3(0) {};
};
class stuSystem
{
public:
	stuSystem();
	~stuSystem();
	void showTable();
	void add();
	void remove();
	void interaction();
	void readFile();
	void writeFile();
	void updateStat();
private:
	vector<student> table;
	int Sum[3];
	int Max[3];
	int Min[3];
};
#endif // !STUSYSTEM_H



