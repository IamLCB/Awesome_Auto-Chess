#include "sceneGame.h"
USING_NS_CC;

/**************初始化函数*************/
bool sceneGame::init()
{
    if (!mainMenu::init())
    {
        return false;
    }
    mapInit();
    whichTurn();
    /*******初始化音频*******/

    smallHero* myyhero1 = new smallHero();
    this->myyhero = myyhero1->initSmall();
    myyhero->moveByMouse_R(myyhero);
    myyhero->setPosition(150, 200);
   

    this->addChild(map, 0);

    this->addChild(afterFight, 1);

    this->addChild(myyhero, 2);

    this->addChild(heroExist, 3);

    this->addChild(playerLayer, 4);

    this->addChild(shopLayer, 5);

    this->addChild(settingsLayer, 6);

    //this->addChild(info, 6);

    this->scheduleUpdate();

    map->scheduleUpdate();
    playerLayer->scheduleUpdate();

    return true;
}

void sceneGame::mapInit()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    float original_x = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION_WIDTH;
    float original_y = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION_HEIGHT;

    float eachCell_x = (visibleSize.width / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_ROW;
    float eachCell_y = (visibleSize.height / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_COL;

    for (int i = 0; i < CHESS_IN_A_ROW; i++)
    {
        for (int j = 1; j < CHESS_IN_A_COL + 1; j++)
        {
            chessMap[j][i].x = original_x + eachCell_x / 2 + i * eachCell_x;
            chessMap[j][i].y = original_y + eachCell_y / 2 + (j - 1) * eachCell_y;
        }
        chessMap[0][i].x = original_x + eachCell_x / 2 + eachCell_x * (i - 1) + HERO_SLOT_CORRECTION_WIDTH;
        chessMap[0][i].y = original_y - HERO_SLOT_CORRECTION_HEIGHT;
        chessMap[CHESS_IN_A_COL + 1][i].x = original_x + eachCell_x / 2 + eachCell_x * (i - 1) + HERO_SLOT_CORRECTION_WIDTH;
        chessMap[CHESS_IN_A_COL + 1][i].y = original_y + CHESS_IN_A_COL * eachCell_y + HERO_SLOT_CORRECTION_HEIGHT;
    }
}

void sceneGame::whichTurn()
{
    globalGameData->changeGameTurn();
    auto turn_label = Label::createWithTTF("TURN", "fonts/Marker Felt.ttf", 24);
    turn_label->setPosition(200, 800);
    this->addChild(turn_label, 2);
    char* mTurn = new char[8];
    sprintf(mTurn, "Turn %02d", globalGameData->gameTurn);
    turn_label->setString(mTurn);
}

/**************鼠标操作***************/

void sceneGame::mouseInit()
{
    if (afterFight->totalTime<1e-2 && afterFight->totalTime>-1e-2) // 在战斗期间才初始化
    {
        if (chessSelected < SEPARATION && chessSelected != -1)
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected - 1]);
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(crt->getTempPosition());
            chessSelected = -1; // 重置棋子的位置并清除选中状态
        }
    }
}

