#pragma once
#include "hero.h"

class ltzz :public Hero
{
    int magicAmount = 0;
public:
    ltzz();
    void Play();
    Hero* initltzz();
    void ltzzAttack(Hero* enemy);
    CREATE_FUNC(ltzz);
    void upLevel(Hero* ltzz1);
};