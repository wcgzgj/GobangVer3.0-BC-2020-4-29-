#include "ChessRobot.h"
#include "Draw.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
using namespace std;

int getInput();

int main()
{
	Map mp;
	ChessRobot cr;
	Draw dr;
	mp.iniMap(15);//棋盘大小 15X15
	mp.iniColor(BLACK);//机器人方为黑子
	dr.drawMap(mp);
	int result=0;
	while(1)
	{
		cr.AI(mp);
		system("cls");
		dr.drawMap(mp);
		result=cr.someWin(mp);
		if(result==1)
		{
			Sleep(2000);
			break;
		}
		dr.pleaseInput();
		while(1)
		{
			int x=getInput();
			int y=getInput();
			if(cr.inputIsOk(mp,Chess(x,y)))
			{
				mp.putPlayChess(Chess(x,y));
				system("cls");
				dr.drawMap(mp);
				break;
			}
			else
			{
				dr.errorReport();
				system("cls");
				dr.drawMap(mp);
				dr.pleaseInput();
				continue;
			}
		}
		result=cr.someWin(mp);
		if(result==2)
		{
			Sleep(2000);
			break;
		}
	}
	
	if(result==1)
	{
		dr.youLose(mp);
		dr.printEndl(10);
	}
	else
	{
		dr.youWin(mp);
		dr.printEndl(10);
	}
	system("pause");
	return 0;
}

int getInput()
{
	string x;
	cin>>x;
	if(x=="a" || x=="A") return 10;
	if(x=="b" || x=="B") return 11;
	if(x=="c" || x=="C") return 12;
	if(x=="d" || x=="D") return 13;
	if(x=="e" || x=="E") return 14;
	if(x=="f" || x=="F") return 15;
	int a=atoi(x.c_str());
	return a;
}
