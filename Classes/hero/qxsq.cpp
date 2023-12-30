#include "qxsq.h"

template <typename T>
qxsq<T>::qxsq()
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
    x = 0, y = 0;//�������ϵ�����
    speed = 0.65;//����
}

template <typename T>
void qxsq<T>::Play()
{
    T* enemy;
    int attackNum = 0;
    while (!isDead() && !isEnd())
    {
        enemy = getEnemy();//���У��ɹ�����Χ����Զ
        attackNum = 0;//��������
        int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
        int add = (level == 1 ? 125 : 250);
        while (enemy->!isDead() && isInRange(enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                qxsq<T>::qxsqAttack(enemy, attackNum,hurt ,add);
            };
            this->schedule(lambda, 1 / speed);
        }
    }
}

template <typename T>
qxsq<T>* qxsq<T>::initqxsq()
{
    auto qxsq = qxsq::create();
    my = qxsq;
    qxsq->picturename = "./hero/qxsq.png";
    qxsq->picturenum = 2;
    qxsq->heroAnimation(qxsq->picturename, qxsq->picturenum, qxsq, qxsq->getPosition(), speed, -1);//??????????//δʶ��
    //tfns->autorelease();
    return qxsq;
}



template <typename T>
void qxsq<T>::qxsqAttack(T* enemy, const int attackNum,const int hurt,const int add)
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
    shootbullet("zidan.png", enemy->getPosition() - this->getPosition(), this);
}

template <typename T>
void qxsq<T>::shootbullet(string picturename, Point Pos, qxsq<T>* my)
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