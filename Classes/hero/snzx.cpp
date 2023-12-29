#include "snzx.h"
//全能坦克
snzx::snzx()
{
    name = "狻猊之心", skillname = "呐啊！";
    skillType = PHYSICS;
    blood = 800;//当前血量
    maxBlood = 800;//生命值
    level = 1; //等级
    attack = 50; //攻击力
    protect = 30;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 2;//攻击距离
    price = 4;//花费
    speed = 0.7;//攻速
}

void snzx::upLevelsnzx(Hero* snzx1, Hero* snzx2, Hero* snzx3)
{
    snzx1->blood = 1440;//当前血量
    snzx1->maxBlood = 1440;//生命值
    snzx1->level = 2; //等级
    snzx1->attack = 90; //攻击力
    snzx2->removeFromParent();
    snzx3->removeFromParent();
}

void snzx::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
        };
        this->schedule(lambda, 1 / 60.f, "snzxMove");
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
        attackNum = 0;//攻击次数
        static int hurt = (int)(attack * enemy->attackRate);//伤害值
        static int add = (level == 1 ? 50 : 100);
       // while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
        {
            attackNum++;//对该敌人的攻击次数+1
            auto lambda = [=](float dt) {
                snzx::snzxAttack(enemy, attackNum,hurt,add);
            };
            this->schedule(lambda, 1 / speed, "snzxAttack");

        }
    }
    //this->removeFromParent();
}


Hero* snzx::initsnzx()
{
    Hero* snzx = static_cast<Hero*>(snzx::create());
    snzx->picturename = "./hero/snzx.png";
    snzx->picturenum = 1;
    snzx->heroAnimation(snzx->picturename, snzx->picturenum, snzx, speed, -1);
    return snzx;
}


void snzx::snzxAttack(Hero* enemy, const int attackNum,const int hurt, const int add)
{
    blue += 30;
    int extra = (level == 1) ? 200 : 300;
    if (blue == blueMax)//如果连续对同一目标攻击5
    {
        this->blood += ((level == 1) ? 250 : 450);
        //createHealthBar(const string& backgroundTexture, const std::string& foregroundTexture, double initialPercentage, const Vec2& position);
        Hero* enemynow = getEnemyByDistance(this,  true,this->ofPlayer);//锁敌最远
        moveToFar(enemynow);
        Dizzy(enemynow);
        enemynow->blood -= (hurt + extra + add - enemynow->protect);
        blue = 0;
    }
    else
    {
        enemy->setColor(Color3B::YELLOW);
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//护甲抵消部分伤害
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方死亡
}

//暂时没有实现，可以参考已经实现了的隐娘
void snzx::moveToFar( Hero* enemy)
{
    // 获取敌人的位置信息
    cocos2d::Vec2 enemyPosition = enemy->getPosition();

    // 获取自身的位置信息
    cocos2d::Vec2 selfPosition = getPosition();

    // 计算敌人和自身之间的距离
    float distance = enemyPosition.distance(selfPosition);

    // 确保距离大于零
    if (distance > 0)
    {
        // 计算目标位置在敌人身后的位置
        cocos2d::Vec2 targetPosition = enemyPosition - (enemyPosition - selfPosition);

        // 使用Cocos系统函数将角色移动到目标位置
        runAction(cocos2d::MoveTo::create(0.f, targetPosition));
    }
}