void sceneGame::mouseMainEvent()
{
    auto MouseListener = EventListenerMouse::create();
    MouseListener = EventListenerMouse::create();
    MouseListener->onMouseMove = CC_CALLBACK_1(sceneGame::mouseMove, this);
    MouseListener->onMouseUp = CC_CALLBACK_1(sceneGame::mouseUp, this);
    MouseListener->onMouseDown = CC_CALLBACK_1(sceneGame::mouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
}

void sceneGame::mouseUp(Event* event)
{
    auto e = static_cast<EventMouse*>(event);

    if ((int)e->getMouseButton() == 0) // 左键
    {
        if (chessSelected >= 0 && chessSelected < SEPARATION) // 选中战斗区棋子
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // 避免重复选择
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));

            }
            else if (pairReturn(crt->getPosition()).x != 0 && pairReturn(crt->getPosition()).x != 7)   //若不在等候区
            {
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));
                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else
            {
                toWaitingArray(crt, myPlayerData);
            }
        }
        else if (chessSelected >= SEPARATION) // 选中备战区的棋子
        {
            auto crt = static_cast<Hero*>(myPlayerData.waitingArray->arr[chessSelected - SEPARATION]);
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // 避免重复选择
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
            else if (pairReturn(crt->getPosition()).x == 0 || pairReturn(crt->getPosition()).x == 7)  //若在等候区
            {
                //Point temppoint = inWhichCell(temp->getPosition());
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));

                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else if (afterFight->totalTime > 1e-6)//进入备战时间
            {
                if (myPlayerData.battleArray->num < myPlayerData.playerLevel)
                    toBattleArray(crt, myPlayerData);
                else
                {
                    crt->setPosition(inWhichCell(crt->getTempPosition()));
                    crt->set(inWhichCell(crt->getTempPosition()));
                    auto label = Label::createWithTTF("Not enough Grade!", "fonts/Marker Felt.ttf", 36);
                    this->addChild(label);
                    label->setTextColor(Color4B::WHITE);
                    label->setPosition(800, 400);
                    auto move = FadeOut::create(2.0f);
                    label->runAction(move);

                    chessSelected = -1;
                }
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
        }
        chessSelected = -1;
    }

}

void sceneGame::mouseDown(Event* event)
{
    auto e = static_cast<EventMouse*>(event);

    // 判断鼠标按下是在备战区还是战斗区
    if (mouseInBattleArray(myPlayerData.battleArray, e) == 1) // 获得了chessSelected
        mouseInBattleArray(myPlayerData.waitingArray, e);
}

void sceneGame::mouseMove(Event* event)
{
    auto e = static_cast<EventMouse*>(event);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float eachCell_y = (visibleSize.height / 2 + SPATIAL_DEVIATION_CORRECTION) / CHESS_IN_A_COL;

    if (chessSelected != -1)
    {
        if (chessSelected < SEPARATION && afterFight->totalTime < 1e-2)// 没时间了,不进行移动操作
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]); // -1?
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(inWhichCell(crt->getTempPosition()));
            chessSelected = -1; // 完成操作，鼠标回到未选中状态
            return;
        }
        else if (chessSelected < SEPARATION) // 可以移动战斗区的棋子
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);// -1?
            auto crtPosition = inWhichCell(crt->getPosition());

            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[3][0].y + eachCell_y / 2) //  空气墙，限制在我方场上
            {
                crt->setPosition(e->getCursorX(), e->getCursorY());
                crt->set(e->getCursorX(), e->getCursorY());  // 移动
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1;  // 重置棋子的位置并清除选中状态
            }
        }
        else if (chessSelected >= SEPARATION) // 对于备战区的棋子
        {
            auto crt = static_cast<Hero*>(myPlayerData.waitingArray->arr[chessSelected - SEPARATION]);//-1?
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[3][0].y + eachCell_y / 2) //  空气墙，限制在我方场上 chessMap的x是width，这里要用y
            {
                crt->setPosition(e->getCursorX(), e->getCursorY());
                crt->set(e->getCursorX(), e->getCursorY());  // 移动
            }
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // 重置棋子的位置并清除选中状态
            }
        }
    }
}

Point sceneGame::inWhichCell(const Point point) const
{
    for (int i = 0; i < CHESS_IN_A_COL + 2; i++)
    {
        for (int j = 0; j < CHESS_IN_A_ROW; j++)
        {
            if (sqrt((point.x - chessMap[i][j].x) * (point.x - chessMap[i][j].x)
                + (point.y - chessMap[i][j].y) * (point.y - chessMap[i][j].y)) < 80)
                return Point(chessMap[i][j].x, chessMap[i][j].y);
        }
    }
    return Point(-1, -1);
}

