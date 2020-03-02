// StudentsI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stuSystem.h"
using namespace std;
int main()
{
	stuSystem sys;
	sys.readFile();
	sys.showTable();
	sys.interaction();
	sys.writeFile();
    return 0;
}