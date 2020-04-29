#include "Map.h"
#include "Draw.h"
#include <iostream>
#include<vector>
#include <Windows.h>
Map::Map(void)
{
	num=0;
}


Map::~Map(void)
{
}

void Map::iniMap(int size)
{
	this->size=size;
	this->map=new Chess *[size+2];//申请的空间比棋盘大小大一，是为了让下标从1开始
	for(int i=0;i<size+2;i++) map[i]=new Chess[size+2];
	for(int j=0;j<size+1;j++) map[0][j]=Chess(NONE,-1,-1,0,j,true); 
	for(int i=0;i<size+1;i++) map[i][0]=Chess(NONE,-1,-1,i,0,true);
	for(int i=0;i<size+2;i++) map[i][size+1]=Chess(NONE,-1,-1,i,size+1,true);
	for(int j=0;j<size+2;j++) map[size+1][j]=Chess(NONE,-1,-1,size+1,j,true);
	for(int i=1;i<=size;i++)
	{
		for(int j=1;j<=size;j++)
		{
			map[i][j]=Chess(NONE,0,0,i,j,false);
		}
	}
}

int Map::getSize()
{
	return size;
}


int Map::getFriendColor()
{
	return this->friendColor;
}

void Map::setAtkValue(Chess ce,int atkValue)
{
	map[ce.row][ce.col].atkValue=atkValue;
	return;
}

void Map::setDefValue(Chess ce,int defValue)
{
	map[ce.row][ce.col].defValue=defValue;
	return;
}

int Map::getAtkValue(Chess ce)
{
	return map[ce.row][ce.col].atkValue;
}

int Map::getDefValue(Chess ce)
{
	return map[ce.row][ce.col].defValue;
}

void Map::giveMapFriend()
{
	std::cout<<"请输入友方棋子个数"<<std::endl;
	int n;
	std::cin>>n;
	std::cout<<"请输入"<<n<<"个棋子的位置"<<std::endl;
	int x,y;
	for(int i=0;i<n;i++)
	{
		std::cin>>x>>y;
		map[x][y].color=friendColor;
	}
	//system("cls");
}

void Map::giveMapEnemy()
{
	std::cout<<"请输入敌方棋子个数"<<std::endl;
	int n;
	std::cin>>n;
	std::cout<<"请输入"<<n<<"个棋子的位置"<<std::endl;
	int x,y;
	for(int i=0;i<n;i++)
	{
		std::cin>>x>>y;
		map[x][y].color=enemyColor;
	}
}

void Map::putAIChess(Chess ce)
{//不整体赋值，是因为没有必要，只赋color可以节省时间
	Draw dr;
	numPlus();
	system("cls");
	dr.printEndl(5);
	map[ce.row][ce.col].color=friendColor;
	/*std::cout<<"机器子颜色: "<<defineToString(map[ce.row][ce.col].color)<<std::endl;
	std::cout<<"机器落子位置: ("<<ce.row<<","<<ce.col<<")"<<std::endl;
	Sleep(2000);*/
	return;
}

void Map::putPlayChess(Chess ce)
{
	numPlus();
	map[ce.row][ce.col].color=enemyColor;
	return;
}

void Map::outputMap()
{
	for(int i=1;i<=size;i++)
	{
		for (int j=1;j<=size;j++)
		{
			//std::cout<<"("<<map[i][j].row<<","<<map[i][j].col<<") ";
			std::cout<<map[i][j].atkValue<<" ";
		}
		std::cout<<std::endl;
	}
}

void Map::iniColor(int color)
{
	this->friendColor=color;
	if(friendColor==BLACK) enemyColor=WHITE;
	else enemyColor=BLACK;
}

void Map::reverseFriendEnemy()
{
	if(this->friendColor==BLACK)
	{
		this->friendColor=WHITE;
		this->enemyColor=BLACK;
	}
	else
	{
		this->friendColor=BLACK;
		this->enemyColor=WHITE;
	}
	return;
}

