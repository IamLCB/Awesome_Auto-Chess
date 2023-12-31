#include "yn.h"


ynyn::ynyn()
{
    name = "隐娘", skillname = "影遁忍术", advice = "中排";
    skillType = PHYSICS;
    blood = 550;//当前血量
    maxBlood = 550;//生命值
    level = 1; //等级
    attack = 70; //攻击力
    protect = 20;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 1;//攻击距离
    price = 3;//花费
    speed = 0.6;//攻速
}

void ynyn::upLevel(Hero* yn1)
{
    yn1->blood = 990;//当前血量
    yn1->maxBlood = 990;//生命值
    yn1->level = 2; //等级
    yn1->attack = 126; //攻击力
}

Hero* ynyn::initynyn()
{
    Hero* yn = static_cast<Hero*>(ynyn::create());
    //my = yn;
    yn->picturename = "./hero/yn.png";
    yn->picturenum = 1;
    yn->heroAnimation(yn->picturename, yn->picturenum, yn,  speed, -1);
   
    return yn;
}



void ynyn::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
    auto lambdd = [=](float dt) {
        
        this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambdd, 1 / 60.f, "ynynMove");


    static double add = (level == 1) ? 300 : 400;
    static double exp = (level == 1) ? 3 : 4;
    static int hurt = (int)(enemy->attackRate * attack);

    attackNum++;//对该敌人的攻击次数+1
    auto lambda = [=](float dt) {
        if (enemy != nullptr && state == ATTACK)
            ynyn::ynynNormalAttack(enemy, attackNum, add, hurt);
    };
    this->schedule(lambda, 1 / speed, "ynAttack");
    // 释放技能
    if (blue == blueMax) {
        auto lambdc = [=](float dt) {
            if (enemy->blood > (int)(0.5 * enemy->maxBlood)) {
                enemy->blood -= (int)(hurt - (enemy->protect) + add);//高血量加成伤害
            }
            else {
                enemy->blood -= (int)(hurt - (enemy->protect) + add * exp);//低血量加倍伤害
            }
        };
        this->schedule(lambdc, 1 / speed, "ynNormalAttack");//释放技能
        blue = 0;
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方死亡
}

void ynyn::ynynNormalAttack(Hero* enemy, const int attackNum,const double add,const int hurt)
{
    blue += 30;
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//护甲抵消部分伤害
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方已死
    swordwaive(this);
    goaway(enemy->getPosition(), this);
}

void ynyn::swordwaive(Hero* my)
{
    Sprite* sword = Sprite::create("./hero/sword.png");
    my->addChild(sword, 3);
    sword->setScale(2.0f);
    sword->setPosition(Vec2(600, 300));
    // 挥舞刀的动作序列
    auto waive = Sequence::create(
        RotateTo::create(1.0f, 90),   // 刀向左旋转
        RotateTo::create(1.0f, 0),      // 刀恢复原始角度
        CallFunc::create([sword]() {
            sword->removeFromParent();
            }),
        nullptr
                );
    // 执行动作序列
    sword->runAction(waive);
}

void ynyn::goaway(Point Pos, Hero* my) {
    // 跑到远处的动作序列
    double distance = 50; // 更改距离的值
    auto run = Sequence::create(
        MoveTo::create(1.0f, Vec2(Pos.x + distance, Pos.y)), // 修改移动目标的位置
        nullptr
    );
    // 执行动作序列
    my->runAction(run);
}
