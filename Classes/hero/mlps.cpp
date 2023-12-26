#include "mlps.h"

template <typename T>
mlps<T>::mlps()
{
    name = "��������", skillname = "��ը��";
    skillType = MAGIC;
    blood = 500;//��ǰѪ��
    maxBlood = 500;//����ֵ
    protect = 20;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    magicAmount = 50;//����ֵ
    attackDistance = 4;//��������
    price = 1;//����
    x = 0, y = 0;//�������ϵ�����
    speed = 0.65;//����
}

template <typename T>
void mlps<T>::Play()
{
    T* enemy;
    int attackNum = 0;
    while (my->!isDead() && !isEnd())
    {
        DWORD start = clock();//�Ӷ���ĳһ���˿�ʼ����ʱ��ʱ
        enemy = getEnemy();//����
        attackNum = 0;//��������
        while (enemy->!isDead() && isInRange(enemy) && my->!isDead() && my->state == ATTACK) //����������������
        {
            attackNum++;//��������+1
            int hurt = (int)(my->attack * enemy->attackRate);//�˺�ֵ
            effect.bomb(enemy);//��ը��Ч
            if (attackNum % 3 == 0 || clock() - start >= 4)//���������ͬһĿ�깥�����λ��ӳ�4��
            {
                //T* initEnemy = enemy;    ʵ����һ��Χ�ڶ����е��˵Ĺ�������Ҫ������ȷ��֮��õ�����
                //while(getDistance(enemy=getEnemy())<һ��ĶԽ��߳���)
                enemy->blood -= level == 1 ? 95 : 135;//�����ʵ�˺�
            }
            else
            {
                enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//�����˺�
                enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ������
                if (enemy->blood < 0)
                    enemy->blood = 0;//�з�����
            }
            my->attack += attack / 2;//ÿ�ι���������50%���˺�
        }
    }
}