int Map::getNum(Chess ce,int dir)
{
	switch(dir)
	{
	case LAY:
		return getLayNum(ce);
	case STAND:
		return getStandNum(ce);
	case MAIN:
		return getMainNum(ce);
	case VICE:
		return getViceNum(ce);
	default:
		return 0;
	}
}

int Map::getNum()
{
	return this->num;
}

void Map::numPlus()
{
	this->num++;
}

void Map::outputChess(Chess ce)
{	
	/*int color;
	int atkValue;
	int defValue;
	int row;
	int col;
	bool isBoundry;*/
	std::cout<<"color:"<<defineToString(ce.color)<<std::endl;
	std::cout<<"atkValue:"<<ce.atkValue<<std::endl;
	std::cout<<"defValue:"<<ce.defValue<<std::endl;
	std::cout<<"row & col: ("<<ce.row<<","<<ce.col<<")"<<std::endl;
	std::cout<<"isBoundry:"<<boolToString(ce.isBoundry)<<std::endl;
	Draw dw;
	dw.printEndl(2);
}

int Map::linkFive(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if(ce1.color==ce2.color && 
		ce2.color==ce3.color && 
		ce3.color==ce4.color && 
		ce4.color==ce5.color && 
		ce5.color==friendColor) return 1;
	return 0;
}

int Map::liveFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if(ce1.color==ce6.color && 
		ce6.color==NONE && 
		ce2.color==ce3.color && 
		ce3.color==ce4.color && 
		ce4.color==ce5.color && 
		ce5.color==friendColor) return 1;
	return 0;
}

int Map::rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if((ce2.color==ce3.color && 
		ce3.color==ce4.color && 
		ce4.color==ce5.color && 
		ce5.color==friendColor && 
		ce1.color==NONE && 
		ce6.color==enemyColor) ||
		(ce2.color==ce3.color && 
		ce3.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce6.color==NONE && 
		ce1.color==enemyColor)) return 1;
	return 0;
}

int Map::rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if((ce1.color==ce2.color &&
		ce2.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==friendColor && 
		ce4.color==NONE) ||
		(ce1.color==ce4.color &&
		ce4.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==friendColor && 
		ce2.color==NONE)) return 1;
	if(ce1.color==ce2.color && 
		ce2.color==ce4.color && 
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce3.color==NONE) return 1;
	return 0;
}

int Map::liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if(ce1.color==ce5.color && 
		ce5.color==NONE && 
		ce2.color==ce3.color &&
		ce3.color==ce4.color && 
		ce4.color== friendColor) return 1;
	return 0;
}

int Map::liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if((ce1.color==ce4.color &&
		ce4.color==ce6.color &&
		ce6.color==NONE && 
		ce2.color==ce3.color && 
		ce3.color==ce5.color &&
		ce5.color==friendColor) ||
		(ce1.color==ce3.color &&
		ce3.color==ce6.color &&
		ce6.color==NONE && 
		ce2.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor)) return 1;
	return 0;
}

int Map::sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if(ce1.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce2.color==ce3.color && 
		ce3.color==NONE) return 1;
	if(ce1.color==ce2.color &&
		ce2.color==ce5.color && 
		ce5.color==friendColor && 
		ce4.color==ce3.color &&
		ce3.color==NONE) return 1;
	if(ce1.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==friendColor && 
		ce2.color==ce4.color &&
		ce4.color==NONE) return 1;
	return 0;
}

int Map::sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if(ce1.color==ce2.color &&
		ce2.color==NONE &&
		ce3.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce6.color==enemyColor) return 1;
	if(ce5.color==ce6.color &&
		ce6.color==NONE && 
		ce3.color==ce4.color &&
		ce4.color==ce2.color &&
		ce2.color==friendColor && 
		ce1.color==enemyColor) return 1;
	if(ce1.color==ce3.color && 
		ce3.color==NONE && 
		ce2.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce6.color==enemyColor) return 1;
	if(ce4.color==ce6.color &&
		ce6.color==NONE && 
		ce2.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==friendColor && 
		ce1.color==enemyColor) return 1;
	if(ce1.color==ce4.color &&
		ce4.color==NONE && 
		ce2.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==friendColor && 
		ce6.color==enemyColor) return 1;
	if(ce3.color==ce6.color &&
		ce6.color==NONE && 
		ce2.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor && 
		ce1.color==enemyColor) return 1;
	return 0;
}

