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
    animation->setDelayPerUnit(speed); //设定速度
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loop); //loop=-1,循环
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

void Hero::update(Hero* my, Hero* enemy, float dt)
{
    Vec2 currentPosition = my->getPosition();
    Vec2 targetPosition = enemy->getPosition(); // 获取目标位置
    // 设置最小的分离距离
    float separationDistance = 200.0f;
    // 设置移动速度
     // 计算移动方向向量
    Vec2 direction = targetPosition - currentPosition;
    direction.normalize();
    float movespeed = 100.0f;
    // 计算两个角色之间的距离
    float distance = currentPosition.distance(targetPosition);
    if (distance < separationDistance)
    {
        // 计算分离向量
        Vec2 separationVector = currentPosition - targetPosition;
        separationVector.normalize();

        // 根据分离向量调整移动方向
        direction += separationVector;
        direction.normalize();
    }
    // 根据方向向量移动英雄
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
    //英雄变成灰色
    enemy->setColor(Color3B::GRAY);
    //禁用英雄的动作
    enemy->stopAllActions();
    auto lambda = [=](float dt) {
        // 在这里添加恢复正常状态的操作，将英雄的颜色恢复为原始颜色
        enemy->setColor(Color3B::WHITE);
        // 重新启用英雄的动作
        enemy->heroAnimation(enemy->picturename, enemy->picturenum, enemy, enemy->speed, -1);
    };
    enemy->scheduleOnce(lambda, 4, "dizzyKey");
}

void sevInjure(Hero* enemy)
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

void proProtect(Hero* my)
{
    my->protect = (int)(my->protect * 1.2);
}


void relProtect(Hero* enemy)
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
    //英雄变成黄色
    enemy->setColor(Color3B::YELLOW);
    auto lambda = [=](float dt) {
        enemy->blood -= (int)(attack * enemy->attackRate * 1.5);
    };
    enemy->scheduleOnce(lambda, 2, "bombKey");
}

void lightning(Hero* enemy, const int hurt)
{
    //英雄变成蓝色
    enemy->setColor(Color3B::GRAY);
    enemy->blood -= hurt * 0.9;//造成额外90%的伤害
}
