#include "hero.h"
#include "tfns.h"
#include "mlps.h"
#include "ltzz.h"
#include "bqzs.h"
#include "yn.h"
#include "qxsq.h"
#include "snzx.h"

Hero* createHero(int name) {
    Hero* hero = nullptr;
    switch (name) {
        case TFNS:
        {
            tfns* tfnsHero = new tfns();
            hero = tfnsHero->inittfns();
        }
        break;
        case BQZS:
        {
            bqzs* bqzsHero = new bqzs();
            hero = bqzsHero->initbqzs();
        }
        break;
        case MLPS:
        {
            mlps* mlpsHero = new mlps();
            hero = mlpsHero->initmlps();
        }
        break;
        case QXSQ:
        {
            qxsq* qxsqHero = new qxsq();
            hero = qxsqHero->initqxsq();
        }
        break;
        case YN:
        {
            ynyn* ynynHero = new ynyn();
            hero = ynynHero->initynyn();
        }
        break;
        case LTZZ:
        {
            ltzz* ltzzHero = new ltzz();
            hero = ltzzHero->initltzz();
        }
        break;
        case SNZX:
        {
            snzx* snzxHero = new snzx();
            hero = snzxHero->initsnzx();
        }
        break;
    }
    return hero;
}

Node* Hero::createHealthBar(const string& backgroundTexture, const std::string& foregroundTexture, double initialPercentage, const Vec2& position) {
    // ����Ѫ���ײ���������
    Sprite* backgroundSprite = Sprite::create(backgroundTexture);

    // ����Ѫ��ǰ������
    Sprite* foregroundSprite = Sprite::create(foregroundTexture);

    // ����Ѫ���� ProgressTimer
    ProgressTimer* healthBar = ProgressTimer::create(foregroundSprite);
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));//??????????//����λ�ã�
    healthBar->setBarChangeRate(Vec2(1, 0));//??????????//����λ�ã�
    healthBar->setPercentage(initialPercentage);

    // ����Ѫ���ײ���������� ProgressTimer ��λ��
    backgroundSprite->setPosition(position);
    healthBar->setPosition(position);

    // ���������ڵ㣬��Ѫ���ײ���������� ProgressTimer ��ӵ�������
    Node* containerNode = Node::create();
    containerNode->addChild(backgroundSprite);
    containerNode->addChild(healthBar);

    return containerNode;
}

bool Hero::isDead()
{
    if (this->blood == 0)
        return true;
    return false;
}

void Hero::heroAnimation(string picturename, const int picturenum, Sprite* sprite, const double speed, const int loop)
{
    Animation* animation = Animation::create();
    const char* picname = picturename.c_str();

    for (int i = 0; i < picturenum; i++) {
        char key[32];
        sprintf(key, picname, i);
        animation->addSpriteFrameWithFile(key);
    }
    animation->setDelayPerUnit(speed); //�趨�ٶ�
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,ѭ��
    auto action = Animate::create(animation);
    //action->setTag(-2);
    //sp->runAction(animate);
    sprite->runAction(action);
}

Hero* Hero::getEnemyByDistance(Hero* myHero, bool mode, bool isMyHero)
{
    playerData opPlayer;
    if(isMyHero){
        opPlayer = opPlayerData;
    }
    else {
        opPlayer = myPlayerData;
    }
    Point enemyPosition(0, 0);
    Point myPosition = myHero->getPosition();
    float opDistance = mode ? -999999 : 999999;
    Hero* enemy = NULL;
    for (int i = 0; i < opPlayer.battleArray->num; i++)
    {
        auto tempEnemy = opPlayer.battleArray->arr[i];
        Point tempEnemyPosition = (static_cast<Hero*>(tempEnemy))->getPosition();
        float tempDistance = sqrt((tempEnemyPosition.x - myPosition.x) * (tempEnemyPosition.x - myPosition.x) +
            (tempEnemyPosition.y - myPosition.y) * (tempEnemyPosition.y - myPosition.y));
        if (mode)
        {
            // ��Զ�ĵ���
            if (tempDistance > opDistance && tempDistance > 0 && !((static_cast<Hero*>(tempEnemy))->isDead()))
            {
                opDistance = tempDistance;
                enemyPosition = tempEnemyPosition;
                enemy = static_cast<Hero*>(tempEnemy);
            }
        }
        else
        {
            // ����ĵ���
            if (tempDistance < opDistance && tempDistance > 0 && !((static_cast<Hero*>(tempEnemy))->isDead()))
            {
                opDistance = tempDistance;
                enemyPosition = tempEnemyPosition;
                enemy = static_cast<Hero*>(tempEnemy);
            }
        }
    }

    return enemy;
}

