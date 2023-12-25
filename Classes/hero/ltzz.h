#pragma once
#include "Hero.h"

template <typename T>
class ltzz :public Hero<T>
{
    int magicAmount = 0;
public:
    ltzz();
    void Play();
};