int Map::sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6,Chess ce7)
{
	if(ce1.color==ce7.color &&
		ce7.color==enemyColor && 
		ce2.color==ce6.color &&
		ce6.color==NONE && 
		ce3.color==ce4.color &&
		ce4.color==ce5.color &&
		ce5.color==friendColor) return 1;
	return 0;
}

int Map::liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4)
{
	if(ce1.color==ce4.color &&
		ce4.color==friendColor &&
		ce2.color==ce3.color &&
		ce3.color==NONE) return 1;
	return 0;
}

int Map::liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if(ce1.color==ce3.color &&
		ce3.color==ce5.color &&
		ce5.color==NONE && 
		ce2.color==ce4.color &&
		ce4.color==friendColor) return 1;
	return 0;
}

int Map::liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if(ce1.color==ce2.color &&
		ce2.color==ce5.color &&
		ce5.color==ce6.color &&
		ce6.color==NONE && 
		ce3.color==ce4.color &&
		ce4.color==friendColor) return 1;
	return 0;
}

int Map::sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5)
{
	if(ce1.color==ce5.color &&
		ce5.color==friendColor && 
		ce2.color==ce3.color &&
		ce3.color==ce4.color &&
		ce4.color==NONE) return 1;
	return 0;
}

int Map::sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6)
{
	if(ce1.color==ce2.color &&
		ce2.color==ce3.color &&
		ce3.color==NONE && 
		ce5.color==ce4.color &&
		ce4.color==friendColor &&
		ce6.color==enemyColor) return 1;
	if(ce4.color==ce5.color &&
		ce5.color==ce6.color &&
		ce6.color==NONE &&
		ce2.color==ce3.color && 
		ce3.color==friendColor &&
		ce1.color==enemyColor) return 1;
	if(ce1.color==ce2.color &&
		ce2.color==ce4.color &&
		ce4.color==NONE && 
		ce5.color==ce3.color && 
		ce3.color==friendColor && 
		ce6.color==enemyColor) return 1;
	if(ce5.color==ce6.color &&
		ce6.color==ce3.color &&
		ce3.color==NONE &&
		ce2.color==ce4.color &&
		ce4.color==friendColor &&
		ce1.color==enemyColor) return 1;
	if(ce1.color==ce3.color &&
		ce3.color==ce4.color &&
		ce4.color==NONE && 
		ce2.color==ce5.color &&
		ce5.color==friendColor && 
		ce6.color==enemyColor) return 1;
	if(ce3.color==ce4.color && 
		ce4.color==ce6.color &&
		ce6.color==NONE && 
		ce2.color==ce5.color &&
		ce5.color==friendColor && 
		ce1.color==enemyColor) return 1;
	return 0;
}

Chess Map::getNext(Chess ce, int dir)
{//如果被查找的棋子本身超出边界，返回错误棋子
	if(ce.col<0 || ce.isBoundry==true) return getErrorChess();
	Chess tmp;
	switch(dir)
	{
	case LAY:
		tmp=rightNext(ce);
		break;
	case STAND:
		tmp=downNext(ce);
		break;
	case MAIN:
		tmp=rightDownNext(ce);
		break;
	case VICE:
		tmp=rightUpNext(ce);
		break;
	default:
		break;
	}
	if(tmp.col<0 || tmp.isBoundry==true) return Chess("ERROR");
	return tmp;
}

Chess Map::getPrev(Chess ce, int dir)
{//如果被查找的棋子本身超出边界，返回错误棋子
	if(ce.col<0 || ce.isBoundry==true) return getErrorChess();
	Chess tmp;
	switch(dir)
	{
	case LAY:
		tmp=leftNext(ce);
		break;
	case STAND:
		tmp=upNext(ce);
		break;
	case MAIN:
		tmp=leftUpNext(ce);
		break;
	case VICE:
		tmp=leftDownNext(ce);
		break;
	default:
		break;
	}
	if(tmp.col<0 || tmp.isBoundry==true) return Chess("ERROR");
	return tmp;
}

