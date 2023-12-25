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
    attackDistance = 3;//��������
    price = 1;//����
    x = 0, y = 0;//�������ϵ�����
    speed = 0.7;//����

}


void tfns::Play()
{
    Hero* enemy;
    int attackNum = 0;
    while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        enemy = getEnemyByDistance(this, opPlayerData);//����
        attackNum = 0;//��������
        while (!enemy->isDead() && isInAttackRange(this,enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                tfns::tfnsAttack(enemy, attackNum);
            };
            this->schedule(lambda, 1 / speed, "tfnsAttack");

        }
    }
}


Hero* tfns::initHero()
{
    Hero* tfns = static_cast<Hero*>(tfns::create());
    // my = tfns;
    tfns->picturename = "./hero/tfns%d.png";
    tfns->picturenum = 3;
    //tfns->setPosition(800, 460);
    tfns->heroAnimation(tfns->picturename, tfns->picturenum, tfns, speed, -1);
    //tfns->autorelease();
    return tfns;
}


void tfns::tfnsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)((level == 1 ? 1.08 : 1.12) * attack * enemy->attackRate);//�˺�ֵ
    blue += 30;
    if (blue == blueMax)//���������ͬһĿ�깥������
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
    //shootArrow("pea.png", enemy->getPosition() - this->getPosition(), this);
}


void tfns::shootArrow(string picturename, Point deltaPos)
{
    Sprite* arrow = Sprite::create(picturename);
    this->addChild(arrow);
    arrow->setPosition(40, 30);//??????????//���ľ��룿
    auto move = MoveBy::create(1.f, deltaPos);
    auto back = MoveTo::create(0.f, Vec2(40, 30));//??????????//���ľ��룿
    auto appear = FadeIn::create(0.f);
    auto disappear = FadeOut::create(0.f);

    auto actionTo = Sequence::createWithTwoActions(appear, move);
    auto actionBack = Sequence::createWithTwoActions(disappear, back);
    auto all = Sequence::createWithTwoActions(actionTo, actionBack);
    arrow->runAction(Repeat::create(all, 1));
}