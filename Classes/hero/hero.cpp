#include "hero.h"

Hero* createHero(int name)
{
    Hero* hero;
    switch (name) {
        case(TFNS):
            tfns* my = new tfns();
            hero = my->initHero();
    }
    return hero;
}

Node* Hero::createHealthBar(const std::string& backgroundTexture, const std::string& foregroundTexture, double initialPercentage, const Vec2& position) {
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
    if (blood == 0)
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

Hero* Hero::getEnemyByDistance(Hero* myHero, playerData& opPlayer, bool mode = false)
{
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


void Effect::Dizzy(Hero* enemy)
{
    //Ӣ�۱�ɻ�ɫ
    enemy->setColor(Color3B::GRAY);
    // ����Ӣ�۵Ķ���
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // ��������ӻָ�����״̬�Ĳ�������Ӣ�۵���ɫ�ָ�Ϊԭʼ��ɫ
        enemy->setColor(Color3B::WHITE);
        // ��������Ӣ�۵Ķ���
        enemy->heroAnimation(enemy->picturename, enemy->picturenum, enemy, enemy->speed, -1);
    };
    enemy->scheduleOnce(lambda, 4, "dizzyKey");
}

void Effect::sevInjure(Hero* enemy)
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

void Effect::proProtect(Hero *my)
{
    my->protect = (int)(my->protect * 1.2);
}


void Effect::relProtect(Hero* enemy)
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


void Effect::immune(Hero* enemy)
{
    double Rate = enemy->attackRate;
    enemy->attackRate = 0;
    auto lambda = [=](float dt) {
        enemy->attackRate = Rate;
    };
    enemy->scheduleOnce(lambda, 2, "immuneKey");
}