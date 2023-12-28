#include "ltzz.h"

ltzz::ltzz()
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
    ltzz1->blood = 1350;//��ǰѪ��
    ltzz1->maxBlood = 1350;//����ֵ
    ltzz1->level = 2; //�ȼ�
    ltzz1->attack = 126; //������
    ltzz2->removeFromParent();
    ltzz3->removeFromParent();
}

void ltzz::Play()
{
    Hero* enemy, tmpEnemy;
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    //{
        enemy = getEnemyByDistance(this, opPlayerData);//����
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
        };
        this->schedule(lambda, 1 / 60.f, "ltzzMove");
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//����������������
        //{
            auto lambdc = [=](float dt) {
                ltzz::ltzzAttack(enemy);
            };
            this->schedule(lambdc, 1 / speed, "ltzzAttack");
            //??????????//�Ƿ����ͬʱ���У�
            auto lambdb = [=](float dt) {
                for (int i = 0; i < 4; i++)//��฽�ӹ���4������
                {
                    Hero* tmpenemy = getEnemyByDistance(this, opPlayerData, true);//û�о�������
                    ltzz::ltzzAttack(tmpenemy);
                }
            };
            this->schedule(lambdb, 20, "ltzzlightAttack");
        //}
    //}
}

void ltzz::ltzzAttack(Hero* enemy)
{
    int hurt = (int)((level == 1 ? 1.9 : 2) * attack * enemy->attackRate);//�˺�ֵ
    //���ȶ��������ĵ��˽��й�����ħ���˺�
    lightning(enemy, hurt);//������Ч
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//��������
    enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ���˺�
    if (enemy->blood < 0) 
        enemy->blood = 0;
}