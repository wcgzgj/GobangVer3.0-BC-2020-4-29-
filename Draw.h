#pragma once
#include "Map.h"
#include <string>
class Draw
{
public:
	Draw(void);
	~Draw(void);
	void drawMap(Map mp);
	void errorReport();
	void youWin(Map mp);
	void youLose(Map mp);
	void printEndl(int n);
	void printBlock(int n);
	void outputString(std::string str);
	void pleaseInput();
};

