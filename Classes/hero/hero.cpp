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
    animation->setDelayPerUnit(speed); //�趨�ٶ�
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,ѭ��
    auto action = Animate::create(animation);
    //action->setTag(-2);
    //sp->runAction(animate);
    sprite->runAction(action);
}


/*template <typename T>
void Effect<T>::Dizzy(T* enemy)
{
    //Ӣ�۱�ɻ�ɫ
    enemy->setColor(Color3B::GRAY);
    // ����Ӣ�۵Ķ���
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        // ��������Ӣ�۵Ķ���
        enemy->runAction(RepeatForever::create(Animate::create(heroAnimation)));
    };
    enemy->scheduleOnce(lambda, 4);
}
template <typename T>
void Effect<T>::sevInjure(T* enemy)
{
    //Ӣ�۱�ɺ�ɫ
    enemy->setColor(Color3B::RED);
    // ����Ӣ��
    enemy->movespeed = enemy->movespeed * 0.5;
    enemy->speed = enemy->speed * 0.5;
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        // ��������Ӣ��
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
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
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
