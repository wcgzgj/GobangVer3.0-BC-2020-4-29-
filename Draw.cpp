#include "Draw.h"
#include "Map.h"
#include "ChessRobot.h"
#include <iostream>
#include <string>
#include <Windows.h>


Draw::Draw(void)
{
}


Draw::~Draw(void)
{
}

void Draw::drawMap(Map mp)
{
  /*┎┬┬┬┬┬┒
	┠┼┼┼┼┼┨
	┠┼┼○●┼┨
	┠┼┼●┼┼┨
	┠┼┼┼┼┼┨
	┠┼┼┼┼┼┨
	┖┷┷┷┷┷┚*/
	char number[6]={'A','B','C','D','E','F'};//两位数换成字母，保证输出不会出错。
	printEndl(3);
	printBlock(8);
	for(int i=1;i<=mp.getSize();i++)
	{
		if(i<10) std::cout<<i<<" ";
		else std::cout<<number[i-10]<<" ";
	}
	printEndl(1);
	printBlock(5);
	outputString("┎ ");
	for(int i=1;i<=mp.getSize();i++) outputString("┬ ");
	outputString("┒");
	printEndl(1);
	for (int i=1;i<=mp.getSize();i++)
	{
		printBlock(4);
		if(i<10) std::cout<<i;
		else std::cout<<number[i-10];
		outputString("┠ ");
		for(int j=1;j<=mp.getSize();j++)
		{
			if(mp.getChess(i,j).color==NONE) outputString("┼ ");
			else if(mp.getChess(i,j).color==BLACK) outputString("○");
			else outputString("●");
		}
		outputString("┨");
		printEndl(1);
	}
	printBlock(5);
	outputString("┖ ");
	for(int i=1;i<=mp.getSize();i++) outputString("┷ ");
	outputString("┚");

	printEndl(3);
}

void Draw::errorReport()
{
	Draw dw;
	system("cls");
	dw.printEndl(5);
	dw.printBlock(5);
	dw.outputString("输入错误，请重新输入！");
	dw.printEndl(5);
	Sleep(2000);
	return;
}

void Draw::youWin(Map mp)
{
	system("cls");
	printEndl(10);
	printBlock(10);
	std::cout<<"你赢了！"<<std::endl;
	Sleep(3000);
	system("cls");
	drawMap(mp);
	return;
}

void Draw::youLose(Map mp)
{
	system("cls");
	printEndl(10);
	printBlock(10);
	std::cout<<"你输了！"<<std::endl;
	Sleep(3000);
	system("cls");
	drawMap(mp);
	return;
}

void Draw::printEndl(int n)
{
	for (int i=0;i<n;i++) std::cout<<std::endl;
}

void Draw::printBlock(int n)
{
	for(int i=0;i<n;i++) std::cout<<" ";
}

void Draw::outputString(std::string str)
{
	std::cout<<str;
}

void Draw::pleaseInput()
{
	printEndl(3);
	outputString("请输入 下棋的 (横,纵) 坐标:");
}
