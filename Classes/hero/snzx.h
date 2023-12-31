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
    void upLevel(Hero* snzx1);
    Hero* initsnzx();
    void snzxAttack(Hero* enemy, const int attackNum, const int hurt, const int add);
    //void goaway(Point Pos, Hero* my);
};