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
	ProgressTimer* healthBar;
	int type = 0;
	string advice;//前排中排后排建议
	int skillType = -1;
	int blood = 500;
	int maxBlood = 500;//血量
	int level = 1; //等级(目前只设置两个等级)
	int attack = 50; //攻击力
	int protect = 0;//护甲
	int magicPro = 10;//魔抗
	int state;//技能状态

	double speed = 0.6;//攻速
	double attackRate = 1;

	int blue = 0;//当前蓝条
	const int blueMax = 150;//最大蓝条值
	double movespeed = 1;
	//////////////////////
	double attackDistance = 100;  //攻击距离
	//玩家相关
	int ofPlayer = 0;     //所属玩家
	int price = 1;    //所需金币
	int soldMoney = price; //卖掉所获金币


public:
	string picturename;   //图片名字
	int picturenum;       //图片张数
	virtual void Play() {}//用于各个子类的进行
	Hero() = default;
	bool isDead();//判断是否死亡
	void update(Hero* my, Hero* enemy, float dt);
	Hero* getEnemyByDistance(Hero* myHero, bool mode, bool isMyHero);
	bool isInAttackRange(Hero* myHero, Hero* enemyHero);
	bool isWin(playerData* myPlayer, playerData* opPlayer);
	int getBlood() { return blood; }
	int getMaxBlood() { return maxBlood; }
	void recover();

	/*******************************12.30添加(可能有已经添加过的，如type)*************************/

	float x = 0.f;
	float y = 0.f;


	float xTemp = x;
	float yTemp = y;
	//用于记录英雄进行移动操作前的坐标，初始设置为与原始坐标一致

	void set(float x1, float y1) { x = x1, y = y1; }
	void set(Point point) { x = point.x; y = point.y; }
	// 对应两种重载形式
	void setTempPosition() { xTemp = x; yTemp = y; }
	Point getTempPosition() { return Point(xTemp, yTemp); }   //获得进入战斗时的位置

	int getPrice() { return price; }
	void setPlayer(int player) {
		ofPlayer = player;
	}

	int getType() { return type; }//返回的是每种英雄的类型，playerData中的enum，默认每种英雄已经有了各自的type

	/*******************************12.30添加*************************/
	virtual void upLevel(Hero* hero) {};

	/*用于装备修改属性*/
	void changeAttackDistance(int value) { attackDistance += value; }
	void changePro(int value) { protect += value; }
	void changeSpeed(double value) { speed += value; }
	void changeAttack(int value) { attack += value; }
	//void equimentchange();
	void heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop);
	Node* Hero::createHealthBar(double percentage);

};

Hero* createHero(int name);
void bomb(Hero* enemy, int attack);
void lightning(Hero* enemy, const int hurt);
void Dizzy(Hero* enemy);
void proProtect(Hero* my);
void sevInjure(Hero* enemy);
void relProtect(Hero* enemy);
void immune(Hero* enemy);





#endif