void Hero::update(Hero* my, Hero* enemy, float dt)
{
    Vec2 currentPosition = my->getPosition();
    Vec2 targetPosition = enemy->getPosition(); // ��ȡĿ��λ��
    // ������С�ķ������
    float separationDistance = 200.0f;
    // �����ƶ��ٶ�
     // �����ƶ���������
    Vec2 direction = targetPosition - currentPosition;
    direction.normalize();
    float movespeed = 100.0f;
    // ����������ɫ֮��ľ���
    float distance = currentPosition.distance(targetPosition);
    if (distance < separationDistance)
    {
        // �����������
        Vec2 separationVector = currentPosition - targetPosition;
        separationVector.normalize();

        // ���ݷ������������ƶ�����
        direction += separationVector;
        direction.normalize();
    }
    // ���ݷ��������ƶ�Ӣ��
    Vec2 newPosition = currentPosition + direction * movespeed * dt;
    my->setPosition(newPosition);
}

bool Hero::isWin(playerData* myPlayer, playerData* opPlayer)
{
    if (myPlayer->battleArray->num == 0 || opPlayer->battleArray->num == 0)
        return true;
    else
        return false;
    return false;
}

bool Hero::isInAttackRange(Hero* myHero, Hero* enemyHero)
{
    Point myPosition = myHero->getPosition();
    Point enemyPosition = enemyHero->getPosition();
    float distance = sqrt((myPosition.x - enemyPosition.x) * (myPosition.x - enemyPosition.x) +
        (myPosition.y - enemyPosition.y) * (myPosition.y - enemyPosition.y));
    if (distance <= myHero->attackDistance)
        return true;
    return false;
}


void Dizzy(Hero* enemy)
{
    //Ӣ�۱�ɻ�ɫ
    enemy->setColor(Color3B::GRAY);
    //����Ӣ�۵Ķ���
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        // ��������Ӣ�۵Ķ���
        enemy->heroAnimation(enemy->picturename, enemy->picturenum, enemy, enemy->speed, -1);
    };
    enemy->scheduleOnce(lambda, 4, "dizzyKey");
}

void sevInjure(Hero* enemy)
{
    //Ӣ�۱�ɺ�ɫ
    enemy->setColor(Color3B::RED);
    // ����Ӣ��
    enemy->movespeed = enemy->movespeed * 0.5;
    enemy->speed = enemy->speed * 0.5;
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        // ��������Ӣ��
        enemy->movespeed = enemy->movespeed * 2;
        enemy->speed = enemy->speed * 2;
    };
    enemy->scheduleOnce(lambda, 2, "sevInjureKey");
}

void proProtect(Hero* my)
{
    my->protect = (int)(my->protect * 1.2);
}


void relProtect(Hero* enemy)
{
    enemy->setColor(Color3B::GREEN);
    enemy->protect = (int)(enemy->protect * 0.8);
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        enemy->protect = (int)(enemy->protect * 1.25);
    };
    enemy->scheduleOnce(lambda, 2, "relProtect");
}


void immune(Hero* enemy)
{
    double Rate = enemy->attackRate;
    enemy->attackRate = 0;
    auto lambda = [=](float dt) {
        enemy->attackRate = Rate;
    };
    enemy->scheduleOnce(lambda, 2, "immuneKey");
}

void bomb(Hero* enemy, int attack)
{
    //Ӣ�۱�ɻ�ɫ
    enemy->setColor(Color3B::YELLOW);
    auto lambda = [=](float dt) {
        enemy->blood -= (int)(attack * enemy->attackRate * 1.5);
    };
    enemy->scheduleOnce(lambda, 2, "bombKey");
}

void lightning(Hero* enemy, const int hurt)
{
    //Ӣ�۱����ɫ
    enemy->setColor(Color3B::GRAY);
    enemy->blood -= hurt * 0.9;//��ɶ���90%���˺�
}
