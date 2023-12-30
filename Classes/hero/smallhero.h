#pragma once
#include"hero.h"
class smallHero :public Hero {
public:
	smallHero() {};
	CREATE_FUNC(smallHero);
	smallHero* initSmall();
	void moveByMouse_R(Hero* myHero);
};
