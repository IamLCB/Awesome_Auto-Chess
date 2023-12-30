#include "tfns.h"


tfns::tfns()
{
    name = "�췣����", skillname = "ʥ�����";
    skillType = PHYSICS;
    blood = 550;//��ǰѪ��
    maxBlood = 550;//����ֵ
    level = 1; //�ȼ�
    attack = 40; //������
    protect = 25;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 500;//��������
    price = 1;//����
    speed = 0.7;//����
}

void tfns::upLeveltfns(Hero* tfns1, Hero* tfns2, Hero* tfns3)
{
    tfns1->blood = 990;//��ǰѪ��
    tfns1->maxBlood = 990;//����ֵ
    tfns1->level = 2; //�ȼ�
    tfns1->attack = 72; //������
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
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        //{
        attackNum++;//�Ըõ��˵Ĺ�������+1
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
    int hurt = (int)((level == 1 ? 1.08 : 1.12) * attack * enemy->attackRate);//�˺�ֵ
    enemy->setColor(Color3B::BLUE);
    blue += 30;
    if (blue == blueMax)//��������������
    {
        enemy->blood -= hurt;//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}
