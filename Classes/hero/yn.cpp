#include "yn.h"


ynyn::ynyn()
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
    speed = 0.6;//����
}

void ynyn::upLevelynyn(Hero* yn1, Hero* yn2, Hero* yn3)
{
    yn1->blood = 990;//��ǰѪ��
    yn1->maxBlood = 990;//����ֵ
    yn1->level = 2; //�ȼ�
    yn1->attack = 126; //������
    yn2->removeFromParent();
    yn3->removeFromParent();
}

Hero* ynyn::initynyn()
{
    Hero* yn = static_cast<Hero*>(ynyn::create());
    //my = yn;
    yn->picturename = "./hero/yn.png";
    yn->picturenum = 1;
    yn->heroAnimation(yn->picturename, yn->picturenum, yn,  speed, -1);
   
    return yn;
}



void ynyn::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdd = [=](float dt) {
        this->update(this, enemy, dt);
    };
    this->schedule(lambdd, 1 / 60.f, "ynynMove");
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
        attackNum = 0;//��������
        static double add = (level == 1) ? 300 : 400;
        static double exp = (level == 1) ? 3 : 4;
        static int hurt = (int)(enemy->attackRate * attack);
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                ynyn::ynynNormalAttack(enemy, attackNum,add,hurt);
            };
            this->schedule(lambda, 1 / speed,"ynAttack");
            // �ͷż���
            if (blue == blueMax) {
                auto lambdc = [=](float dt) {
                    ynyn::swordwaive("sword.png", this);//??????????//picture
                    //yn::goaway(enemy->getPosition(),this);//�ܵ�Զ��//??????????//getposition
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
    //this->removeFromParent();
}

void ynyn::ynynNormalAttack(Hero* enemy, const int attackNum,const double add,const int hurt)
{
    blue += 30;
    enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    //swordwaive("sword.png", this);//??????????//picture
    goaway(enemy->getPosition(), this);
}

void ynyn::swordwaive(string picturename, Hero* my)
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

void ynyn::goaway(Point Pos, Hero* my) {
    // �ܵ�Զ���Ķ�������
    double distance = 50; // ���ľ����ֵ
    auto run = Sequence::create(
        MoveTo::create(1.0f, Vec2(Pos.x + distance, Pos.y)), // �޸��ƶ�Ŀ���λ��
        nullptr
    );
    // ִ�ж�������
    my->runAction(run);
}
