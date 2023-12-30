#ifndef _SMALLHERO_H_
#define _SMALLHERO_H_
#include"hero/hero.h"
class smallHero :public Hero {
public:
	smallHero() {};
	CREATE_FUNC(smallHero);
	smallHero* initSmall();
	void moveByMouse_R(Hero* myHero);
};
#endif