/**************计时器***************/
void sceneGame::update(float dt) // 实时更新
{
    if (afterFight->totalTime > 1e-6) //备战时间
    {
        heroExist->heroUpgrade(myPlayerData);
        heroExist->heroUpgrade(opPlayerData);
        //addHeroToWaiting(myPlayerData, 0);
        //addHeroToWaiting(opPlayerData, 1);
        AIPlayer.judgeGold();

    }
    addHeroToWaiting(myPlayerData, 0);
    addHeroToWaiting(opPlayerData, 1);
    mouseMainEvent();

    if (afterFight->totalTime < -1e-2) // 战斗时间
    {
        if (isAI)
        {
            AIPlayer.creatBattleArray();
            heroExist->aiShowBattleArray();  //显示电脑玩家信息
            heroExist->aiShowWaitingArray();
            if (opPlayerData.waitingArray->num == 8)
                soldHero(opPlayerData, AIPlayer.soldHero(), opPlayerData.waitingArray);   //电脑卖棋子
            isAI = 0;
        }
        mouseInit();   //取消对战斗区棋子的选取
        afterFight->setPosition(10000, 10000);
        heroExist->scheduleUpdate();
        if (!this->battleStarted)
        {
            startBattle();
            battleStarted = true; // 确保战斗只开始一次
        }
        win();
    }
}

/**************局面***************/

// 添加英雄到等待区
void sceneGame::addHeroToWaiting(playerData& player, int playerInfo)
{
    if (player.playerHaveNewHero)
    {
        bool haveAdded = false;
        auto selected = (static_cast<Hero*>(player.waitingArray->arr[player.waitingArray->num - 1]));
        if (playerInfo == 0)
        {
            for (int i = 0; i < CHESS_IN_A_ROW; i++)
            {
                if (haveChess[0][i] == 0)
                {
                    player.playerHaveNewHero = 0;
                    heroExist->addChild(selected);
                    //player.playerMoney -= selected->getPrice();
                    selected->setPosition(chessMap[0][i].x, chessMap[0][i].y);
                    selected->set(chessMap[0][i].x, chessMap[0][i].y);
                    selected->setTempPosition();
                    selected->retain();
                    selected->setPlayer(playerInfo);
                    player.heroNum[selected->getType()]++;
                    haveChess[0][i] = 1;
                    haveAdded = true;
                    break;
                }
            }
        }
        else
        {
            //player.playerMoney -= selected->getPrice();
            heroExist->addChild(selected);
            selected->setPosition(10000, 10000);
            selected->set(10000, 10000); // ?
            selected->setPlayer(playerInfo);
            player.heroNum[selected->getType()]++;
            player.playerHaveNewHero = 0;
            haveAdded = true;
        }
        if (!haveAdded)
        {
            ccArrayRemoveObject(player.waitingArray, selected);
            player.playerHaveNewHero = 0;
        }
    }
}

int sceneGame::endAlivePieces(const playerData& player) const
{
    int alive = 0;
    for (int i = 0; i < player.battleArray->num; i++)
    {
        auto crt = static_cast<Hero*>(player.battleArray->arr[i]);
        if (!crt->isDead())
        {
            alive++;
        }
    }
    return alive;
}

void sceneGame::win()
{
    int myAlivePieces = endAlivePieces(myPlayerData);
    int opAlivePieces = endAlivePieces(opPlayerData);

    if (!(myAlivePieces && opAlivePieces))
    {
        if (myAlivePieces == 0)
        {
            myPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * opAlivePieces);
        }
        else if (opAlivePieces == 0)
        {
            opPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * myAlivePieces);
        }
        afterWin(myPlayerData.waitingArray);
        afterWin(myPlayerData.battleArray);
        afterWin(opPlayerData.waitingArray);
        afterWin(opPlayerData.battleArray);
        /*********************************/
        // 添加音频
        heroExist->unscheduleUpdate();     
        /*********************************/

        myPlayerData.updateMoneyAndExp();
        opPlayerData.updateMoneyAndExp();
        battleStarted = false;
        if (myPlayerData.playerHealth > 0 && opPlayerData.playerHealth > 0) // 双方依然存活
        {
            _director->replaceScene(sceneGame::createScene(playerName));
        }
        else
        {
            string winner = myPlayerData.playerHealth > 0 ? playerName : "opPlayer";
            winner += " win!";
            auto label = Label::createWithTTF(winner, "fonts/Marker Felt.ttf", 36);
            this->addChild(label);
            label->setTextColor(Color4B::WHITE);
            label->setPosition(800, 400);
            auto move = FadeOut::create(5.0f);
            label->runAction(move);


            auto sprite2 = Sprite::create("vict.png");
            this->addChild(sprite2);
            sprite2->setPosition(800, 460);
            sprite2->setScale(2.0f);
            auto move2 = FadeOut::create(2.0f);
            sprite2->runAction(move2);


            this->unscheduleUpdate();

            myPlayerData.playerInit();
            opPlayerData.playerInit();

            for (int i = 0; i < CHESS_IN_A_COL + 2; i++)
            {
                for (int j = 0; j < CHESS_IN_A_ROW; j++)
                {
                    haveChess[i][j] = false;
                }
            }
            _director->replaceScene(TransitionFade::create(8.0f, mainMenu::createScene()));
        }
    }
}

