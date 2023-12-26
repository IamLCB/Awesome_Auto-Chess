#pragma once
#include "hero.h"


class yn :public Hero
{
private:
    double magic = 75;
public:
    yn();
    void Play();
    CREATE_FUNC(yn);
    void upLevelyn(Hero* yn1, Hero* yn2, Hero* yn3);
    Hero* inityn();
    void ynNormalAttack(Hero* enemy, const int attackNum,const double add, const int hurt);
    void swordwaive(string picturename, Hero* my);
    void goaway(Point Pos, Hero* my);
};
