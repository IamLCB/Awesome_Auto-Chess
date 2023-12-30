#include "wlshz.h"

wlshz::wlshz()
{
    name = "未来守护者", skillname = "闪电领域";
    skillType = TANK;
    blood = 700;//当前血量
    maxBlood = 700;//生命值
    level = 1; //等级
    attack = 60; //攻击力
    protect = 35;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    magicAmount = 50;//法力值
    attackDistance = 100;//攻击距离
    price = 2;//花费
    speed = 0.65;//攻速
}

void wlshz::upLevelwlshz(Hero* wlshz1, Hero* wlshz2, Hero* wlshz3)
{
    wlshz1->blood = 1260;//当前血量
    wlshz1->maxBlood = 1260;//生命值
    wlshz1->level = 2; //等级
    wlshz1->attack = 108; //攻击力
    wlshz2->removeFromParent();
    wlshz3->removeFromParent();
}

void wlshz::Play()
{
    static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);
    static int attackNum = 0;
    auto lambda = [=](float dt) {
        this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambda, 1 / 60.f, "wlshzMove");
    //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
    //{
    auto lambdb = [=](float dt) {
        wlshz::wlshzAttack(enemy);
    };
    this->schedule(lambdb, 1 / speed, "wlshzAttack");
    auto lambdc = [=](float dt) {
        enemy->setColor(Color3B::RED);
    };
    this->schedule(lambdc, speed, "tmp");
    //}
}

Hero* wlshz::initwlshz()
{
    Hero* tfns = wlshz::create();
    tfns->picturename = "./hero/wlshz.png";
    tfns->picturenum = 1;
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    return tfns;
}


void wlshz::wlshzAttack(Hero* enemy)
{
    int hurt = (int)((level == 1 ? 2.00 : 3.50) * attack * enemy->attackRate);//伤害值
    enemy->setColor(Color3B::ORANGE);
    blue += 30;
    Dizzy(enemy);
    if (blue == blueMax)//如果连续攻击五次
    {
        enemy->blood -= hurt;//造成真实伤害
        blue = 0;
    }
    else
    {
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法攻击
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方死亡
}