Chess Map::getChess(int x,int y)
{
	return map[x][y];
}


void Map::outputOneDVector(std::vector<Chess> ce)
{
	using std::vector;
	vector<Chess>::iterator it;
	it=ce.begin();
	while(it!=ce.end())
	{
		outputChess(*it);
		it++;
	}
	return;
}

void Map::outputTwoDVector(std::vector<std::vector<Chess>> ce)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	it=ce.begin();
	while(it!=ce.end())
	{
		outputOneDVector(*it);
		it++;
	}
}


int Map::linkFive(std::vector<Chess> ce,int n)
{
	if(n==5) return linkFive(ce[0],ce[1],ce[2],ce[3],ce[4]);
	return 0;
}

int Map::liveFour(std::vector<Chess> ce,int n)
{
	if(n==6) return liveFour(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	return 0;
}

int Map::rushFour(std::vector<Chess> ce,int n)
{
	int count=0;
	if(n==5) count+= rushFour(ce[0],ce[1],ce[2],ce[3],ce[4]);
	if(n==6) count+= rushFour(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	return count;
}

int Map::liveThree(std::vector<Chess> ce,int n)
{
	int count=0;
	if(n==5) count+= liveThree(ce[0],ce[1],ce[2],ce[3],ce[4]);
	if(n==6) count+= liveThree(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	return count;
}

int Map::sleepThree(std::vector<Chess> ce,int n)
{
	int count=0;
	if(n==5) count+= sleepThree(ce[0],ce[1],ce[2],ce[3],ce[4]);
	if(n==6) count+= sleepThree(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	if(n==7) count+= sleepThree(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5],ce[6]);
	return count;
}

int Map::liveTwo(std::vector<Chess> ce,int n)
{
	int count=0;
	if(n==4) count+= liveTwo(ce[0],ce[1],ce[2],ce[3]);
	if(n==5) count+= liveTwo(ce[0],ce[1],ce[2],ce[3],ce[4]);
	if(n==6) count+= liveTwo(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	return count;
}

int Map::sleepTwo(std::vector<Chess> ce,int n)
{
	int count=0;
	if(n==5) count+= sleepTwo(ce[0],ce[1],ce[2],ce[3],ce[4]);
	if(n==6) count+= sleepTwo(ce[0],ce[1],ce[2],ce[3],ce[4],ce[5]);
	return count;
}

std::vector<std::vector<Chess>> Map::getChessChain(Chess ce,int n,int loc)
{
	using std::vector;
	vector<Chess> vErrorCeTmp;
	vErrorCeTmp.push_back(getErrorChess());
	vector<vector<Chess>> vErrorCe;
	vErrorCe.push_back(vErrorCeTmp);
	vector<vector<Chess>> vce;
	vector<Chess> vceLay,vceStand,vceMain,vceVice;
	switch(n)
	{
	case 4:
		vceLay=fourChain(ce,LAY,loc);
		vceStand=fourChain(ce,STAND,loc);
		vceMain=fourChain(ce,MAIN,loc);
		vceVice=fourChain(ce,VICE,loc);
		break;
	case 5:
		vceLay=fiveChain(ce,LAY,loc);
		vceStand=fiveChain(ce,STAND,loc);
		vceMain=fiveChain(ce,MAIN,loc);
		vceVice=fiveChain(ce,VICE,loc);
		break;
	case 6:
		vceLay=sixChain(ce,LAY,loc);
		vceStand=sixChain(ce,STAND,loc);
		vceMain=sixChain(ce,MAIN,loc);
		vceVice=sixChain(ce,VICE,loc);
		break;
	case 7:
		vceLay=sevenChain(ce,LAY,loc);
		vceStand=sevenChain(ce,STAND,loc);
		vceMain=sevenChain(ce,MAIN,loc);
		vceVice=sevenChain(ce,VICE,loc);
		break;
	default:
		return vErrorCe;
	}
	vce.push_back(vceLay);
	vce.push_back(vceStand);
	vce.push_back(vceMain);
	vce.push_back(vceVice);
	return vce;
}

int Map::countLinkFive(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=1;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=linkFive(vce,5);
	}
	return count;
}

int Map::countLiveFour(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=2;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=liveFour(vce,6);
	}
	return count;
}

int Map::countRushFour(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=2;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=rushFour(vce,6);
	}
	for(int i=1;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=rushFour(vce,5);
	}
	return count;
}

int Map::countLiveThree(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=2;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=liveThree(vce,6);//<====
	}
	for(int i=2;i<=4;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=liveThree(vce,5);
	}
	return count;
}

