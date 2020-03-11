#include "stdafx.h"
#include "Table.h"


Table::Table()
{
}


Table::~Table()
{
}

void Table::readFile(std::string filename)
{
	//The .txt will store the information in a format as below:
	//All the info should be shorter than 10 chars.
	//Student number and average score will be generate after readFile.
	//Example:
	//name   course_1   course_2   course_3 ... course_n 
	//mary   100        99         NULL         150      
	//......

	//read the file and put it into vector
	std::ifstream fin;
	fin.open(filename);
	std::string tempLine;
	std::string tempStr;
	getline(fin, tempLine);
	//read the table schema (first line)
	int i = 0;
	while (isalpha(tempLine[i])) i++;
	while (tempLine[i] == ' ') i++;
	while (i < tempLine.size()) {
		tempStr.clear();
		while (i < tempLine.size() && isalpha(tempLine[i])) {
			tempStr.push_back(tempLine[i]);
			i++;
		}
		courseList.push_back(tempStr);
		while (i < tempLine.size() && tempLine[i] == ' ') i++;
	}
	//read the data
	while (!fin.eof()) {
		getline(fin, tempLine);
		i = 0;
		student* temp = new student();
		while (isalpha(tempLine[i]) || tempLine[i] == '.')
			temp->name.push_back(tempLine[i++]);
		while (tempLine[i] == ' ') i++;
		int score = 0;
		int scoreSum = 0;
		int courseNum = 0;      //help record the course name of the score
		while (i < tempLine.size()) {
			score = 0;
			//skip the courses with 'NULL'
			if (isalpha(tempLine[i])) {
				courseNum++;
				while (i < tempLine.size() && isalpha(tempLine[i])) i++;
			}
			//read score
			if (i < tempLine.size() && isdigit(tempLine[i])) {
				while (i < tempLine.size() && isdigit(tempLine[i])) {
					score = 10 * score + tempLine[i] - '0';
					i++;
				}
				temp->scores.insert({ courseList[courseNum], score });
				courseNum++;
				scoreSum += score;
			}
			while (i < tempLine.size() && tempLine[i] == ' ') i++;
		}
		if (temp->scores.size() == 0) temp->scoreSum = 0;
		else
			temp->scoreSum = scoreSum;
		studentList.push_back(*temp);
	}
	fin.close();
	updateStat();
}

void Table::printFile(std::string filename)
{
	//write current table in .txt
	std::ofstream fout;
	fout.open(filename);
	//write table schema
	fout << std::left << std::setw(20) << std::setfill(' ') << "name";
	for (int courseID = 0; courseID < courseList.size(); courseID++) 
		fout << std::left << std::setw(20) << std::setfill(' ') << courseList[courseID];
	fout << std::endl;
	//write table data
	for (int stuID = 0; stuID < studentList.size(); stuID++) {
		fout << std::left << std::setw(20) << std::setfill(' ') << studentList[stuID].name;
		for (int courseID = 0; courseID < courseList.size(); courseID++) {
			std::left;
			std::setw(20);
			std::setfill(' ');
			if (studentList[stuID].scores.find(courseList[courseID]) != studentList[stuID].scores.end())
				fout << std::left << std::setw(20) << std::setfill(' ')
					 << studentList[stuID].scores[courseList[courseID]];
			else
				fout << std::left << std::setw(20) << std::setfill(' ') << "NULL";
		}
		if (stuID < studentList.size() - 1)
			fout << std::endl;
	}
	fout.close();
}

void Table::query()
{
	//table management query
	while (true) {
		std::cout << std::endl;
		std::cout << "What do you want to do?" << std::endl;
		std::cout << "Show the table: s" << std::endl;
		std::cout << "add student: as" << std::endl;
		std::cout << "add course: ac" << std::endl;
		std::cout << "delete student: ds" << std::endl;
		std::cout << "delete course: dc" << std::endl;
		std::cout << "change score: cs" << std::endl;
		std::cout << "quit: q" << std::endl;
		std::string order;
		std::cin >> order;
		if (order == "s") showTable();
		else if (order == "as") addStudent();
		else if (order == "ac") addCourse();
		else if (order == "ds") delStudent();
		else if (order == "dc") delCourse();
		else if (order == "cs") changeScore();
		else break;
	}
}

