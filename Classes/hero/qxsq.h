#pragma once
#include "hero.h"


class qxsq :public Hero
{
private:
    double magic = 35;
public:
    qxsq();
    void Play();
    void upLevelqxsq(Hero* qxsq1, Hero* qxsq2, Hero* qxsq3);
    CREATE_FUNC(qxsq);
    Hero* initqxsq();
    void qxsqAttack(Hero* enemy, const int attackNum, const int hurt,const int add);
    void shootbullet(string picturename, Point Pos, Hero* my);
   
};

