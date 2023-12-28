#include "ltzz.h"

ltzz::ltzz()
{
    name = "雷霆之主", skillname = "雷霆怒爪";
    skillType = MAGIC;
    blood = 750;//当前血量
    maxBlood = 750;//生命值
    attack = 70; //攻击力
    protect = 30;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    attackDistance = 1;//攻击距离
    magicAmount = 75;//法力值
    price = 3;//花费
    x = 0, y = 0;//在棋盘上的坐标
    speed = 0.65;//攻速
}

Hero* ltzz::initltzz()
{
    Hero* ltzz = static_cast<Hero*>(ltzz::create());
    ltzz->picturename = "./hero/ltzz.png";
    ltzz->picturenum = 1;
    ltzz->heroAnimation(ltzz->picturename, ltzz->picturenum, ltzz, speed, -1);
    return ltzz;
}

void upLevelltzz(Hero* ltzz1, Hero* ltzz2, Hero* ltzz3)
{
    ltzz1->blood = 1350;//当前血量
    ltzz1->maxBlood = 1350;//生命值
    ltzz1->level = 2; //等级
    ltzz1->attack = 126; //攻击力
    ltzz2->removeFromParent();
    ltzz3->removeFromParent();
}

void ltzz::Play()
{
    Hero* enemy, tmpEnemy;
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    //{
    enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
        };
        this->schedule(lambda, 1 / 60.f, "ltzzMove");
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//符合连续进攻条件
        //{
            auto lambdc = [=](float dt) {
                ltzz::ltzzAttack(enemy);
            };
            this->schedule(lambdc, 1 / speed, "ltzzAttack");
            //??????????//是否可以同时进行？
            auto lambdb = [=](float dt) {
                for (int i = 0; i < 4; i++)//最多附加攻击4名敌人
                {
                    Hero* tmpenemy = getEnemyByDistance(this, true, this->ofPlayer);//没有距离限制
                    ltzz::ltzzAttack(tmpenemy);
                }
            };
            this->schedule(lambdb, 20, "ltzzlightAttack");
        //}
    //}
}

void ltzz::ltzzAttack(Hero* enemy)
{
    int hurt = (int)((level == 1 ? 1.9 : 2) * attack * enemy->attackRate);//伤害值
    //首先对先锁定的敌人进行攻击和魔法伤害
    lightning(enemy, hurt);//闪电特效
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//物理攻击
    enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法伤害
    if (enemy->blood < 0) 
        enemy->blood = 0;
}