#include "stdafx.h"
#include "player.h"
player::player(): myPuzzle()
{

}

void player::query()
{
	//main menu of the game
	while (true) {
		system("cls");
		std::string input;
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "Quick start: q" << std::endl;
		std::cout << "Start game: s" << std::endl;
		std::cout << "Input file: file" << std::endl;
		std::cout << "exit: e" << std::endl;
		std::cin >> input;
		if (input == "q") quickStart();
		else if (input == "s") start();
		else if (input == "file") readFile();
		else if (input == "e") break;
		else{
			std::cout << "no such option!" << std::endl;
			std::cin >> input;
		}
	}
	return;
}

void player::readFile()
{
	//read the file
	//success: return true
	//fail: return false
	std::string fileName;
	std::cout << "Input your file name:" << std::endl;
	std::cin >> fileName;
	std::ifstream file(fileName);
	myPuzzle.Initialize(10, 10);
	myPuzzle.setMonsterPos(8, 8);
	myPuzzle.setPrincessPos(9, 9);
	myPuzzle.setMyPos(0, 0);
	int lineCount = 0;
	while (!file.eof()) {
		std::string command;
		getline(file, command);
		++lineCount;
		if (command == "q" || command == "quit") break;
		int i = 0;
		while (command[i] == ' ') ++i;
		if (command.substr(i, 2) != "go") {
			system("cls");
			std::cout << "Invalid input at line " << lineCount << std::endl;
			system("pause");
			return;
		}
		else {
			i += 2;
			while (command[i] == ' ') ++i;
			if (myPuzzle.move(command.substr(i, command.size() - i)) == false) {
				system("cls");
				std::cout << "Invalid move at line " << lineCount << std::endl;
				system("pause");
				return;
			}	
		}
		if (myPuzzle.judgeWin() == -1) {
			system("cls");
			std::cout << "You lose!" << std::endl;
			system("pause");
			return;
		}
		else if (myPuzzle.judgeWin() == 1) {
			system("cls");
			std::cout << "You Win!" << std::endl;
			system("pause");
			return;
		}
	}
	system("cls");
	std::cout << "You haven't finish" << std::endl;
	system("pause");
	return ;
}

void player::quickStart()
{
	myPuzzle.Initialize(10, 10);
	//randomly initialize the puzzle
	int x1, y1, x2, y2, x3, y3;
	srand(time(NULL));
	x1 = rand() % 10;
	y1 = rand() % 10;
	myPuzzle.setMyPos(x1, y1);
	srand(time(NULL));
	x2 = rand() % 10;
	y2 = rand() % 10;
	while (x2 == x1 && y2 == y1) {
		srand(time(NULL));
		x2 = rand() % 10;
		y2 = rand() % 10;
	}
	myPuzzle.setMonsterPos(x2, y2);
	srand(time(NULL));
	x3 = rand() % 10;
	y3 = rand() % 10;
	while ((x3 == x1 && y3 == y1) || (x3 == x2 && y3 == y2)) {
		srand(time(NULL));
		x3 = rand() % 10;
		y3 = rand() % 10;
	}
	myPuzzle.setMonsterPos(x3, y3);
	//start playing
	play();
	return;
}

void player::start()
{
	//start game after setting
	int x, y;
	while (true) {
		std::cout << "input the size of puzzle (width & height):" << std::endl;
		std::cin >> x;
		std::cin >> y;
		if (myPuzzle.Initialize(x, y)) break;
		std::cout << "Puzzle size is too small, it must be greater than 5*5." << std::endl;
	}
	while (true) {
		std::cout << "input the position of the princess (x & y):" << std::endl;
		std::cin >> x;
		std::cin >> y;
		if (myPuzzle.setPrincessPos(x, y)) break;
		std::cout << "Invalid position" << std::endl;
	}
	while (true) {
		std::cout << "input the position of the monster (x & y):" << std::endl;
		std::cin >> x;
		std::cin >> y;
		if (myPuzzle.setMonsterPos(x, y)) break;
		std::cout << "Invalid position" << std::endl;
	}
	while (true) {
		std::cout << "input your position (x & y):" << std::endl;
		std::cin >> x;
		std::cin >> y;
		if (myPuzzle.setMyPos(x, y)) break;
		std::cout << "Invalid position" << std::endl;
	}
	//start playing
	play();
	return;
}

void player::play()
{
	while (true) {
		std::string command;
		std::string direction;
		std::string roomName;
		std::vector<std::string> exits;
		int pDist = 0;
		int mDist = 0;
		//show the puzzle on screen
		system("cls");
		myPuzzle.show();
		//print instructions on screen
		myPuzzle.analyze(roomName, exits, &pDist, &mDist);
		std::cout << "Welcome to the " << roomName << ". There are " << (int)(exits.size()) << " exits:";
		for (int i = 0; i < exits.size() - 1; ++i)
			std::cout << " " << exits[i];
		std::cout << " and " << exits.back() << "." << std::endl;
		std::cout << "Your distance to princess is: " << pDist << std::endl;
		std::cout << "Your distance to monster is: " << mDist << std::endl;
		std::cout << "Enter your command:"<< std::endl;
		std::cout << "quit game: q/quit" << std::endl;
		std::getline(std::cin, command);
		if (command == "q" || command == "quit") break;
		int i = 0;
		while (command[i] == ' ') ++i;
		if (command.substr(i, 2) != "go") {
			std::cout << "invalid input!" << std::endl;
			system("pause");
			continue;
		}
		else {
			i += 2;
			while (command[i] == ' ') ++i;
			direction = command.substr(i, command.size() - i);
		}
		//valid input, try to move
		if (myPuzzle.move(direction) == false) {
			std::cout << "Illegal move!" << std::endl;
			system("pause");
			continue;
		}
		else {
			if (myPuzzle.judgeWin() == -1) {
				system("cls");
				myPuzzle.show();
				std::cout << "You are eaten by the monster!" << std::endl;
				system("pause");
				break;
			}
			else if (myPuzzle.judgeWin() == 1) {
				system("cls");
				myPuzzle.show();
				std::cout << "You win!" << std::endl;
				system("pause");
				break;
			}
		}
	}
	return;
}


player::~player()
{
}