void Table::addStudent()
{
	system("cls");
	student* temp = new student();
	std::string input;
	std::cout << "What's his/her name?" << std::endl;
	std::cin >> temp->name;
	int courseCount = 0;
	int scoreSum = 0;
	for (int courseID = 0; courseID < courseList.size(); courseID++) {
		std::cout << "What's his/her score of " << courseList[courseID] << "?" << std::endl;
		std::cout << "Enter an int (default = NULL) :" << std::endl;
		std::cin >> input;
		int score = 0;
		int i = 0;
		for (i = 0; i < input.size(); i++) {
			if (isalpha(input[i]))
				break;
			score = 10 * score + input[i] - '0';
		}
		if (i == input.size()) {
			courseCount++;
			scoreSum += score;
			if (input.size())
				temp->scores.insert({ courseList[courseID], score });
		}
	}
	temp->scoreSum = scoreSum;
	studentList.push_back(*temp);
	updateStat();
	return;
}

void Table::addCourse()
{
	system("cls");
	std::cout << "What's the course's name?" << std::endl;
	std::string input;
	std::cin >> input;
	int courseID = 0;
	for (courseID = 0; courseID < courseList.size(); courseID++) 
		if (courseList[courseID] == input) break;
	if (courseID == courseList.size()) {
		courseList.push_back(input);
		std::cout << "Do you want to enter the students' scores? (y/[n])" << std::endl;
		std::cin >> input;
		//enter students' scores of this course
		if (input == "y") 
			for (int stuID = 0; stuID < studentList.size(); stuID++) {
				std::cout << "What's " << studentList[stuID].name << "'s score?" << std::endl;
				std::cin >> input;
				int score = 0;
				int i = 0;
				for (i = 0; i < input.size(); i++) {
					if (isalpha(input[i]))
						break;
					score = 10 * score + input[i] - '0';
				}
				if (i == input.size()) {
					studentList[stuID].scoreSum += score;
					if (input.size())
						studentList[stuID].scores.insert({ courseList.back(), score });
				}
			}
	}
	else {
		std::cout << "The course has existed" << std::endl;
		return;
	}
	updateStat();
	return;
}

void Table::delStudent()
{
	std::cout << "Please enter the student's number:" << std::endl;
	std::string input;
	int num = 0;
	std::cin >> input;
	int i = 0;
	for (i = 0; i < input.size(); i++) {
		if (isalpha(input[i]))
			break;
		num = 10 * num + input[i] - '0';
	}
	if (num > 0 && num - 1 < studentList.size())
		studentList.erase(studentList.begin() + num - 1);
	else
		std::cout << "No such student!" << std::endl;
	updateStat();
	return;
}

void Table::delCourse()
{
	std::cout << "Which course would you like to delete? (input course name)" << std::endl;
	std::string courseName;
	std::cin >> courseName;
	int courseID = 0;
	for (courseID = 0; courseID < courseList.size(); courseID++) {
		if (courseName == courseList[courseID])
			break;
	}
	if (courseID < courseList.size()) {
		courseList.erase(courseList.begin() + courseID);
		for (int stuID = 0; stuID < studentList.size(); stuID++) 
			if (studentList[stuID].scores.find(courseName) != studentList[stuID].scores.end())
				studentList[stuID].scores.erase(courseName);
	}
	else 
		std::cout << "No such course!" << std::endl;
	updateStat();
	return;
}

void Table::changeScore()
{
	std::cout << "Enter the student's number:" << std::endl;
	std::string input;
	int num = 0;
	std::cin >> input;
	int i = 0;
	for (i = 0; i < input.size(); i++) {
		if (isalpha(input[i]))
			break;
		num = 10 * num + input[i] - '0';
	}
	if (num > 0 && num - 1 < studentList.size()) {
		std::cout << "which subject would you like to change?" << std::endl;
		std::cin >> input;
		int courseID = 0;
		for (courseID = 0; courseID < courseList.size(); courseID++)
			if (courseList[courseID] == input) break;
		if (courseID < courseList.size()) {
			int score = 0;
			std::cout << "Please enter a score" << std::endl;
			std::cin >> input;
			for (i = 0; i < input.size(); i++) {
				if (isalpha(input[i]))
					break;
				score = 10 * score + input[i] - '0';
			}
			if (i < input.size()) return;   //Invalid score
			//Change score
			if (studentList[num - 1].scores.find(courseList[courseID]) != studentList[num - 1].scores.end())
				studentList[num - 1].scores.insert({ courseList[courseID], score });
			else
				studentList[num - 1].scores[courseList[courseID]] = score;
		}
		else
			std::cout << "No such course! (You should add course first)" << std::endl;
	}
	else
		std::cout << "No such student!" << std::endl;
	updateStat();
	return;
}

