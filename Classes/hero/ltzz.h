#pragma once
#include "Hero.h"

class ltzz :public Hero
{
    int magicAmount = 0;
public:
    ltzz();
    void Play();
    Hero* initltzz();
    void ltzzAttack(Hero* enemy);
    CREATE_FUNC(ltzz);
    void upLevelltzz(Hero* ltzz1, Hero* ltzz2, Hero* ltzz3);
};