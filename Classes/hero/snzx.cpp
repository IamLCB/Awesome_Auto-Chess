#include "snzx.h"
//ȫ��̹��
snzx::snzx()
{
    name = "��֮��", skillname = "�Ű���";
    skillType = PHYSICS;
    blood = 800;//��ǰѪ��
    maxBlood = 800;//����ֵ
    level = 1; //�ȼ�
    attack = 50; //������
    protect = 30;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    attackDistance = 2;//��������
    price = 4;//����
    speed = 0.7;//����
}

void snzx::upLevelsnzx(Hero* snzx1, Hero* snzx2, Hero* snzx3)
{
    snzx1->blood = 1440;//��ǰѪ��
    snzx1->maxBlood = 1440;//����ֵ
    snzx1->level = 2; //�ȼ�
    snzx1->attack = 90; //������
    snzx2->removeFromParent();
    snzx3->removeFromParent();
}

void snzx::Play()
{
    static Hero* enemy;
    static int attackNum = 0;
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    {
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
        };
        this->schedule(lambda, 1 / 60.f, "snzxMove");
        enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
        attackNum = 0;//��������
        static int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
        static int add = (level == 1 ? 50 : 100);
       // while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK)//������������������������� 
        {
            attackNum++;//�Ըõ��˵Ĺ�������+1
            auto lambda = [=](float dt) {
                snzx::snzxAttack(enemy, attackNum,hurt,add);
            };
            this->schedule(lambda, 1 / speed, "snzxAttack");

        }
    }
    //this->removeFromParent();
}


Hero* snzx::initsnzx()
{
    Hero* snzx = static_cast<Hero*>(snzx::create());
    snzx->picturename = "./hero/snzx.png";
    snzx->picturenum = 1;
    snzx->heroAnimation(snzx->picturename, snzx->picturenum, snzx, speed, -1);
    return snzx;
}


void snzx::snzxAttack(Hero* enemy, const int attackNum,const int hurt, const int add)
{
    blue += 30;
    int extra = (level == 1) ? 200 : 300;
    if (blue == blueMax)//���������ͬһĿ�깥��5
    {
        this->blood += ((level == 1) ? 250 : 450);
        //createHealthBar(const string& backgroundTexture, const std::string& foregroundTexture, double initialPercentage, const Vec2& position);
        Hero* enemynow = getEnemyByDistance(this,  true,this->ofPlayer);//������Զ
        moveToFar(enemynow);
        Dizzy(enemynow);
        enemynow->blood -= (hurt + extra + add - enemynow->protect);
        blue = 0;
    }
    else
    {
        enemy->setColor(Color3B::YELLOW);
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
}

//��ʱû��ʵ�֣����Բο��Ѿ�ʵ���˵�����
void snzx::moveToFar( Hero* enemy)
{
    // ��ȡ���˵�λ����Ϣ
    cocos2d::Vec2 enemyPosition = enemy->getPosition();

    // ��ȡ������λ����Ϣ
    cocos2d::Vec2 selfPosition = getPosition();

    // ������˺�����֮��ľ���
    float distance = enemyPosition.distance(selfPosition);

    // ȷ�����������
    if (distance > 0)
    {
        // ����Ŀ��λ���ڵ��������λ��
        cocos2d::Vec2 targetPosition = enemyPosition - (enemyPosition - selfPosition);

        // ʹ��Cocosϵͳ��������ɫ�ƶ���Ŀ��λ��
        runAction(cocos2d::MoveTo::create(0.f, targetPosition));
    }
}