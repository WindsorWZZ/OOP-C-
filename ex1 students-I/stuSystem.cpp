#include "stdafx.h"
#include "stuSystem.h"


stuSystem::stuSystem()
{
}


stuSystem::~stuSystem()
{
}

void stuSystem::showTable()
{
	system("cls");
	cout << std::left << setw(20) << "no"
		<< std::left << setw(20) << "name"
		<< std::left << setw(20) << "score1"
		<< std::left << setw(20) << "score2"
		<< std::left << setw(20) << "score3"
		<< std::left << setw(20) << "average" << endl;
	for (int i = 0; i < table.size(); i++) {
		cout << std::left << setw(20) << i + 1
			<< std::left << setw(20) << table[i].name
			<< std::left << setw(20) << table[i].score_1
			<< std::left << setw(20) << table[i].score_2
			<< std::left << setw(20) << table[i].score_3
			<< std::left << setw(20) << table[i].average << endl;
	}
	cout << std::left << setw(20) << ' '
		<< std::left << setw(20) << "Average"
		<< std::left << setw(20) << Sum[0] / (1.0 * table.size())
		<< std::left << setw(20) << Sum[1] / (1.0 * table.size())
		<< std::left << setw(20) << Sum[2] / (1.0 * table.size()) << endl;
	cout << std::left << setw(20) << ' '
		<< std::left << setw(20) << "Max"
		<< std::left << setw(20) << Max[0] 
		<< std::left << setw(20) << Max[1] 
		<< std::left << setw(20) << Max[2] << endl;
	cout << std::left << setw(20) << ' '
		<< std::left << setw(20) << "Min"
		<< std::left << setw(20) << Min[0]
		<< std::left << setw(20) << Min[1]
		<< std::left << setw(20) << Min[2] << endl;
	return;
}

void stuSystem::add()
{
	system("cls");
	student* temp = new student();
	cout << "what's his/her name?" << endl;
	cin >> temp->name;
	cout << "input score1:" << endl;
	cin >> temp->score_1;
	cout << "input score2:" << endl;
	cin >> temp->score_2;
	cout << "input score3:" << endl;
	cin >> temp->score_3;
	cout << "input finished" << endl;
	temp->average = (temp->score_1 + temp->score_2 + temp->score_3) / 3.0;
	table.push_back(*temp);
	updateStat();
	return;
}

void stuSystem::remove()
{
	system("cls");
	cout << "which one do you want to remove? input a number" << endl;
	int num;
	cin >> num;
	if (num > table.size()) cout << "no such student" << endl;
	else
		table.erase(table.begin() + num - 1);
	updateStat();
	return;
}

void stuSystem::interaction()
{
	while (true) {
		cout << "What do you want to do?" << endl;
		cout << "Show the table: s" << endl;
		cout << "add: a" << endl;
		cout << "remove: r" << endl;
		cout << "quit: q" << endl;
		string order;
		cin >> order;
		if (order.length() > 1) {
			cout << "wrong input!" << endl;
			continue;
		}
		if (order[0] == 's') showTable();
		else if (order[0] == 'a') add();
		else if (order[0] == 'r') remove();
		else break;
	}
}

void stuSystem::readFile()
{
	//read the file and put it into vector
	ifstream fin;
	fin.open("NameList.txt");
	string tempLine;
	while (!fin.eof()) {
		getline(fin, tempLine);
		if (tempLine[0] > '9' || tempLine[0] < '0')
			continue;
		student* temp = new student();
		int i = 2;
		while (tempLine[i] == ' ') i++;
		while (isalpha(tempLine[i]) || tempLine[i] == '.')
			temp->name.push_back(tempLine[i++]);
		while (tempLine[i] == ' ') i++;
		while (isdigit(tempLine[i]))
			temp->score_1 = tempLine[i++] - '0';
		while (tempLine[i] == ' ') i++;
		while (isdigit(tempLine[i]))
			temp->score_2 = tempLine[i++] - '0';
		while (tempLine[i] == ' ') i++;
		while (isdigit(tempLine[i]))
			temp->score_3 = tempLine[i++] - '0';
		temp->average = (temp->score_1 + temp->score_2 + temp->score_3) / 3.0;
		table.push_back(*temp);
	}
	updateStat();
	fin.close();
	return;
}

void stuSystem::writeFile()
{
	//write the data into the file
	ofstream fout;
	fout.open("NameList.txt");
	fout << std::left << setw(20) << setfill(' ') << "no"
		<< std::left << setw(20) << setfill(' ') << "name"
		<< std::left << setw(20) << setfill(' ') << "score1"
		<< std::left << setw(20) << setfill(' ') << "score2"
		<< std::left << setw(20) << setfill(' ') << "score3"
		<< std::left << setw(20) << setfill(' ') << "average" << endl;
	for (int i = 0; i < table.size(); i++) {
		fout << std::left << setw(20) << setfill(' ') << i
			<< std::left << setw(20) << setfill(' ') << table[i].name
			<< std::left << setw(20) << setfill(' ') << table[i].score_1
			<< std::left << setw(20) << setfill(' ') << table[i].score_2
			<< std::left << setw(20) << setfill(' ') << table[i].score_3
			<< std::left << setw(20) << setfill(' ') << table[i].average << endl;
	}
	fout.close();
}

void stuSystem::updateStat()
{
	//update score_1
	int sum = 0;
	int max = INT_MIN;
	int min = INT_MAX;
	for (int i = 0; i < table.size(); i++) {
		sum += table[i].score_1;
		if (table[i].score_1 > max) max = table[i].score_1;
		if (table[i].score_1 < min) min = table[i].score_1;
	}
	Sum[0] = sum;
	Max[0] = max;
	Min[0] = min;
	//update score_2
	sum = 0;
	max = INT_MIN;
	min = INT_MAX;
	for (int i = 0; i < table.size(); i++) {
		sum += table[i].score_2;
		if (table[i].score_2 > max) max = table[i].score_2;
		if (table[i].score_2 < min) min = table[i].score_2;
	}
	Sum[1] = sum;
	Max[1] = max;
	Min[1] = min;
	//update score_3
	sum = 0;
	max = INT_MIN;
	min = INT_MAX;
	for (int i = 0; i < table.size(); i++) {
		sum += table[i].score_3;
		if (table[i].score_3 > max) max = table[i].score_3;
		if (table[i].score_3 < min) min = table[i].score_3;
	}
	Sum[2] = sum;
	Max[2] = max;
	Min[2] = min;
}