void Table::updateStat()
{
	sumList.clear();
	maxList.clear();
	minList.clear();
	courseTaker.clear();
	//update sumList,minList,maxList
	for (int courseID = 0; courseID < courseList.size(); courseID++) {
		int sum = 0;
		int count = 0;
		int Max = INT_MIN;
		int Min = INT_MAX;
		for (int stuID = 0; stuID < studentList.size(); stuID++)
			if (studentList[stuID].scores.find(courseList[courseID]) != studentList[stuID].scores.end()) {
				int score = studentList[stuID].scores[courseList[courseID]];
				if (Max < score) Max = score;
				if (Min > score) Min = score;
				sum += score;
				count++;
			}
		maxList.push_back(Max);
		minList.push_back(Min);
		sumList.push_back(sum);
		courseTaker.push_back(count);
	}
		return;
}

void Table::showTable()
{
	//show current table on screen
	int x, y;
	system("cls");
	//print the table schema
	x = 0;
	y = 0;
	SetCursorPosition(x, y);
	std::cout << "NO";
	x += 10;
	SetCursorPosition(x, y);
	std::cout << "name";
	for (int i = 0; i < courseList.size(); i++) {
		x += 10;
		SetCursorPosition(x, y);
		std::cout << courseList[i];
	}
	x += 10;
	SetCursorPosition(x, y);
	std::cout << "average";
	//print table data
	for (int stuID = 0; stuID < studentList.size(); stuID++) {
		x = 0;
		y = stuID + 1;
		SetCursorPosition(x, y);
		std::cout << stuID + 1;
		x += 10;
		SetCursorPosition(x, y);
		std::cout << studentList[stuID].name;
		for (int courseID = 0; courseID < courseList.size(); courseID++) {
			x += 10;
			SetCursorPosition(x, y);
			//if the student has this course
			if (studentList[stuID].scores.find(courseList[courseID]) != studentList[stuID].scores.end())
				std::cout << studentList[stuID].scores[courseList[courseID]];
			else
				std::cout << "NULL";
		}
		x += 10;
		SetCursorPosition(x, y);
		std::cout << studentList[stuID].scoreSum / (1.0 * studentList[stuID].scores.size());
	}
	//print avg
	x = 10;
	y++;
	SetCursorPosition(x, y);
	std::cout << "average";
	for (int courseID = 0; courseID < courseList.size(); courseID++) {
		x += 10;
		SetCursorPosition(x, y);
		if (courseTaker[courseID] == 0)
			std::cout << "NULL";
		else
			std::cout << 1.0 * sumList[courseID] / (1.0 * courseTaker[courseID]);
	}
	//print max
	x = 10;
	y++;
	SetCursorPosition(x, y);
	std::cout << "max";
	for (int courseID = 0; courseID < courseList.size(); courseID++) {
		x += 10;
		SetCursorPosition(x, y);
		if (courseTaker[courseID] == 0)
			std::cout << "NULL";
		else
			std::cout << maxList[courseID];
	}
	//print min
	x = 10;
	y++;
	SetCursorPosition(x, y);
	std::cout << "min";
	for (int courseID = 0; courseID < courseList.size(); courseID++) {
		x += 10;
		SetCursorPosition(x, y);
		if (courseTaker[courseID] == 0)
			std::cout << "NULL";
		else
			std::cout << minList[courseID];
	}
	std::cout << std::endl;
	return;
}

void Table::SetCursorPosition(const int x, const int y)
{
	COORD   position; 
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	return;
}

Table::student::student():scoreSum(0)
{
}
