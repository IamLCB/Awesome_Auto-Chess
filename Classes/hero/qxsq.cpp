#include "qxsq.h"


qxsq::qxsq()
{
    name = "驱邪圣枪", skillname = "冷酷追击", advice = "中排";
    skillType = PHYSICS;
    blood = 600;//当前血量
    maxBlood = 600;//生命值
    level = 1; //等级
    attack = 65; //攻击力
    protect = 25;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 100;//攻击距离
    price = 2;//花费
    speed = 0.65;//攻速
}

void qxsq::upLevel(Hero* qxsq1)
{
    qxsq1->blood = 1080;//当前血量
    qxsq1->maxBlood = 1080;//生命值
    qxsq1->level = 2; //等级
    qxsq1->attack = 117; //攻击力
    setScale(0.35f);
}

void qxsq::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdb = [=](float dt) {
        enemy = getEnemyByDistance(this, true, this->ofPlayer);//锁敌
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambdb, 1 / 60.f, "qxsqMove");
    {
        attackNum = 0;//攻击次数
        if(enemy!=nullptr)
        {
            static int hurt = (int)(attack * enemy->attackRate);//伤害值
            static int add = (level == 1 ? 125 : 250);
            {
                attackNum++;//对该敌人的攻击次数+1
                auto lambda = [=](float dt) {
                    if (state == ATTACK) {
                        enemy->setColor(Color3B::GRAY);
                        qxsq::qxsqAttack(enemy, attackNum, hurt, add);
                        attackNum++;
                    }
                };
                this->schedule(lambda, 1 / speed, "qxsqAttack");
            }
        }
        }
}


Hero* qxsq::initqxsq()
{
    Hero* qxsq = static_cast<Hero*>(qxsq::create());
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 1;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, speed, -1);
    return qxsq;
}




void qxsq::qxsqAttack(Hero* enemy, const int attackNum,const int hurt,const int add)
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
}


//void qxsq::shootbullet(string picturename, Point Pos, Hero* my)
//{
//    Sprite* bullet = Sprite::create(picturename);
//    this->addChild(bullet);
//    bullet->setPosition(400,230);//??????????//更改距离？
//
//    auto move = MoveBy::create(1.f, Pos);
//    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//更改距离？
//    auto appear = FadeIn::create(0.f);
//    auto disappear = FadeOut::create(0.f);
//
//    auto actionTo = Sequence::createWithTwoActions(appear, move);
//    auto actionBack = Sequence::createWithTwoActions(disappear, back);
//    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
//    bullet->runAction(Repeat::create(all, 1));
//}