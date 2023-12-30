#pragma once
#include "hero.h"


class ynyn :public Hero
{
private:
    double magic = 75;
public:
    ynyn();
    void Play();
    CREATE_FUNC(ynyn);
    void upLevel(Hero* yn1);
    Hero* initynyn();
    void ynynNormalAttack(Hero* enemy, const int attackNum,const double add, const int hurt);
    void swordwaive(Hero* my);
    void goaway(Point Pos, Hero* my);
};
