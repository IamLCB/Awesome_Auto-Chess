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
    void upLevelwlshz(Hero* wlshz1, Hero* wlshz2, Hero* wlshz3);
};