#include "mlps.h"

mlps::mlps()
{
    name = "��������", skillname = "��ը��";
    skillType = MAGIC;
    blood = 500;//��ǰѪ��
    maxBlood = 500;//����ֵ
    protect = 20;//����
    magicPro = 20;//ħ��
    state = ATTACK;//����״̬
    magicAmount = 50;//����ֵ
    attackDistance = 4;//��������
    price = 1;//����
    speed = 0.65;//����
}

Hero* mlps::initmlps()
{
    Hero* mlps = static_cast<Hero*>(mlps::create());
    mlps->picturename = "./hero/mlps.png";
    mlps->picturenum = 1;
    mlps->heroAnimation(mlps->picturename, mlps->picturenum, mlps, speed, -1);
    return mlps;
}

void mlps::upLevelmlps(Hero* mlps1, Hero* mlps2, Hero* mlps3)
{
    mlps1->blood = 900;//��ǰѪ��
    mlps1->maxBlood = 900;//����ֵ
    mlps1->level = 2; //�ȼ�
    mlps1->attack = 90; //������
    mlps2->removeFromParent();
    mlps3->removeFromParent();
}

void mlps::Play()
{
    Hero* enemy;
    int attackNum = 0;
    //while (!isDead() && !isWin(&myPlayerData, &opPlayerData))
    //{
    enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
        auto lambda = [=](float dt) {
            this->update(this, enemy, dt);
            this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
            isDead();
        };
        this->schedule(lambda, 1 / 60.f, "mlpsMove");
        attackNum = 0;//��������
        //while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK) //����������������
        //{
            attackNum++;//��������+1
            auto lambdb = [=](float dt) {
                mlps::mlpsAttack(enemy, attackNum);
            };
            this->schedule(lambdb, 1 / speed, "mlpsAttack");
            auto lambdc = [=](float dt) {
                enemy->setColor(Color3B::YELLOW);
            };
            this->schedule(lambdc, speed, "tmp");
        //}
    //}
}

void mlps::mlpsAttack(Hero* enemy, const int attackNum)
{
    int hurt = (int)(attack * enemy->attackRate);//�˺�ֵ
    blue += 30;
    enemy->setColor(Color3B::RED);
    if (blue == blueMax)//��������������
    {
        enemy->blood -= level == 1 ? 95 : 135;//�����ʵ�˺�
        bomb(enemy, attack);//��ը��Ч
        blue = 0;
    }
    else
    {
        enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//�����˺�
        enemy->magicPro > magicAmount ? enemy->blood -= 0 : enemy->blood -= magicAmount - enemy->magicPro;//ħ������
    }
    if (enemy->blood < 0)
        enemy->blood = 0;//�з�����
    attack += attack / 2;//ÿ�ι���������50%���˺�
    
    //�ӳ�����
    auto lambda = [=](float dt) {
        enemy->blood -= level == 1 ? 95 : 135;//�����ʵ�˺�
    };
    enemy->scheduleOnce(lambda, 4, "mlpsTimeAttack");
}