#pragma once
#include "hero.h"
//��ս̹��

class bqzs :public Hero
{
	double magic = 100;
public:
	bqzs();
	void Play();
	Hero* initbqzs();
	void bqzs::upLevelbqzs(Hero* bqzs1, Hero* bqzs2, Hero* bqzs3);
	CREATE_FUNC(bqzs);
	void bqzsnormalAttack(Hero* enemy,int hurt,double add);
	/*void swordwaive(string picturename,Hero* my);
	void swordswing(string picturename, Hero* my);*/
};