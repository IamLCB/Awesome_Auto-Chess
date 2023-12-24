#ifndef _HERO_H_
#define _HERO_H_
#include"cocos2d.h"
#include<string>
USING_NS_CC;

using std::string;

#define FREEZETIME 2
#define COLDDOWNTIME 1
#define ATTACK 1
#define FREEZE 0
#define PHYSICS 0
#define MAGIC 1

class Skill;



//template <typename T>
class Hero :public Sprite
{
public:
	//friend Effect<T>;
	//friend Battle<T>;
	string name, skillname;
	int skillType = -1;
	int blood = 500;
	int maxBlood = 500;//Ѫ��
	int level = 1; //�ȼ�(Ŀǰֻ���������ȼ�)
	int attack = 50; //������
	int protect = 0;//����
	int magicPro = 10;//ħ��
	int state;//����״̬
	int x = 0, y = 0;//�������ϵ�����
	double speed = 0.6;//����
	double attackRate = 1;

	int blue = 0;//��ǰ����
	const int blueMax = 150;//�������ֵ
	double movespeed = 1;
	//////////////////////
	double attackDistance = 100;  //��������

	double xtemp = x;      //����ս��ʱ��λ��(��ͼλ��)
	double ytemp = y;
	//���ӻ�
	double height = 0; //����ͼƬ�ĳ��ȺͿ��
	double width = 0;
	//������
	int ofPlayer = 0;     //�������
	int price = 1;    //������
	int soldMoney = price; //����������


public:
	string picturename;   //ͼƬ����
	int picturenum;       //ͼƬ����
	//virtual void Play();//���ڸ�������Ľ���
	Hero() = default;
	bool isDead();//�ж��Ƿ�����
	//virtual Hero* initHero();
	struct myPoint
	{
		int x;
		int y;
	};

	//װ��������
	/*---------------set����----------------------*/

	/*void setPlayer(int player) { ofplayer = player; }
	void setSpeed(double a) { speed = a; }
	void setBlood(int a) { blood = a; }
	void set(Point point)
	{
		x = point.x;
		y = point.y;
	};
	void setTempPosition() { xtemp = x; ytemp = y; }*/

	//////////////���ӻ����֣�����
	/*------------------��������----------------*/
	/*Sprite* bloodFrame = Sprite::create("BloodFrame.jpg");
	ProgressTimer* Blood = ProgressTimer::create(Sprite::create("Blood.jpg"));
	ProgressTimer* magic = ProgressTimer::create(Sprite::create("magic.png"));
	Sprite* magicFrame = Sprite::create("BloodFrame.jpg");
	Label* Star = Label::createWithTTF("", "fonts/arial.ttf", 24);

	void update(float dt);         //����update����
	void bloodUpdate(float dt);*/

	/*����װ���޸�����*/
	void changeAttackDistance(int value) { attackDistance += value; }
	void changePro(int value) { protect += value; }
	void changeSpeed(double value) { speed += value; }
	void changeAttack(int value) { attack += value; }
	//void equimentchange();
	void heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop);
	
};

template <typename T>
class Effect
{
	friend Hero;
public:
	//void Dizzy(T* enemy);
	//void Bomb(T* enemy);
	//void proProtect(T* my);
	//void sevInjure(T* enemy);
	//void relProtect(T* enemy);
	//void immune(T* enemy);
};

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
	int getPlayer() { return my.ofPlayer; }           //�����������
	float getSpeed() { return my.speed; }
	int getAttackDistance() { return attackDistance; };        //��ù�������
	const cocos2d::Size getContentSize() { return Size(width, height); }   //���ͼƬ����
};*/

#endif