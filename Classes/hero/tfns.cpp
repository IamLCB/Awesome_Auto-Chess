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
    attackDistance = 500;//攻击距离
    price = 1;//花费
    speed = 0.7;//攻速
}

void tfns::upLeveltfns(Hero* tfns1, Hero* tfns2, Hero* tfns3)
{
    tfns1->blood = 990;//当前血量
    tfns1->maxBlood = 990;//生命值
    tfns1->level = 2; //等级
    tfns1->attack = 72; //攻击力
    tfns2->removeFromParent();
    tfns3->removeFromParent();
}

void tfns::Play()
{
    static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);
    static int attackNum = 0;
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
            this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
            isDead();
        };
        this->schedule(lambda, 1 / 60.f, "tfnsMove");
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//符合连续攻击条件则持续攻击 
        //{
        attackNum++;//对该敌人的攻击次数+1
        auto lambdb = [=](float dt) {
            tfns::tfnsAttack(enemy, attackNum);
        };
        this->schedule(lambdb, 1 / speed, "tfnsAttack");
        auto lambdc = [=](float dt) {
            enemy->setColor(Color3B::GREEN);
        };
        this->schedule(lambdc, speed, "tmp");
    //}

}

Hero* tfns::inittfns()
{
    Hero* tfns = tfns::create();
    tfns->picturename = "./hero/tfns.png";
    tfns->picturenum = 1;
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    return tfns;
}


void tfns::tfnsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)((level == 1 ? 1.08 : 1.12) * attack * enemy->attackRate);//伤害值
    enemy->setColor(Color3B::BLUE);
    blue += 30;
    if (blue == blueMax)//如果连续攻击五次
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
}
