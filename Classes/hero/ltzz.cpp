#include "ltzz.h"

template <typename T>
ltzz<T>::ltzz()
{
    name = "����֮��", skillname = "����ŭצ";
    skillType = MAGIC;
    blood = 750;//��ǰѪ��
    maxBlood = 750;//����ֵ
    attack = 70; //������
    protect = 30;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 1;//��������
    magicAmount = 75;//����ֵ
    price = 3;//����
    x = 0, y = 0;//�������ϵ�����
    speed = 0.65;//����
}

template <typename T>
void ltzz<T>::Play()
{
    T* enemy, tmpEnemy;
    int attackNum = 0;
    while (!isDead() && !isEnd())
    {
        enemy = getEnemy();//����
        while (enemy->!isDead() && isInRange(enemy) && !isDead() && my->state == ATTACK)//����������������
        {
            int hurt = (int)((level == 1 ? 1.9 : 2) * attack * enemy->attackRate);//�˺�ֵ
            //���ȶ��������ĵ��˽��й�����ħ���˺�
            effect.Lightning(enemy);//��Ч
            enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//������
            enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ���˺�
            if (enemy->blood < 0) {
                enemy->blood = 0;
                break;//�з�������
            }
            for (int i = 0; i < 4; i++) {//��฽�ӹ���4������
                int start = clock();
                while (clock() - start <= 5);//�ڶ�ʮ����ÿ�������һ���������н��и������繥��
                getEnemy(enemy);//û�о�������
                effect.Lightning(enemy);//��Ч
                enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ���˺�
                if (enemy->blood < 0) {
                    enemy->blood = 0;
                    break;//�з�������
                }
            }
        }
    }
}