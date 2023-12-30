#include "wlshz.h"

wlshz::wlshz()
{
    name = "δ���ػ���", skillname = "��������";
    skillType = TANK;
    blood = 700;//��ǰѪ��
    maxBlood = 700;//����ֵ
    level = 1; //�ȼ�
    attack = 60; //������
    protect = 35;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    magicAmount = 50;//����ֵ
    attackDistance = 100;//��������
    price = 2;//����
    speed = 0.65;//����
}

void wlshz::upLevelwlshz(Hero* wlshz1, Hero* wlshz2, Hero* wlshz3)
{
    wlshz1->blood = 1260;//��ǰѪ��
    wlshz1->maxBlood = 1260;//����ֵ
    wlshz1->level = 2; //�ȼ�
    wlshz1->attack = 108; //������
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
    //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
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
    int hurt = (int)((level == 1 ? 2.00 : 3.50) * attack * enemy->attackRate);//�˺�ֵ
    enemy->setColor(Color3B::ORANGE);
    blue += 30;
    Dizzy(enemy);
    if (blue == blueMax)//��������������
    {
        enemy->blood -= hurt;//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ������
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}