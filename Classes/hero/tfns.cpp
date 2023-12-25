#include "tfns.h"


tfns::tfns()
{
    name = "天罚弩神", skillname = "圣银弩箭";
    skillType = PHYSICS;
    blood = 550;//当前血量
    maxBlood = 550;//生命值
    level = 1; //等级
    attack = 40; //攻击力
    protect = 25;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 3;//攻击距离
    price = 1;//花费
    x = 0, y = 0;//在棋盘上的坐标
    speed = 0.7;//攻速

}


void tfns::Play()
{
    Hero* enemy;
    int attackNum = 0;
    while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, opPlayerData);//锁敌
        attackNum = 0;//攻击次数
        while (!enemy->isDead() && isInAttackRange(this,enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
        {
            attackNum++;//对该敌人的攻击次数+1
            auto lambda = [=](float dt) {
                tfns::tfnsAttack(enemy, attackNum);
            };
            this->schedule(lambda, 1 / speed, "tfnsAttack");

        }
    }
}


Hero* tfns::initHero()
{
    Hero* tfns = static_cast<Hero*>(tfns::create());
    // my = tfns;
    tfns->picturename = "./hero/tfns%d.png";
    tfns->picturenum = 3;
    //tfns->setPosition(800, 460);
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    //tfns->autorelease();
    return tfns;
}


void tfns::tfnsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)((level == 1 ? 1.08 : 1.12) * attack * enemy->attackRate);//伤害值
    blue += 30;
    if (blue == blueMax)//如果连续对同一目标攻击三次
    {
        enemy->blood -= hurt;//造成真实伤害
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//护甲抵消部分伤害
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方死亡
    //shootArrow("pea.png", enemy->getPosition() - this->getPosition(), this);
}


void tfns::shootArrow(string picturename, Point deltaPos)
{
    Sprite* arrow = Sprite::create(picturename);
    this->addChild(arrow);
    arrow->setPosition(40, 30);//??????????//更改距离？
    auto move = MoveBy::create(1.f, deltaPos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//更改距离？
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    arrow->runAction(Repeat::create(all, 1));
}