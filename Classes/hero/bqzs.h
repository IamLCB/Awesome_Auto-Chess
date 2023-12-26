#pragma once
#include "hero.h"
//½üÕ½Ì¹¿Ë

class bqzs :public Hero
{
public:
	bqzs();
	void Play();
	Hero* initbqzs();
	CREATE_FUNC(bqzs);
	void bqzsnormalAttack(Hero* enemy,double add, int hurt);
	void swordwaive(string picturename,Hero* my);
	void swordswing(string picturename, Hero* my);
};