#pragma once
#include "puzzle.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
class player
{
public:
	player();
	void query();
	void readFile();
	void quickStart();
	void start();
	void play();
	virtual ~player();
private:
	puzzle myPuzzle;
};

