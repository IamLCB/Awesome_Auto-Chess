#pragma once
#include "hero.h"
//½üÕ½Ì¹¿Ë

class bqzs :public Hero
{
	double magic = 100;
public:
	bqzs();
	void Play();
	Hero* initbqzs();
	void bqzs::upLevelbqzs(Hero* bqzs1, Hero* bqzs2, Hero* bqzs3);
	CREATE_FUNC(bqzs);
	void bqzsnormalAttack(Hero* enemy,double add, int hurt);
	void swordwaive(string picturename,Hero* my);
	void swordswing(string picturename, Hero* my);
};