#pragma once
#include "hero.h"

class mlps :public Hero
{
    int magicAmount = 0;
public:
    mlps();
    void Play();
    Hero* initmlps();
    void mlpsAttack(Hero* enemy, const int attackNum);
    CREATE_FUNC(mlps);
    void upLevel(Hero* mlps1);
};