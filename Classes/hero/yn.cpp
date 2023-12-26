#include "yn.h"


yn::yn()
{
    name = "����", skillname = "Ӱ������";
    skillType = PHYSICS;
    blood = 550;//��ǰѪ��
    maxBlood = 550;//����ֵ
    level = 1; //�ȼ�
    attack = 70; //������
    protect = 20;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 1;//��������
    price = 3;//����
    x = 0, y = 0;//�������ϵ�����
    speed = 0.6;//����
}


Hero* yn::inityn()
{
    Hero* yn = static_cast<Hero*>(yn::create());
    //my = yn;
    yn->picturename = "./hero/yn%d.png";
    yn->picturenum = 3;
    yn->heroAnimation(yn->picturename, yn->picturenum, yn,  speed, -1);
   
    return yn;
}



void yn::Play()
{
    Hero* enemy;
    int attackNum = 0;
    while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, opPlayerData);//����
        attackNum = 0;//��������
        double add = (level == 1) ? 300 : 400;
        double exp = (level == 1) ? 3 : 4;
        int hurt = (int)(enemy->attackRate * attack);
        while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                yn::ynNormalAttack(enemy, attackNum,add,hurt);
            };
            this->schedule(lambda, 1 / speed,"ynAttack");
            // �ͷż���
            if (blue == blueMax) {
                auto lambdc = [=](float dt) {
                    yn::swordwaive("sword.png", this);//??????????//picture
                    yn::goaway(enemy->getPosition(),this);//�ܵ�Զ��//??????????//getposition
                    if (enemy->blood > (int)(0.5 * enemy->maxBlood)) {
                        enemy->blood -= (int)(hurt - (enemy->protect) + add);//��Ѫ���ӳ��˺�
                    }
                    else {
                        enemy->blood -= (int)(hurt - (enemy->protect) + add*exp);//��Ѫ���ӱ��˺�
                    }
                };
                this->schedule(lambdc, 1 / speed,"ynNormalAttack");//�ͷż���
                blue = 0;
            }
            if (enemy->blood < 0)
                enemy->blood = 0;//�з�����
        }
    }
}

void yn::ynNormalAttack(Hero* enemy, const int attackNum,const double add,const int hurt)
{
    blue += 30;
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    swordwaive("sword.png", this);//??????????//picture
}

void yn::swordwaive(string picturename, Hero* my)
{
    Sprite* sword = Sprite::create(picturename);
    this->addChild(sword);
    sword->setPosition(Vec2(0, 0)); // ���õ��ĳ�ʼλ��//??????????//���ľ��룿
    // ���赶�Ķ�������
    auto waive = Sequence::create(
        RotateTo::create(0.05f, -45),   // ��������ת
        RotateTo::create(0.1f, 0),      // ���ָ�ԭʼ�Ƕ�
        nullptr
    );
    // ִ�ж�������
    sword->runAction(waive);
}

void yn::goaway(Point Pos,Hero* my) {
    // �ܵ�Զ���Ķ�������
    double distance = 5;//??????????//���ľ��룿
    auto run = Sequence::create(
        MoveTo::create(1.f, Vec2(Pos.x + distance, Pos.y));//??????????//���ľ��룿
        nullptr
    );
    // ִ�ж�������
    my->runAction(run);
}
