#pragma once
#include "hero.h"

class tfns :public Hero
{
public:
    tfns();
    void Play();
    Hero* inittfns();
    void tfnsAttack(Hero* enemy, const int attackNum);
    CREATE_FUNC(tfns);
    void upLevel(Hero* tfns1);
};