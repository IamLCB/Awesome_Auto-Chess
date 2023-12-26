#pragma once
#include "Hero.h"

template <typename T>
class mlps :public Hero<T>
{
    int magicAmount = 0;
public:
    mlps();
    void Play();
};