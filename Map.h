#pragma once
#include <string>
#include<vector>

#define LAY 801
#define STAND 802
#define MAIN 803
#define VICE 804

#define BLACK 811
#define WHITE 812
#define NONE 813

#define ERROR -123

struct Chess 
{
	int color;
	int atkValue;
	int defValue;
	int row;
	int col;
	bool isBoundry;
	Chess(){this->isBoundry=false;};//一般情况下都不是边界，只有在初始赋值的情况下有边界

	//************************************
	// Method:    Chess
	// FullName:  Chess::Chess
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: int color 当前空位的颜色
	// Parameter: int atkValue 作为攻击方的权值
	// Parameter: int defValue 作为防守方的权值
	// Parameter: int x 横坐标
	// Parameter: int y 纵坐标
	// Parameter: bool isBoundry 判断是不是边界
	//************************************
	Chess(int color,int atkValue,int defValue,int x,int y,bool isBoundry)
	{
		this->color=color;
		this->atkValue=atkValue;
		this->defValue=defValue;
		this->row=x;
		this->col=y;
		this->isBoundry=isBoundry;
	}
	Chess(int color,int atkValue,int defValue)
	{
		this->color=color;
		this->atkValue=atkValue;
		this->defValue=defValue;
		this->isBoundry=false;
	}
	Chess(int color)
	{
		this->color=color;
		this->isBoundry=false;
	}
	Chess(int x,int y)
	{
		this->row=x;
		this->col=y;
		this->isBoundry=false;
	}
	Chess(std::string error)
	{
		this->color=ERROR;
		this->atkValue=ERROR;
		this->defValue=ERROR;
		this->row=ERROR;
		this->col=ERROR;
		this->isBoundry=true;
	}
};

class Map
{
private:
	int size;
	Chess **map;
	int friendColor;
	int enemyColor;
	int num;//记录全盘棋子数
public:
	Map(void);
	~Map(void);
	void iniMap(int size);
	int getSize();
	int getFriendColor();
	int getNum();
	void numPlus();
	void setAtkValue(Chess ce,int atkValue);
	void setDefValue(Chess ce,int defValue);
	int getAtkValue(Chess ce);
	int getDefValue(Chess ce);
	//************************************
	// Method:    giveMapValue
	// FullName:  Map::giveMapValue
	// Access:    public 
	// Returns:   void
	// Qualifier: 测试使用，给棋盘下友方棋子棋子
	//************************************
	void giveMapFriend();
	void giveMapEnemy();

	void putAIChess(Chess ce);
	void putPlayChess(Chess ce);
	
	//************************************
	// Method:    outputMap
	// FullName:  Map::outputMap
	// Access:    public 
	// Returns:   void
	// Qualifier: 输出整个棋盘的数值，测试用
	//************************************
	void outputMap();

	//************************************
	// Method:    iniColor
	// FullName:  Map::iniColor
	// Access:    public 
	// Returns:   void
	// Qualifier: 初始化机器人的棋子颜色，因为程序的第一人称是机器人
	//只给己方赋值，敌方会自动赋值
	// Parameter: int color
	//************************************
	void iniColor(int color);

	//************************************
	// Method:    reverseFriendEnemy
	// FullName:  Map::reverseFriendEnemy
	// Access:    public 
	// Returns:   void
	// Qualifier: 转换friendColor 和 enemyColor
	//主要是为了给defValue赋值
	//************************************
	void reverseFriendEnemy();

	//************************************
	// Method:    getNum
	// FullName:  Map::getNum
	// Access:    public 
	// Returns:   int
	// Qualifier: 获得特定方向的友方棋子数
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	int getNum(Chess ce,int dir);

	//************************************
	// Method:    outputChess
	// FullName:  Map::outputChess
	// Access:    public 
	// Returns:   void
	// Qualifier: 输出棋子的相关信息
	// Parameter: Chess ce
	//************************************
	void outputChess(Chess ce);

	//************************************
	// Method:    getNext
	// FullName:  Map::getNext
	// Access:    public 
	// Returns:   Chess
	// Qualifier: 获取当前位置棋子发下一个棋子
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	Chess getNext(Chess ce, int dir);

	//************************************
	// Method:    getPrev
	// FullName:  Map::getPrev
	// Access:    public 
	// Returns:   Chess
	// Qualifier: 获取当前位置棋子的前一个棋子
	// Parameter: Chess ce
	// Parameter: int dir
	//************************************
	Chess getPrev(Chess ce, int dir);

	//************************************
	// Method:    getChess
	// FullName:  Map::getChess
	// Access:    public 
	// Returns:   Chess
	// Qualifier: 通过坐标获取棋盘该位置的信息
	//写完才发现这个是个废物函数...
	// Parameter: int x
	// Parameter: int y
	//************************************
	Chess getChess(int x,int y);

	void outputOneDVector(std::vector<Chess> ce);
	void outputTwoDVector(std::vector<std::vector<Chess>> ce);

