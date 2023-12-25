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
    // 创建血条底部背景精灵
    Sprite* backgroundSprite = Sprite::create(backgroundTexture);

    // 创建血条前景精灵
    Sprite* foregroundSprite = Sprite::create(foregroundTexture);

    // 创建血条的 ProgressTimer
    ProgressTimer* healthBar = ProgressTimer::create(foregroundSprite);
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));//??????????//更改位置？
    healthBar->setBarChangeRate(Vec2(1, 0));//??????????//更改位置？
    healthBar->setPercentage(initialPercentage);

    // 设置血条底部背景精灵和 ProgressTimer 的位置
    backgroundSprite->setPosition(position);
    healthBar->setPosition(position);

    // 创建容器节点，将血条底部背景精灵和 ProgressTimer 添加到容器中
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
    animation->setDelayPerUnit(speed); //设定速度
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,循环
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
            // 最远的敌人
            if (tempDistance > opDistance && tempDistance > 0 && !((static_cast<Hero*>(tempEnemy))->isDead()))
            {
                opDistance = tempDistance;
                enemyPosition = tempEnemyPosition;
                enemy = static_cast<Hero*>(tempEnemy);
            }
        }
        else
        {
            // 最近的敌人
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
    //英雄变成灰色
    enemy->setColor(Color3B::GRAY);
    // 禁用英雄的动作
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄的动作
        enemy->heroAnimation(enemy->picturename, enemy->picturenum, enemy, enemy->speed, -1);
    };
    enemy->scheduleOnce(lambda, 4, "dizzyKey");
}

void Effect::sevInjure(Hero* enemy)
{
    //英雄变成红色
    enemy->setColor(Color3B::RED);
    // 禁用英雄
    enemy->movespeed = enemy->movespeed * 0.5;
    enemy->speed = enemy->speed * 0.5;
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄
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
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
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