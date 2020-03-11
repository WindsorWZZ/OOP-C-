// Students II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Table.h"
using namespace std;
int main()
{
	Table table;
	table.readFile("stuTable.txt");
	table.showTable();
	table.query();
	table.printFile("stuTable.txt");
	system("pause");
	return 0;
}