int Map::countSleepThree(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=3;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,7,i);
		if(!chainIsOK(vce)) continue;
		count+=sleepThree(vce,7);
	}
	for(int i=2;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=sleepThree(vce,6);
	}
	for(int i=1;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=sleepThree(vce,5);
	}
	return count;
}

int Map::countLiveTwo(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=3;i<=4;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=liveTwo(vce,6);
	}
	for (int i=2;i<=4;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=liveTwo(vce,5);
	}
	for(int i=1;i<=4;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,4,i);
		if(!chainIsOK(vce)) continue;
		count+=liveTwo(vce,4);
	}
	return count;
}

int Map::countSleepTwo(Chess ce)
{
	using std::vector;
	int count=0;
	for (int i=2;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,6,i);
		if(!chainIsOK(vce)) continue;
		count+=sleepTwo(vce,6);
	}
	for (int i=1;i<=5;i++)
	{
		vector<vector<Chess>> vce=getChessChain(ce,5,i);
		if(!chainIsOK(vce)) continue;
		count+=sleepTwo(vce,5);
	}
	return count;
}

int Map::linkFive(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=linkFive(*it,n);
		it++;
	}
	return count;
}

int Map::liveFour(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=liveFour(*it,n);
		it++;
	}
	return count;
}

int Map::rushFour(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=rushFour(*it,n);
		it++;
	}
	return count;
}

int Map::liveThree(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=liveThree(*it,n);//<=====
		it++;
	}
	return count;
}

int Map::sleepThree(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=sleepThree(*it,n);
		it++;
	}
	return count;
}

int Map::liveTwo(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=liveTwo(*it,n);
		it++;
	}
	return count;
}

int Map::sleepTwo(std::vector<std::vector<Chess>> ce,int n)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	int count=0;
	it=ce.begin();
	while(it!=ce.end())
	{
		if(!chainOneDIsOk((*it)))
		{
			it++;
			continue;
		}
		count+=sleepTwo(*it,n);
		it++;
	}
	return count;
}

std::vector<Chess> Map::fourChain(Chess ce, int dir, int loc)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return inDirOne(ce,4,dir);
	case 2:
		return inDirTwo(ce,4,dir);
	case 3:
		return inDirThree(ce,4,dir);
	case 4:
		return inDirFour(ce,4,dir);
	default:
		return vErrorCe;
	}
	return vErrorCe;
}

std::vector<Chess> Map::fiveChain(Chess ce, int dir, int loc)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return inDirOne(ce,5,dir);
	case 2:
		return inDirTwo(ce,5,dir);
	case 3:
		return inDirThree(ce,5,dir);
	case 4:
		return inDirFour(ce,5,dir);
	case 5:
		return inDirFive(ce,5,dir);
	default:
		return vErrorCe;
	}
	return vErrorCe;
}

std::vector<Chess> Map::sixChain(Chess ce, int dir, int loc)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return inDirOne(ce,6,dir);
	case 2:
		return inDirTwo(ce,6,dir);
	case 3:
		return inDirThree(ce,6,dir);
	case 4:
		return inDirFour(ce,6,dir);
	case 5:
		return inDirFive(ce,6,dir);
	case 6:
		return inDirSix(ce,6,dir);
	default:
		return vErrorCe;
	}
	return vErrorCe;
}

