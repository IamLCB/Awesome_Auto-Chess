#pragma once
#include "hero.h"


class snzx :public Hero
{
private:
    double magic = 100;
public:
    snzx();
    void Play();
    CREATE_FUNC(snzx);
    void upLevelsnzx(Hero* snzx1, Hero* snzx2, Hero* snzx3);
    Hero* initsnzx();
    void snzxAttack(Hero* enemy, const int attackNum, const int hurt, const int add);
    void moveToFar(Hero* my);
};