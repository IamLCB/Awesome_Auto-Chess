#include "qxsq.h"

template <typename T>
qxsq<T>::qxsq()
{
    name = "驱邪圣枪", skillname = "冷酷追击";
    skillType = PHYSICS;
    blood = 600;//当前血量
    maxBlood = 600;//生命值
    level = 1; //等级
    attack = 65; //攻击力
    protect = 25;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 3;//攻击距离
    price = 2;//花费
    x = 0, y = 0;//在棋盘上的坐标
    speed = 0.65;//攻速
}

template <typename T>
void qxsq<T>::Play()
{
    T* enemy;
    int attackNum = 0;
    while (!isDead() && !isEnd())
    {
        enemy = getEnemy();//锁敌，可攻击范围内最远
        attackNum = 0;//攻击次数
        int hurt = (int)(attack * enemy->attackRate);//伤害值
        int add = (level == 1 ? 125 : 250);
        while (enemy->!isDead() && isInRange(enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
        {
            attackNum++;//对该敌人的攻击次数+1
            auto lambda = [=](float dt) {
                qxsq<T>::qxsqAttack(enemy, attackNum,hurt ,add);
            };
            this->schedule(lambda, 1 / speed);
        }
    }
}

template <typename T>
qxsq<T>* qxsq<T>::initqxsq()
{
    auto qxsq = qxsq::create();
    my = qxsq;
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 2;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, qxsq->getPosition(), speed, -1);//??????????//未识别？
    //tfns->autorelease();
    return qxsq;
}



template <typename T>
void qxsq<T>::qxsqAttack(T* enemy, const int attackNum,const int hurt,const int add)
{
    blue += 50;
    if (blue == blueMax)//如果连续对同一目标攻击三次
    {
        enemy->blood -= (hurt + add);//造成真实伤害
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//护甲抵消部分伤害
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方死亡
    shootbullet("zidan.png", enemy->getPosition() - this->getPosition(), this);
}

template <typename T>
void qxsq<T>::shootbullet(string picturename, Point Pos, qxsq<T>* my)
{
    Sprite* bullet = Sprite::create(picturename);
    this->addChild(bullet);
    bullet->setPosition(40, 30);//??????????//更改距离？

    auto move = MoveBy::create(1.f, Pos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//更改距离？
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    bullet->runAction(Repeat::create(all, 1));
}