std::vector<Chess> Map::sevenChain(Chess ce, int dir, int loc)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	switch (loc)
	{
	case 1:
		return inDirOne(ce,7,dir);
	case 2:
		return inDirTwo(ce,7,dir);
	case 3:
		return inDirThree(ce,7,dir);
	case 4:
		return inDirFour(ce,7,dir);
	case 5:
		return inDirFive(ce,7,dir);
	case 6:
		return inDirSix(ce,7,dir);
	case 7:
		return inDirSeven(ce,7,dir);
	default:
		return vErrorCe;
	}
	return vErrorCe;
}

std::vector<Chess> Map::inDirOne(Chess ce,int n,int dir)
{//错误数组，如果结果不合理，返回错误数组
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	//棋子位于棋链的位置1处，棋链长n,方向为dir
	std::vector<Chess> vce;//用来存储该棋链
	if(n<1) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==1) return vce;
	for(int i=2;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}

	/*defineToString(dir);
	outputOneDVector(vce);*/

	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirTwo(Chess ce,int n,int dir)//<=====临时改变！！
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<2) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce1=getPrev(ce,dir);
	vce.push_back(ce1);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);//别放了再把原来的oce给push回去
	if(n==2) return vce;
	for (int i=3;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirThree(Chess ce,int n,int dir)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<3) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce2=getPrev(ce,dir);
	Chess ce1=getPrev(ce2,dir);
	vce.push_back(ce1);
	vce.push_back(ce2);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==3) return vce;
	for (int i=4;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirFour(Chess ce,int n,int dir)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<4) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce1;
	Chess ce2;
	Chess ce3;
	ce3=getPrev(ce,dir);
	ce2=getPrev(ce3,dir);
	ce1=getPrev(ce2,dir);
	vce.push_back(ce1);
	vce.push_back(ce2);
	vce.push_back(ce3);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==4) return vce;
	for (int i=5;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirFive(Chess ce,int n,int dir)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<5) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce1;
	Chess ce2;
	Chess ce3;
	Chess ce4;
	ce4=getPrev(ce,dir);
	ce3=getPrev(ce4,dir);
	ce2=getPrev(ce3,dir);
	ce1=getPrev(ce2,dir);
	vce.push_back(ce1);
	vce.push_back(ce2);
	vce.push_back(ce3);
	vce.push_back(ce4);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==5) return vce;
	for (int i=6;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirSix(Chess ce,int n,int dir)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<6) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce1;
	Chess ce2;
	Chess ce3;
	Chess ce4;
	Chess ce5;
	ce5=getPrev(ce,dir);
	ce4=getPrev(ce5,dir);
	ce3=getPrev(ce4,dir);
	ce2=getPrev(ce3,dir);
	ce1=getPrev(ce2,dir);
	vce.push_back(ce1);
	vce.push_back(ce2);
	vce.push_back(ce3);
	vce.push_back(ce4);
	vce.push_back(ce5);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==6) return vce;
	for (int i=7;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

std::vector<Chess> Map::inDirSeven(Chess ce,int n,int dir)
{
	std::vector<Chess> vErrorCe;
	vErrorCe.push_back(getErrorChess());
	std::vector<Chess> vce;//用来存储该棋链
	if(n<7) return vce;//如果棋子的位置比棋链长还大，则不合常理
	Chess ce1;
	Chess ce2;
	Chess ce3;
	Chess ce4;
	Chess ce5;
	Chess ce6;
	ce6=getPrev(ce,dir);
	ce5=getPrev(ce6,dir);
	ce4=getPrev(ce5,dir);
	ce3=getPrev(ce4,dir);
	ce2=getPrev(ce3,dir);
	ce1=getPrev(ce2,dir);
	vce.push_back(ce1);
	vce.push_back(ce2);
	vce.push_back(ce3);
	vce.push_back(ce4);
	vce.push_back(ce5);
	vce.push_back(ce6);
	Chess oce=map[ce.row][ce.col];
	oce.color=friendColor;//<===必须要将空白位改为friendColor，否则会影响判断！！！
	vce.push_back(oce);
	if(n==7) return vce;
	for (int i=8;i<=n;i++)
	{
		Chess tmpCe;
		tmpCe=getNext(vce[i-2],dir);
		vce.push_back(tmpCe);
	}
	for (int i=0;i<n;i++)
	{
		if(vce[i].isBoundry) return vErrorCe;
	}
	return vce;
}

Chess Map::upNext(Chess ce)
{
	if(ce.row<=0) return getErrorChess();
	Chess tmp=Chess(map[ce.row-1][ce.col].color,
		map[ce.row-1][ce.col].atkValue,
		map[ce.row-1][ce.col].defValue,
		map[ce.row-1][ce.col].row,
		map[ce.row-1][ce.col].col,
		map[ce.row-1][ce.col].isBoundry);
	return tmp;
}

Chess Map::downNext(Chess ce)
{
	if(ce.row>=size+1) return getErrorChess();
	Chess tmp=Chess(map[ce.row+1][ce.col].color,
		map[ce.row+1][ce.col].atkValue,
		map[ce.row+1][ce.col].defValue,
		map[ce.row+1][ce.col].row,
		map[ce.row+1][ce.col].col,
		map[ce.row+1][ce.col].isBoundry);
	return tmp;
}

Chess Map::leftNext(Chess ce)
{
	if(ce.col<=0) return getErrorChess();
	Chess tmp=Chess(map[ce.row][ce.col-1].color,
		map[ce.row][ce.col-1].atkValue,
		map[ce.row][ce.col-1].defValue,
		map[ce.row][ce.col-1].row,
		map[ce.row][ce.col-1].col,
		map[ce.row][ce.col-1].isBoundry);
	return tmp;
}

Chess Map::rightNext(Chess ce)
{
	if(ce.col>=size+1) return getErrorChess();
	Chess tmp=Chess(map[ce.row][ce.col+1].color,
		map[ce.row][ce.col+1].atkValue,
		map[ce.row][ce.col+1].defValue,
		map[ce.row][ce.col+1].row,
		map[ce.row][ce.col+1].col,
		map[ce.row][ce.col+1].isBoundry);
	return tmp;
}

Chess Map::leftUpNext(Chess ce)
{
	if(ce.row<=0 || ce.col<=0) return getErrorChess();
	Chess tmp=Chess(map[ce.row-1][ce.col-1].color,
		map[ce.row-1][ce.col-1].atkValue,
		map[ce.row-1][ce.col-1].defValue,
		map[ce.row-1][ce.col-1].row,
		map[ce.row-1][ce.col-1].col,
		map[ce.row-1][ce.col-1].isBoundry);
	return tmp;
}

Chess Map::rightUpNext(Chess ce)
{
	if(ce.row<=0 || ce.col>=size+1) return getErrorChess();
	Chess tmp=Chess(map[ce.row-1][ce.col+1].color,
		map[ce.row-1][ce.col+1].atkValue,
		map[ce.row-1][ce.col+1].defValue,
		map[ce.row-1][ce.col+1].row,
		map[ce.row-1][ce.col+1].col,
		map[ce.row-1][ce.col+1].isBoundry);
	return tmp;
}

Chess Map::leftDownNext(Chess ce)
{
	if(ce.row>=size+1 || ce.col<=0) return getErrorChess();
	Chess tmp=Chess(map[ce.row+1][ce.col-1].color,
		map[ce.row+1][ce.col-1].atkValue,
		map[ce.row+1][ce.col-1].defValue,
		map[ce.row+1][ce.col-1].row,
		map[ce.row+1][ce.col-1].col,
		map[ce.row+1][ce.col-1].isBoundry);
	return tmp;
}

Chess Map::rightDownNext(Chess ce)
{
	if(ce.row>=size+1 || ce.col>=size+1) return getErrorChess();
	Chess tmp=Chess(map[ce.row+1][ce.col+1].color,
		map[ce.row+1][ce.col+1].atkValue,
		map[ce.row+1][ce.col+1].defValue,
		map[ce.row+1][ce.col+1].row,
		map[ce.row+1][ce.col+1].col,
		map[ce.row+1][ce.col+1].isBoundry);
	return tmp;
}

int Map::getLayNum(Chess ce)
{
	int count=0;
	count+=left(ce);
	count+=right(ce);
	return count+1;
}

int Map::getStandNum(Chess ce)
{
	int count=0;
	count+=up(ce);
	count+=down(ce);
	return count+1;
}

int Map::getMainNum(Chess ce)
{
	int count=0;
	count+=leftUp(ce);
	count+=rightDown(ce);
	return count+1;
}

int Map::getViceNum(Chess ce)
{
	int count=0;
	count+=rightUp(ce);
	count+=leftDown(ce);
	return count+1;
}

int Map::up(Chess ce)
{
	int count=0;
	ce.row--;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row--;
	}
	return count;
}

