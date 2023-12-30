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
    static Hero* enemy;
    static int attackNum = 0;
    auto lambdb = [=](float dt) {
        this->update(this, enemy, dt);
        this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
    };
    this->schedule(lambdb, 1 / 60.f, "qxsqMove");
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, true, this->ofPlayer);//����
        attackNum = 0;//��������
        static int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
        static int add = (level == 1 ? 125 : 250);
       // while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                qxsq::qxsqAttack(enemy, attackNum,hurt ,add);
            };
            this->schedule(lambda, 1 / speed,"qxsqAttack");
            auto lambdc = [=](float dt) {
                enemy->setColor(Color3B::GRAY);
            };
            this->schedule(lambdc,  speed, "tmp22");
        }
    }
    //this->removeFromParent();
}


Hero* qxsq::initqxsq()
{
    Hero* qxsq = static_cast<Hero*>(qxsq::create());
   // my = qxsq;
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 1;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, speed, -1);
    //tfns->autorelease();
    return qxsq;
}




void qxsq::qxsqAttack(Hero* enemy, const int attackNum,const int hurt,const int add)
{
    blue += 50;
    enemy->setColor(Color3B::BLUE);
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
    //shootbullet("zidan.png", enemy->getPosition() - this->getPosition(), this);//??????????//ͼƬ
}


void qxsq::shootbullet(string picturename, Point Pos, Hero* my)
{
    Sprite* bullet = Sprite::create(picturename);
    this->addChild(bullet);
    bullet->setPosition(400,230);//??????????//���ľ��룿

    auto move = MoveBy::create(1.f, Pos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//���ľ��룿
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    bullet->runAction(Repeat::create(all, 1));
}