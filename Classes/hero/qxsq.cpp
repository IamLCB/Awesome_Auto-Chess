#include "qxsq.h"


qxsq::qxsq()
{
    name = "��аʥǹ", skillname = "���׷��";
    skillType = PHYSICS;
    blood = 600;//��ǰѪ��
    maxBlood = 600;//����ֵ
    level = 1; //�ȼ�
    attack = 65; //������
    protect = 25;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 3;//��������
    price = 2;//����
    speed = 0.65;//����
}

void qxsq::upLevelqxsq(Hero* qxsq1, Hero* qxsq2, Hero* qxsq3)
{
    qxsq1->blood = 1080;//��ǰѪ��
    qxsq1->maxBlood = 1080;//����ֵ
    qxsq1->level = 2; //�ȼ�
    qxsq1->attack = 117; //������
    qxsq2->removeFromParent();
    qxsq3->removeFromParent();
}

void qxsq::Play()
{
    Hero* enemy;
    int attackNum = 0;
    while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, opPlayerData);//����
        attackNum = 0;//��������
        int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
        int add = (level == 1 ? 125 : 250);
        while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                qxsq::qxsqAttack(enemy, attackNum,hurt ,add);
            };
            this->schedule(lambda, 1 / speed,"qxsqAttack");
        }
    }
    this->removeFromParent();
}


Hero* qxsq::initqxsq()
{
    Hero* qxsq = static_cast<Hero*>(qxsq::create());
   // my = qxsq;
    qxsq->picturename = "./hero/qxsq%d.png";
    qxsq->picturenum = 3;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, speed, -1);
    //tfns->autorelease();
    return qxsq;
}




void qxsq::qxsqAttack(Hero* enemy, const int attackNum,const int hurt,const int add)
{
    blue += 50;
    if (blue == blueMax)//���������ͬһĿ�깥������
    {
        enemy->blood -= (hurt + add);//�����ʵ�˺�
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
    shootbullet("zidan.png", enemy->getPosition() - this->getPosition(), this);//??????????//ͼƬ
}


void qxsq::shootbullet(string picturename, Point Pos, Hero* my)
{
    Sprite* bullet = Sprite::create(picturename);
    this->addChild(bullet);
    bullet->setPosition(40, 30);//??????????//���ľ��룿

    auto move = MoveBy::create(1.f, Pos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//���ľ��룿
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    bullet->runAction(Repeat::create(all, 1));
}