int Map::down(Chess ce)
{
	int count=0;
	ce.row++;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row++;
	}
	return count;
}

int Map::left(Chess ce)
{
	int count=0;
	ce.col--;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.col--;
	}
	return count;
}

int Map::right(Chess ce)
{
	int count=0;
	ce.col++;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.col++;
	}
	return count;
}

int Map::leftUp(Chess ce)
{
	int count=0;
	ce.row--;
	ce.col--;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row--; 
		ce.col--;
	}
	return count;
}

int Map::rightUp(Chess ce)
{
	int count=0;
	ce.row--;
	ce.col++;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row--; 
		ce.col++;
	}
	return count;
}

int Map::leftDown(Chess ce)
{
	int count=0;
	ce.row++; ce.col--;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row++; 
		ce.col--;
	}
	return count;
}

int Map::rightDown(Chess ce)
{
	int count=0;
	ce.row++; ce.col++;
	while(map[ce.row][ce.col].color==friendColor)
	{
		count++; 
		ce.row++; 
		ce.col++;
	}
	return count;
}

std::string Map::defineToString(int code)
{
	switch(code)
	{
	case BLACK:
		return "BLACK";
	case WHITE:
		return "WHITE";
	case NONE:
		return "NONE";
	case LAY:
		return "LAY";
	case STAND:
		return "STAND";
	case MAIN:
		return "MAIN";
	case VICE:
		return "VICE";
	default:
		return "ERROR";
	}
	return "ERROR";
}

