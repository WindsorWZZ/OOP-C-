#include "stdafx.h"
#include "puzzle.h"

puzzle::puzzle(int x, int y) : 
		puzzleMap(std::vector<std::vector<bool> >(x, std::vector<bool>(y, false))), curPos({0,0}), princessPos({0,0}), monsterPos({0,0})
{

}


bool puzzle::Initialize(int x, int y)
{
	//Initialize the puzzle size
	if (x < 5 || y < 5) return false;
	puzzleMap = std::vector<std::vector<bool> >(x, std::vector<bool>(y, false));
	curPos = { 0,0 };
	princessPos = { 0,0 };
	monsterPos = { 0,0 };
	got = false;
	return true;
}

bool puzzle::setMyPos(int x, int y)
{
	if (x < 0 || x >= puzzleMap.size() || y < 0 || y >= puzzleMap[0].size())
		return false;
	//set player's position
	curPos = { x, y };
	lobby = { x, y };
	puzzleMap[x][y] = true;
	return true;
}

bool puzzle::setMonsterPos(int x, int y)
{
	if (x < 0 || x >= puzzleMap.size() || y < 0 || y >= puzzleMap[0].size())
		return false;
	//set monster's position
	monsterPos = { x, y };
	return true;
}

bool puzzle::setPrincessPos(int x, int y)
{
	if (x < 0 || x >= puzzleMap.size() || y < 0 || y >= puzzleMap[0].size())
		return false;
	//set princess's position
	princessPos = { x,y };
	return true;
}

bool puzzle::move(std::string dir)
{
	//return true after successful move
	//return false when input illegal
	if (dir == "east" || dir == "right") {
		if (curPos.second == puzzleMap[0].size() - 1) 
			return false;
		++curPos.second;
	}
	else if (dir == "west" || dir == "left") {
		if (curPos.second == 0)
			return false;
		--curPos.second;
	}
	else if (dir == "south" || dir == "down") {
		if (curPos.first == puzzleMap.size() - 1)
			return false;
		++curPos.first;
	}
	else if (dir == "north" || dir == "up") {
		if (curPos.first == 0)
			return false;
		--curPos.first;
	}
	else return false;
	puzzleMap[curPos.first][curPos.second] = true;
	if (curPos == princessPos) {
		got = true;
		system("cls");
		std::cout << "You've got the princess!!!" << std::endl;
		system("pause");
	}
	return true;
}

void puzzle::analyze(std::string& roomName, std::vector<std::string>& exits, int * pDist, int * mDist)
{
	if (lobby == curPos) roomName = "lobby";
	else if (lobby == princessPos) roomName = "princess's room";
	else roomName = "empty room";
	if (curPos.first > 0) exits.push_back("west/left");
	if (curPos.first < puzzleMap.size() - 1) exits.push_back("east/right");
	if (curPos.second > 0) exits.push_back("north/up");
	if (curPos.second < puzzleMap[0].size() - 1) exits.push_back("south/down");
	if (got) *pDist = 0;
	else 
		*pDist = abs(princessPos.first - curPos.first) + abs(princessPos.second - curPos.second);
	*mDist = abs(monsterPos.first - curPos.first) + abs(monsterPos.second - curPos.second);
	return;
}

int puzzle::judgeWin()
{
	//return 1 if win
	//return 0 if nothing happen
	//return -1 if fail
	if (got && curPos == lobby)
		return 1;
	else if (curPos == monsterPos)
		return -1;
	return 0;
}

void puzzle::show()
{
	//show the puzzle on screen
	system("cls");
	COORD position;
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	for (int i = 0; i < puzzleMap.size(); ++i) {
		for (int j = 0; j < puzzleMap[0].size(); ++j) {
			position.X = 2 * j;
			position.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			if (puzzleMap[i][j]) {
				if (curPos.first == i && curPos.second == j)
					std::cout << "O";
				else if (princessPos.first == i && princessPos.second == j)
					std::cout << "P";
				else if (monsterPos.first == i && monsterPos.second == j)
					std::cout << "M";
				else if (lobby.first == i && lobby.second == j)
					std::cout << "L";
				else if (puzzleMap[i][j])
					std::cout << "*";
			}
		}
	}
	std::cout << std::endl;
	return;
}

puzzle::~puzzle()
{
}