void sceneGame::afterWin(ccArray* crtArray)
{
    for (int i = 0; i < crtArray->num; i++)
    {
        Hero* crt = static_cast<Hero*>(crtArray->arr[i]);

        crt->retain();
        /************释放/恢复******************/
        crt->removeFromParent();
        crt->recover();
    }
}

void sceneGame::soldHero(playerData& player, Hero* hero, ccArray* Array)
{
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    myPlayerData.playerMoney += hero->soldMoney;
    hero->retain();
    heroExist->removeChild(hero);
    ccArrayRemoveObject(Array, hero);
}

bool sceneGame::mouseInBattleArray(ccArray* Array, EventMouse* e)
{
    int temp = (Array == myPlayerData.waitingArray) ? SEPARATION : 0;
    // 战斗区从0开始，备战区从SEPARATION开始

    if (afterFight->totalTime > 0 || afterFight->totalTime <= 0 && temp == SEPARATION)// 确保在备战时间
    {
        for (int m = 0; m < Array->num; m++)
        {
            float distance = sqrt(
                (e->getCursorX() - (static_cast<Hero*>(Array->arr[m]))->getPosition().x)
                * (e->getCursorX() - (static_cast<Hero*>(Array->arr[m]))->getPosition().x) +
                (e->getCursorY() - (static_cast<Hero*>(Array->arr[m]))->getPosition().y)
                * (e->getCursorY() - (static_cast<Hero*>(Array->arr[m]))->getPosition().y));
            if (distance < CAN_BE_SELECTED)
            {
                if ((int)e->getMouseButton() == 0) // 左键
                {
                    chessSelected = m + temp;
                }
                else if ((int)e->getMouseButton() == 1 && afterFight->totalTime > 1e-2) // 右键，并且在备战时间，卖出棋子
                {
                    auto tempHero = static_cast<Hero*>(Array->arr[m]);
                    soldHero(myPlayerData, tempHero, Array);
                    return false;
                }
                (static_cast<Hero*>(Array->arr[m]))->setTempPosition();
                return false;
            }
        }
    }
    return true;
}

void sceneGame::toBattleArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //更改棋子存在情况
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.battleArray, hero);  //放入战斗区
    ccArrayRemoveObject(myPlayerData.waitingArray, hero);   //更新备战区
}

void sceneGame::toWaitingArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //更改棋子存在情况
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.waitingArray, hero);    //放入备战区
    ccArrayRemoveObject(myPlayerData.battleArray, hero);   //更新战斗区
}

sceneGame* sceneGame::createScene(string& userName)
{
    playerName = userName;
    return sceneGame::create();
}

string sceneGame::getUserName() const
{
    return playerName;
}

sceneGame::sceneGame()
{

}

sceneGame::~sceneGame()
{

}

void sceneGame::startBattle()
{
    // 遍历战斗区数组中的每个 Hero 对象并调用 play 函数
    for (int i = 0; i < myPlayerData.battleArray->num; i++)
    {
        auto hero = static_cast<Hero*>(myPlayerData.battleArray->arr[i]);
        hero->ofPlayer = HUMAN;
        hero->connection(myPlayerData);
        hero->Play(); 
    }
    for (int i = 0; i < opPlayerData.battleArray->num; i++)
    {
        auto hero = static_cast<Hero*>(opPlayerData.battleArray->arr[i]);
        hero->ofPlayer = AI;
        hero->Play();
    }
}
