#include "mlps.h"

template <typename T>
mlps<T>::mlps()
{
    name = "麦林炮手", skillname = "爆炸火花";
    skillType = MAGIC;
    blood = 500;//当前血量
    maxBlood = 500;//生命值
    protect = 20;//护甲
    magicPro = 20;//魔抗
    state = ATTACK;//技能状态
    magicAmount = 50;//法力值
    attackDistance = 4;//攻击距离
    price = 1;//花费
    x = 0, y = 0;//在棋盘上的坐标
    speed = 0.65;//攻速
}

template <typename T>
void mlps<T>::Play()
{
    T* enemy;
    int attackNum = 0;
    while (my->!isDead() && !isEnd())
    {
        DWORD start = clock();//从对于某一敌人开始进攻时计时
        enemy = getEnemy();//锁敌
        attackNum = 0;//进攻次数
        while (enemy->!isDead() && isInRange(enemy) && my->!isDead() && my->state == ATTACK) //符合连续进攻条件
        {
            attackNum++;//进攻次数+1
            int hurt = (int)(my->attack * enemy->attackRate);//伤害值
            effect.bomb(enemy);//爆炸特效
            if (attackNum % 3 == 0 || clock() - start >= 4)//如果连续对同一目标攻击三次或延迟4秒
            {
                //T* initEnemy = enemy;    实现在一格范围内对所有敌人的攻击，需要在棋盘确定之后得到数据
                //while(getDistance(enemy=getEnemy())<一格的对角线长度)
                enemy->blood -= level == 1 ? 95 : 135;//造成真实伤害
            }
            else
            {
                enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//物理伤害
                enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//魔法攻击
                if (enemy->blood < 0)
                    enemy->blood = 0;//敌方已死
            }
            my->attack += attack / 2;//每次攻击会增加50%的伤害
        }
    }
}