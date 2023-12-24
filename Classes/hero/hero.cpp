#include "hero.h"

//template <typename T>
bool Hero::isDead()
{
	if (blood == 0)
		return true;
	return false;
}
//template <typename T>
void Hero::heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop)
{
    Animation* animation = Animation::create();
    const char* picname = picturename.c_str();

    for (int i = 0; i < picturenum; i++) {
        char key[32];
        sprintf(key, picname, i);
        animation->addSpriteFrameWithFile(key);
    }
    animation->setDelayPerUnit(speed); //设定速度
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,循环
    auto action = Animate::create(animation);
    //action->setTag(-2);
    //sp->runAction(animate);
    sprite->runAction(action);
}


/*template <typename T>
void Effect<T>::Dizzy(T* enemy)
{
    //英雄变成灰色
    enemy->setColor(Color3B::GRAY);
    // 禁用英雄的动作
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄的动作
        enemy->runAction(RepeatForever::create(Animate::create(heroAnimation)));
    };
    enemy->scheduleOnce(lambda, 4);
}
template <typename T>
void Effect<T>::sevInjure(T* enemy)
{
    //英雄变成红色
    enemy->setColor(Color3B::RED);
    // 禁用英雄
    enemy->movespeed = enemy->movespeed * 0.5;
    enemy->speed = enemy->speed * 0.5;
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄
        enemy->movespeed = enemy->movespeed * 2;
        enemy->speed = enemy->speed * 2;
    };
    enemy->scheduleOnce(lambda, 2);
}



template <typename T>
void Effect<T>::proProtect(T*my)
{
    my->protect = (int)(my->protect * 1.2);
}

template <typename T>
void Effect<T>::relProtect(T* enemy)
{
    enemy->setColor(Color3B::GREEN);
    enemy->protect = (int)(enemy->protect * 0.8);
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        enemy->protect = (int)(enemy->protect * 1.25);
    };
    enemy->scheduleOnce(lambda, 2);
}

template <typename T>
void Effect<T>::immune(T* enemy)
{
    double Rate = enemy->attackRate;
    enemy->attackRate = 0;
    auto lambda = [=](float dt) {
        enemy->attackRate = Rate;
    };
    enemy->scheduleOnce(lambda, 2);
}*/
