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
	void upLevel(Hero* bqzs1);
	CREATE_FUNC(bqzs);
	void bqzsnormalAttack(Hero* enemy, int hurt, double add);
	void swordwaive(Hero* my);
	void swordswing(Hero* my);
};