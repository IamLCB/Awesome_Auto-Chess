#include "ltzz.h"

template <typename T>
ltzz<T>::ltzz()
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

template <typename T>
void ltzz<T>::Play()
{
    T* enemy, tmpEnemy;
    int attackNum = 0;
    while (!isDead() && !isEnd())
    {
        enemy = getEnemy();//锁敌
        while (enemy->!isDead() && isInRange(enemy) && !isDead() && my->state == ATTACK)//符合连续进攻条件
        {
            int hurt = (int)((level == 1 ? 1.9 : 2) * attack * enemy->attackRate);//伤害值
            //首先对先锁定的敌人进行攻击和魔法伤害
            effect.Lightning(enemy);//特效
            enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//物理攻击
            enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法伤害
            if (enemy->blood < 0) {
                enemy->blood = 0;
                break;//敌方已死亡
            }
            for (int i = 0; i < 4; i++) {//最多附加攻击4名敌人
                int start = clock();
                while (clock() - start <= 5);//在二十秒内每五秒进行一次重新锁敌进行附加闪电攻击
                getEnemy(enemy);//没有距离限制
                effect.Lightning(enemy);//特效
                enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法伤害
                if (enemy->blood < 0) {
                    enemy->blood = 0;
                    break;//敌方已死亡
                }
            }
        }
    }
}