	//************************************
	// Method:    countLinkFive
	// FullName:  Map::countLinkFive
	// Access:    public 
	// Returns:   int
	// Qualifier: 以countLinkFive()为例，统计棋子ce，任意方向
	//棋型可能位置，棋型可能长度上连5的个数，使用时必须保证空位假设棋子颜色
	//和己方颜色一致，否则要重设friendColor！！！
	// Parameter: Chess ce
	//************************************
	int countLinkFive(Chess ce);
	int countLiveFour(Chess ce);
	int countRushFour(Chess ce);
	int countLiveThree(Chess ce);
	int countSleepThree(Chess ce);
	int countLiveTwo(Chess ce);
	int countSleepTwo(Chess ce);
private:
	//************************************
	// Method:    getChessChain
	// FullName:  Map::getChessChain
	// Access:    private 
	// Returns:   std::vector<std::vector<Chess>>
	// Qualifier: 获取四个方向的长度为n,位置为loc的棋子链
	// Parameter: Chess ce
	// Parameter: int n
	// Parameter: int loc
	//************************************
	std::vector<std::vector<Chess>> getChessChain(Chess ce,int n,int loc);
	//--getChessChain()和下面的函数要联合使用
	//--getChessChain()获得四向的单棋子链
	//然后四向单棋子链要分别通过下面的棋型判断函数
	int linkFive(std::vector<std::vector<Chess>> ce,int n);
	int liveFour(std::vector<std::vector<Chess>> ce,int n);
	int rushFour(std::vector<std::vector<Chess>> ce,int n);
	int liveThree(std::vector<std::vector<Chess>> ce,int n);
	int sleepThree(std::vector<std::vector<Chess>> ce,int n);
	int liveTwo(std::vector<std::vector<Chess>> ce,int n);
	int sleepTwo(std::vector<std::vector<Chess>> ce,int n);
	//	|由单个棋子，获取一维
	//	|由一维，获取二维	
	//	|从而逐步减轻机器判断的负担
	int linkFive(std::vector<Chess> ce,int n);
	int liveFour(std::vector<Chess> ce,int n);
	int rushFour(std::vector<Chess> ce,int n);
	int liveThree(std::vector<Chess> ce,int n);
	int sleepThree(std::vector<Chess> ce,int n);
	int liveTwo(std::vector<Chess> ce,int n);
	int sleepTwo(std::vector<Chess> ce,int n);

	int linkFive(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int rushFour(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepThree(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6,Chess ce7);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int liveTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);
	int sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5);
	int sleepTwo(Chess ce1,Chess ce2,Chess ce3,Chess ce4,Chess ce5,Chess ce6);

	//************************************
	// Method:    fourChain
	// FullName:  Map::fourChain
	// Access:    private 
	// Returns:   std::vector<Chess>
	// Qualifier: 以fourChain为例，说明一下该函数的作用
	//返回链长为4，当前空白位为ce,方向为dir，空白位位置为loc的棋子链
	//如果棋子链部分超出边界，或者给的loc超过棋子链长度n，会返回一个错误数组
	//错误数组只有一个元素，除isBoundry是true以外，其他参数全是ERROR，从而便于判断
	// Parameter: Chess ce 当前棋子的信息（正在被判断的空白棋子）
	// Parameter: int dir 棋子链方向（四个方向）
	// Parameter: int loc 当前棋子在棋子链中的位置
	//************************************
	std::vector<Chess> fourChain(Chess ce, int dir, int loc);
	std::vector<Chess> fiveChain(Chess ce, int dir, int loc);
	std::vector<Chess> sixChain(Chess ce, int dir, int loc);
	std::vector<Chess> sevenChain(Chess ce, int dir, int loc);

	//下面七个函数的定义是，位于位置one或two~seven的棋子ce,获得其方向为dir，长度为n的棋子链
	std::vector<Chess> inDirOne(Chess ce,int n,int dir);
	std::vector<Chess> inDirTwo(Chess ce,int n,int dir);
	std::vector<Chess> inDirThree(Chess ce,int n,int dir);
	std::vector<Chess> inDirFour(Chess ce,int n,int dir);
	std::vector<Chess> inDirFive(Chess ce,int n,int dir);
	std::vector<Chess> inDirSix(Chess ce,int n,int dir);
	std::vector<Chess> inDirSeven(Chess ce,int n,int dir);


	Chess upNext(Chess ce);
	Chess downNext(Chess ce);
	Chess leftNext(Chess ce);
	Chess rightNext(Chess ce);
	Chess leftUpNext(Chess ce);
	Chess rightUpNext(Chess ce);
	Chess leftDownNext(Chess ce);
	Chess rightDownNext(Chess ce);

	int getLayNum(Chess ce);
	int getStandNum(Chess ce);
	int getMainNum(Chess ce);
	int getViceNum(Chess ce);

	int up(Chess ce);
	int down(Chess ce);
	int left(Chess ce);
	int right(Chess ce);
	int leftUp(Chess ce);
	int rightUp(Chess ce);
	int leftDown(Chess ce);
	int rightDown(Chess ce);

	std::string defineToString(int code);
	std::string boolToString(bool flag);
	//************************************
	// Method:    getErrorChess
	// FullName:  Map::getErrorChess
	// Access:    private 
	// Returns:   Chess
	// Qualifier: 获取一个参数全是ERROR(除isBoundry是true),的棋子
	//用作一些函数的错误返回值
	//************************************
	Chess getErrorChess();

	
	//************************************
	// Method:    chainIsOk
	// FullName:  Map::chainIsOk
	// Access:    private 
	// Returns:   bool
	// Qualifier: 一维数组必须全部不是边界
	// Parameter: std::vector<Chess> ce
	//************************************
	bool chainOneDIsOk(std::vector<Chess> ce);

	//************************************
	// Method:    chainIsOK
	// FullName:  Map::chainIsOK
	// Access:    private 
	// Returns:   bool
	// Qualifier: 二维数组只要有一组ok就行了
	// Parameter: std::vector<std::vector<Chess>> vce
	//************************************
	bool chainIsOK(std::vector<std::vector<Chess>> vce);
};