std::string Map::boolToString(bool flag)
{
	switch(flag)
	{
	case true:
		return "true";
	case false:
		return "false";
	}
	return "false";
}

Chess Map::getErrorChess()
{
	Chess ce=Chess(ERROR,ERROR,ERROR,ERROR,ERROR,true);
	return ce;
}

bool Map::chainOneDIsOk(std::vector<Chess> ce)
{
	using std::vector;
	vector<Chess>::iterator it;
	it=ce.begin();
	while(it!=ce.end())
	{
		if((*it).isBoundry) return false;//如果是边界或者错误棋子，那么就不ok
		it++;
	}
	return true;
}

bool Map::chainIsOK(std::vector<std::vector<Chess>> vce)
{
	using std::vector;
	vector<vector<Chess>>::iterator it;
	it=vce.begin();
	while(it!=vce.end())
	{
		vector<Chess>::iterator it2;
		it2=(*it).begin();
		while(it2!=(*it).end())
		{
			if(!(*it2).isBoundry) return true;
			it2++;
		}
		it++;
	}
	return false;
}

//bool Map::chainIsOk(std::vector<std::vector<Chess>> ce)
//{
//	using std::vector;
//	vector<Chess>::iterator iter1;//一维数组迭代器
//	vector<vector<Chess>>::iterator iter2;//二维数组迭代器
//	for(iter2=ce.begin();iter2!=ce.end();iter2++)
//	{
//		for(iter1=(*iter2).begin();iter1!=(*iter2).end();iter1++)
//		{
//			if((*iter1).isBoundry) return false;
//		}
//	}
//	return true;
//}//不要判断二维数组，不能通过局部否定整体

