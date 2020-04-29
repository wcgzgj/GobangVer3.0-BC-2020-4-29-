#include "ChessRobot.h"
#include "Map.h"
#include "Draw.h"
#include <iostream>
#include <vector>

ChessRobot::ChessRobot(void)
{
}


ChessRobot::~ChessRobot(void)
{
}

void ChessRobot::AI(Map mp)
{//程序先给每个空位更新权值
	//然后再获得权值最大的棋子
	//最后将权值最大的棋子放置在棋盘中
	if(mp.getNum()==0)
	{
		putChess(mp,Chess((mp.getSize()+1)/2,(mp.getSize()+1)/2));
		return;
	}
	giveAllValue(mp);
	Chess ce=getBestChess(mp);
	putChess(mp,ce);
}

int ChessRobot::getAtkValue(Map mp, Chess ce)
{
	int allValue[7];
	//将七种棋型的个数存入数组
	allValue[0]=mp.countLinkFive(ce);
	allValue[1]=mp.countLiveFour(ce);
	allValue[2]=mp.countRushFour(ce);
	allValue[3]=mp.countLiveThree(ce);
	allValue[4]=mp.countSleepThree(ce);
	allValue[5]=mp.countLiveTwo(ce);
	allValue[6]=mp.countSleepTwo(ce);
	int atkValue=0;
	atkValue+=allValue[0]*TWO_VAL;
	atkValue+=allValue[1]*FIFTEEN_VAL;
	atkValue+=getFibHand(allValue)*SIX_VAL;
	atkValue+=allValue[2]*EIGHT_VAL;
	atkValue+=allValue[3]*TEN_VAL;
	atkValue+=allValue[4]*TWELVE_VAL;
	atkValue+=allValue[5]*FOURTEEN_VAL;
	atkValue+=allValue[6]*FIFTEEN_VAL;
	return atkValue;
}

int ChessRobot::getDefValue(Map mp, Chess ce)
{
	//将friendColor和enemyColor互换
	mp.reverseFriendEnemy();

	int allValue[7];
	//将七种棋型的个数存入数组
	allValue[0]=mp.countLinkFive(ce);
	allValue[1]=mp.countLiveFour(ce);
	allValue[2]=mp.countRushFour(ce);
	allValue[3]=mp.countLiveThree(ce);
	allValue[4]=mp.countSleepThree(ce);
	allValue[5]=mp.countLiveTwo(ce);
	allValue[6]=mp.countSleepTwo(ce);
	int defValue=0;
	defValue+=allValue[0]*THREE_VAL;
	defValue+=allValue[1]*FOUR_VAL;
	defValue+=getFibHand(allValue)*SEVEN_VAL;
	defValue+=allValue[2]*NINE_VAL;
	defValue+=allValue[3]*ELEVEN_VAL;
	defValue+=allValue[4]*THIRTEEN_VAL;
	defValue+=allValue[5]*FIFTEEN_VAL/2;
	defValue+=allValue[6]*FIFTEEN_VAL/2/2;

	//用完后将friendColor和enemyColor换回来
	mp.reverseFriendEnemy();
	return defValue;
}

int ChessRobot::getFibHand(int allValue[])
{
	int count=0;
	if(allValue[3]>=2) count++;//双活三禁手
	if(allValue[1]>=2 || allValue[2]>=2 || (allValue[1]&&allValue[2])) count++;//双四禁手
	//长连禁手不用管
	return count;
}

int ChessRobot::someWin(Map mp)
{
	for(int i=1;i<=mp.getSize();i++)
	{
		for(int j=1;j<=mp.getSize();j++)
		{
			if(mp.getChess(i,j).color==mp.getFriendColor() && mp.countLinkFive(Chess(i,j))>0) 
				return 1;//1是机器人赢
			mp.reverseFriendEnemy();//原来的朋友变成敌人
			if(mp.getChess(i,j).color==mp.getFriendColor() && mp.countLinkFive(Chess(i,j))>0) 
			{
				mp.reverseFriendEnemy();
				return 2;//2是玩家赢
			}
			mp.reverseFriendEnemy();//原来的敌人又变回朋友
		}
	}
	return 0;
}

void ChessRobot::giveAllValue(Map mp)
{
	for(int i=1;i<=mp.getSize();i++)
	{
		for(int j=1;j<=mp.getSize();j++)
		{
			Chess tmpCe=mp.getChess(i,j);
			if(tmpCe.color==NONE)
			{
				mp.setAtkValue(tmpCe,getAtkValue(mp,tmpCe));
				mp.setDefValue(tmpCe,getDefValue(mp,tmpCe));
			}
		}
	}
	return;
}

void ChessRobot::outputAtkDefValue(Map mp)
{
	Draw dw;
	for(int i=1;i<=mp.getSize();i++)
	{
		for(int j=1;j<=mp.getSize();j++)
		{
			std::cout<<mp.getAtkValue(Chess(i,j))<<" ";
		}
		std::cout<<std::endl;
	}
	dw.printEndl(3);
	for(int i=1;i<=mp.getSize();i++)
	{
		for(int j=1;j<=mp.getSize();j++)
		{
			std::cout<<mp.getDefValue(Chess(i,j))<<" ";
		}
		std::cout<<std::endl;
	}
	return;
}

int ChessRobot::inputIsOk(Map mp,Chess ce)
{//超范围或者下棋的位置非空，都是错误的
	if(ce.col<1 || ce.col>mp.getSize() || ce.row<1 || ce.row>mp.getSize() ||
		mp.getChess(ce.row,ce.col).color!=NONE) return 0;
	else return 1;
}

Chess ChessRobot::getBestChess(Map mp)
{
	if(mp.getNum()==0) return Chess((mp.getSize()+1)/2,(mp.getSize()+1)/2);
	using std::vector;
	vector<Chess> chessChain;
	
	for (int i=1;i<=mp.getSize();i++)
	{
		for (int j=1;j<=mp.getSize();j++)
		{
			if(mp.getChess(i,j).color==NONE) 
			{
				chessChain.push_back(mp.getChess(i,j));
			}
		}

	}
	Chess maxAtk;
	Chess maxDef;
	vector<Chess>::iterator it;
	int countNone=0;
	int countLen=0;
	//it=chessChain.begin();
	//while(it!=chessChain.end())
	//{
	//	countLen++;
	//	if((*it).color==NONE) countNone++;
	//	it++;
	//}
	////如果棋盘为空，在棋盘中间放子
	//if(countLen==countNone) return Chess((mp.getSize()+1)/2,(mp.getSize()+1)/2);<<=====
	//if(mp.getNum()==0) return Chess((mp.getSize()+1)/2,(mp.getSize()+1)/2);

	it=chessChain.begin();
	maxAtk=*it;
	while(it!=chessChain.end())
	{
		if((*it).atkValue>maxAtk.atkValue) maxAtk=*it;
		it++;
	}

	it=chessChain.begin();
	maxDef=*it;
	while(it!=chessChain.end())
	{
		if((*it).defValue>maxDef.defValue) maxDef=*it;
		it++;
	}

	if(maxAtk.atkValue>maxDef.defValue) return maxAtk;
	else return maxDef;
}

void ChessRobot::putChess(Map mp, Chess ce)
{
	mp.putAIChess(ce);
	return;
}
