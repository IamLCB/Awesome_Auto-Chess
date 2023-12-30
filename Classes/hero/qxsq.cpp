#include "qxsq.h"


qxsq::qxsq()
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
    speed = 0.65;//攻速
}

void qxsq::upLevelqxsq(Hero* qxsq1, Hero* qxsq2, Hero* qxsq3)
{
    qxsq1->blood = 1080;//当前血量
    qxsq1->maxBlood = 1080;//生命值
    qxsq1->level = 2; //等级
    qxsq1->attack = 117; //攻击力
    qxsq2->removeFromParent();
    qxsq3->removeFromParent();
}

void qxsq::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdb = [=](float dt) {
        this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
    };
    this->schedule(lambdb, 1 / 60.f, "qxsqMove");
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, true, this->ofPlayer);//锁敌
        attackNum = 0;//攻击次数
        static int hurt = (int)(attack * enemy->attackRate);//伤害值
        static int add = (level == 1 ? 125 : 250);
       // while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
        {
            attackNum++;//对该敌人的攻击次数+1
            auto lambda = [=](float dt) {
                qxsq::qxsqAttack(enemy, attackNum,hurt ,add);
            };
            this->schedule(lambda, 1 / speed,"qxsqAttack");
            auto lambdc = [=](float dt) {
                enemy->setColor(Color3B::GRAY);
            };
            this->schedule(lambdc,  speed, "tmp22");
        }
    }
    //this->removeFromParent();
}


Hero* qxsq::initqxsq()
{
    Hero* qxsq = static_cast<Hero*>(qxsq::create());
   // my = qxsq;
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 1;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, speed, -1);
    //tfns->autorelease();
    return qxsq;
}




void qxsq::qxsqAttack(Hero* enemy, const int attackNum,const int hurt,const int add)
{
    blue += 50;
    enemy->setColor(Color3B::BLUE);
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
    //shootbullet("zidan.png", enemy->getPosition() - this->getPosition(), this);//??????????//图片
}


void qxsq::shootbullet(string picturename, Point Pos, Hero* my)
{
    Sprite* bullet = Sprite::create(picturename);
    this->addChild(bullet);
    bullet->setPosition(400,230);//??????????//更改距离？

    auto move = MoveBy::create(1.f, Pos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//更改距离？
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    bullet->runAction(Repeat::create(all, 1));
}