#include "mlps.h"

mlps::mlps()
{
    name = "麦林炮手", skillname = "爆炸火花", advice = "后排";
    skillType = MAGIC;
    blood = 500;//当前血量
    maxBlood = 500;//生命值
    protect = 20;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    magicAmount = 50;//法力值
    attackDistance = 4;//攻击距离
    price = 1;//花费
    speed = 0.65;//攻速
}

Hero* mlps::initmlps()
{
    Hero* mlps = static_cast<Hero*>(mlps::create());
    mlps->picturename = "./hero/mlps.png";
    mlps->picturenum = 1;
    mlps->heroAnimation(mlps->picturename, mlps->picturenum, mlps, speed, -1);
    return mlps;
}

void mlps::upLevel(Hero* mlps1)
{
    mlps1->blood = 900;//当前血量
    mlps1->maxBlood = 900;//生命值
    mlps1->level = 2; //等级
    mlps1->attack = 90; //攻击力

}

void mlps::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambda = [=](float dt) {
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
        if (enemy != nullptr)
            this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
        isDead();
    };
    this->schedule(lambda, 1 / 60.f, "mlpsMove");
    attackNum = 0;//进攻次数
    auto lambdb = [=](float dt) {
        if (enemy != nullptr) {
            bomb(enemy, attack);//爆炸特效
            if (state == ATTACK) 
            {
                attackNum++;//进攻次数+1
                mlps::mlpsAttack(enemy, attackNum);
            }
        }
    };
    this->schedule(lambdb, 1 / speed, "mlpsAttack");    
}

void mlps::mlpsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)(attack * enemy->attackRate);//伤害值
    blue += 30;
    if (blue == blueMax)//如果连续攻击五次
    {
        enemy->blood -= level == 1 ? 95 : 135;//造成真实伤害
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//物理伤害
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法攻击
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//敌方已死
    attack += attack / 2;//每次攻击会增加50%的伤害
    
    //延迟四秒
    auto lambda = [=](float dt) {
        enemy->blood -= level == 1 ? 95 : 135;//造成真实伤害
    };
    enemy->scheduleOnce(lambda, 4, "mlpsTimeAttack");
}