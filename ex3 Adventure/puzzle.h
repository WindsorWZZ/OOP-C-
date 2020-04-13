#pragma once
#include <vector>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <iostream>
class puzzle
{
public:
	puzzle(int x = 10, int y = 10);
	bool Initialize(int x, int y);
	bool setMyPos(int x, int y);
	bool setMonsterPos(int x, int y);
	bool setPrincessPos(int x, int y);
	bool move(std::string dir);
	void analyze(std::string& roomName, std::vector<std::string>& exits, int *pDist, int *mDist);
	int judgeWin();
	void show();
	virtual ~puzzle();
private:
	std::vector<std::vector<bool> > puzzleMap;
	bool got;
	std::pair<int, int> curPos;
	std::pair<int, int> lobby;
	std::pair<int, int> princessPos;
	std::pair<int, int> monsterPos;
};

