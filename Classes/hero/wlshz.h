#pragma once
#include "hero.h"

class wlshz :public Hero
{
    int magicAmount = 0;
public:
    wlshz();
    void Play();
    Hero* initwlshz();
    void wlshzAttack(Hero* enemy);
    CREATE_FUNC(wlshz);
    void upLevel(Hero* wlshz1);
};