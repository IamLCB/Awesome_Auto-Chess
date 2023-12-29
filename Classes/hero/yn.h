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
    void upLevelynyn(Hero* yn1, Hero* yn2, Hero* yn3);
    Hero* initynyn();
    void ynynNormalAttack(Hero* enemy, const int attackNum,const double add, const int hurt);
    void swordwaive(string picturename, Hero* my);
    void goaway(Point Pos, Hero* my);
};
