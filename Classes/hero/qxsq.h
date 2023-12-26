#pragma once
#include "Hero.h"

template <typename T>
class qxsq :public Hero<T>
{
private:
    magic = 35;
public:
    qxsq();
    void Play();
    CREATE_FUNC(qxsq);
    qxsq<T>* initqxsq();
    void qxsqAttack(T* enemy, const int attackNum, const int hurt,const int add);
    void shootbullet(string picturename, Point Pos, qxsq<T>* my);
   
};

