#pragma once
#include "hero.h"


class qxsq :public Hero
{
private:
    double magic = 35;
public:
    qxsq();
    void Play();
    void upLevel(Hero* qxsq1);
    CREATE_FUNC(qxsq);
    Hero* initqxsq();
    void qxsqAttack(Hero* enemy, const int attackNum, const int hurt,const int add);
    //void shootbullet( Point Pos, Hero* my);
};

