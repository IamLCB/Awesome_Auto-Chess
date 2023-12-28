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
    x = 0, y = 0;//�������ϵ�����
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
    //Hero* enemy;
    int attackNum = 0;
   // while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        attackNum = 0;//��������
        static Hero* enemy = getEnemyByDistance(this, opPlayerData);
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
            //int attackNum = 0;
            //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
            //{
                //attackNum++;//�Ըõ��˵Ĺ�������+1
                //auto lambdb = [=](float dt) {
                    //tfns::tfnsAttack(enemy, attackNum);
                //};
                //this->schedule(lambdb, 1 / speed, "tfnsAttack");

            //}
        };
        this->schedule(lambda, 1 / 60.f, "tfnsMove");
    }
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