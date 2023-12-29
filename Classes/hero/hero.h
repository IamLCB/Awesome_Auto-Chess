#ifndef _HERO_H_
#define _HERO_H_
#include"cocos2d.h"
#include"player/playerData.h"
#include "globalResSetting.h"
#include<string>
USING_NS_CC;

using std::string;

#define FREEZETIME 2
#define COLDDOWNTIME 1
#define ATTACK 1
#define FREEZE 0
#define PHYSICS 0
#define MAGIC 1
#define TANK 2

class Hero :public Sprite
{
public:
	//friend Battle<T>;
	string name, skillname;
	int skillType = -1;
	int blood = 500;
	int maxBlood = 500;//血量
	int level = 1; //等级(目前只设置两个等级)
	int attack = 50; //攻击力
	int protect = 0;//护甲
	int magicPro = 10;//魔抗
	int state;//技能状态
	int x = 0, y = 0;//在棋盘上的坐标
	double speed = 0.6;//攻速
	double attackRate = 1;

	int blue = 0;//当前蓝条
	const int blueMax = 150;//最大蓝条值
	double movespeed = 1;
	//////////////////////
	double attackDistance = 100;  //攻击距离

	double xtemp = x;      //进入战斗时的位置(地图位置)
	double ytemp = y;
	//可视化
	double height = 0; //所带图片的长度和宽度
	double width = 0;
	//玩家相关
	int ofPlayer = 0;     //所属玩家
	int price = 1;    //所需金币
	int soldMoney = price; //卖掉所获金币


public:
	string picturename;   //图片名字
	int picturenum;       //图片张数
	//virtual void Play();//用于各个子类的进行
	Hero() = default;
	bool isDead();//判断是否死亡
	void update(Hero* my, Hero* enemy, float dt);
	virtual void Play() {}
	struct myPoint
	{
		int x;
		int y;
	};
	Hero* getEnemyByDistance(Hero* myHero, bool mode, bool isMyHero);
	bool isInAttackRange(Hero* myHero, Hero* enemyHero);
	bool isWin(playerData* myPlayer, playerData* opPlayer);

	//装备？？？
	/*---------------set类型----------------------*/

	/*void setPlayer(int player) { ofplayer = player; }
	void setSpeed(double a) { speed = a; }
	void setBlood(int a) { blood = a; }
	void set(Point point)
	{
		x = point.x;
		y = point.y;
	};
	void setTempPosition() { xtemp = x; ytemp = y; }*/

	//////////////可视化部分，不会
	/*------------------所需子类----------------*/
	/*Sprite* bloodFrame = Sprite::create("BloodFrame.jpg");
	ProgressTimer* Blood = ProgressTimer::create(Sprite::create("Blood.jpg"));
	ProgressTimer* magic = ProgressTimer::create(Sprite::create("magic.png"));
	Sprite* magicFrame = Sprite::create("BloodFrame.jpg");
	Label* Star = Label::createWithTTF("", "fonts/arial.ttf", 24);

	void update(float dt);         //子类update函数
	void bloodUpdate(float dt);*/

	/*用于装备修改属性*/
	void changeAttackDistance(int value) { attackDistance += value; }
	void changePro(int value) { protect += value; }
	void changeSpeed(double value) { speed += value; }
	void changeAttack(int value) { attack += value; }
	//void equimentchange();
	void heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop);
	Node* createHealthBar(const string& backgroundTexture, const string& foregroundTexture, double initialPercentage, const Vec2& position);

};

Hero* createHero(int name);
void Dizzy(Hero* enemy);
void bomb(Hero* enemy, int attack);
void lightning(Hero* enemy, const int hurt);
void proProtect(Hero* my);
void sevInjure(Hero* enemy);
void relProtect(Hero* enemy);
void immune(Hero* enemy);
/*template <typename T>
class Battle
{
	T* my;
public:
	Battle(string n);
	string getMyName() { return my.name; };
	string getSkillName() { return my.skillname; };
	int getType() { return my.skillType; };
	int getBlood() { return my.blood; };
	int getMaxBlood() { return my.maxBlood; };
	int getLevel() { return my.level; };
	int getAttack() { return my.attack; };
	double getSpeed() { return my.speed };
	int getMagicPro() { return my.magicpro };
	int getProtect() { return my.protect };
	myPoint getCoordinate();
	int getPrice() { return my.price; }
	int getSoldMoney() { return my.soldMoney; }
	int getPlayer() { return my.ofPlayer; }           //返回所属玩家
	float getSpeed() { return my.speed; }
	int getAttackDistance() { return attackDistance; };        //获得攻击距离
	const cocos2d::Size getContentSize() { return Size(width, height); }   //获得图片长宽
};*/




#endif
