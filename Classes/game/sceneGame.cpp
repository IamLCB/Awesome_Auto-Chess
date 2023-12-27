#include "sceneGame.h"
USING_NS_CC;

string name;  // 玩家昵称

/**************初始化函数*************/
bool sceneGame::init()
{
    if (!mainMenu::init())
    {
        return false;
    }

    // 初始化游戏逻辑
    // 例如：设置背景、初始化英雄、设置玩家数据等

    this->addChild(map, 0);

    this->addChild(playerLayer, 1);

     this->addChild(timer, 2); 

    this->addChild(heroLayer, 3);

    this->addChild(shopLayer, 4);

    this->addChild(settingsLayer, 5);

    //装备
    //layerPackage->setPosition(0, 0);
    //this->addChild(layerPackage, 6);

    this->scheduleUpdate();

    map->scheduleUpdate();
    playerLayer->scheduleUpdate();

    playerLayer->scheduleUpdate();
    heroLayer->scheduleUpdate();

    return true;
}

void mapInit()
{

    // init chessMap[i][j] coordinate
}

/**************鼠标操作***************/

void sceneGame::mouseInit()
{
    //判断时间
    if (chessSelected < maxHeroNum && chessSelected != -1)
    {
        auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
        crt->setPosition(inWhichCell(crt->getTempPosition()));
        crt->set(crt->getTempPosition());
        chessSelected = -1; // 重置棋子的位置并清除选中状态
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
        if (equipmentSelected != -1)
        {
            if (EquipSearchChess(e->getCursorX(), e->getCursorY(), equipmentSelected))//装备搜索到附近的棋子
            {
                myPlayerData.equippedNum--;
            }
            else  
            {
                ((Equipment*)(myPlayerData.UnequipedEquipment->arr[equipmentSelected]))->setPosition(myPlayerData.slotPoint[equipmentSelected]);
            }
            equipmentSelected = -1;
        }
    }
    if ((int)e->getMouseButton() == 0) // 还是左键
    {
        if (chessSelected >= 0 && chessSelected < maxHeroNum)
        {
            auto crt = ((Hero*)(myPlayerData.battleArray->arr[chessSelected]));
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // 避免重复选择
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));

            }
            else if (inWhichCell(crt->getPosition()).y != 0 && inWhichCell(crt->getPosition()).y != 9)   //若不在等候区
            {

                //Point crtpoint = inWhichCell(crt->getPosition());
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));
                haveChess[inWhichCell(crt->getPosition()).x][inWhichCell(crt->getPosition()).y] = 1;
                haveChess[inWhichCell(crt->getTempPosition()).x][inWhichCell(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else    
            {
                toWaitingArray(crt, myPlayerData);
            }
        }
        else if (chessSelected >= maxHeroNum)
        {
            auto crt = ((Hero*)(myPlayerData.battleArray->arr[chessSelected - maxHeroNum]));
            if (haveChess[inWhichCell(crt->getPosition()).x][inWhichCell(crt->getPosition()).y] == 1)   // 避免重复选择
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
            else if (pairReturn(crt->getPosition()).y == 0 || pairReturn(crt->getPosition()).y == 9)  //若在等候区
            {
                //Point temppoint = inWhichCell(temp->getPosition());
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));

                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else if ()//添加时间限制 进入战斗区
            {
                if (myPlayerData.battleArray->num < myPlayerData.playerLevel)
                    toBattleArray(crt, myPlayerData);
                else
                {
                    crt->setPosition(inWhichCell(crt->getTempPosition()));
                    crt->set(inWhichCell(crt->getTempPosition()));
                    // 添加不够升级（标签）

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

    bool toSelect = false;

    if (!toSelect) // 并且在选取装备时间
    {
        for (int i = 0; i < myPlayerData.UnequipedEquipment->num; i++)
        {
            double dx = (e->getCursorX() - ((Equipment*)(myPlayerData.UnequipedEquipment->arr[i]))->getPosition().x);
            double dy = (e->getCursorY() - ((Equipment*)(myPlayerData.UnequipedEquipment->arr[i]))->getPosition().y);
            double distance = sqrt(dx * dx + dy * dy);
            if (distance < 20)
            {
                equipmentSelected = i;   //确定选中的装备
                toSelect = true;
            }
        }
    }

    if (!toSelect) 
    {
        if (mouseInBattleArray(myPlayerData.battleArray, e) == 1);
        else
            mouseInBattleArray(myPlayerData.waitingArray, e);
    }
}

void sceneGame::mouseMove(Event* event)
{
    auto e = static_cast<EventMouse*>(event);
    
    if (chessSelected != -1)
    {
        if (chessSelected < maxHeroNum)// 添加 选中棋子的时间是否在限制时间内
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(inWhichCell(crt->getTempPosition()));
            chessSelected = -1; // 完成操作，鼠标回到未选中状态
            return;
        }
        else if (chessSelected < maxHeroNum) // 等待区
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[0][4].y + height) //  待确定
                ;
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // 取消选中
            }
        }
        else if (chessSelected >= maxHeroNum) // 战斗区
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected-maxHeroNum]);
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[0][4].y + height)  // 待确定
                ;
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // 取消选中
            }
        }
    }
}

Point sceneGame::inWhichCell(Point point)
{
    for (int p= 0; p < 8; p++)
    {
        for (int q = 0; q < 10; q++)
        {
            if (q == 0)         // 对于等候区
            {
                if (point.y >= 50 && point.y <= 150 &&
                    point.x >= chessMap[p][0].x - 37.5 && point.x <= chessMap[p][0].x + 37.5)
                    return Point(chessMap[p][q].x, chessMap[p][q].y);
            }
            else if (q== 9)
            {
                if (point.y >= 750 && point.y <= 850 &&
                    point.x >= chessMap[p][9].x - 37.5 && point.x <= chessMap[p][9].x + 37.5)
                    return Point(chessMap[p][q].x, chessMap[p][q].y);
            }
            else if (sqrt((point.x - chessMap[p][q].x) * (point.x - chessMap[p][q].x)    //遍历地图，判断是否在格子内
                + (point.y - chessMap[p][q].y) * (point.y - chessMap[p][q].y)) < 37.5 * sqrt(2))
                return Point(chessMap[p][q].x, chessMap[p][q].y);
        }

    }
    return Point(-1, -1);
}

/**************计时器***************/
/* 计时+开始战斗 */

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
            for (int i = 0; i < 8; i++)
            {
                if (haveChess[i][0 + 9 * playerInfo] == 0)
                {
                    player.playerHaveNewHero = 0;
                    heroExist->addchild(selected);
                    player.playerMoney -= selected->getPrice();
                    selected->setPosition(chessMap[i][0 + 9 * playerInfo].x, chessMap[i][0 + 9 * playerInfo].y);
                    selected->set(chessMap[i][0 + 9 * playerInfo].x, chessMap[i][0 + 9 * playerInfo].y);
                    selected->setTempPosition();
                    selected->retain();
                    selected->setPlayer(playerInfo);
                    player.heroNum[selected->getType()]++; // 棋子升级
                    haveChess[i][0 + 9 * playerInfo] = 1;
                    haveAdded = true;
                    break;
                }
            }
        }
        else
        {
            player.playerMoney -= selected->getPrice();
            heroExist->addChild(selected);
            selected->setPosition(10000, 10000);
            selected->set(10000, 10000);
            selected->setPlayer(playerInfo);
            player.heroNum[selected->getResourceType()]++;
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
int sceneGame::endAlivePieces(playerData& player)
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
}

void sceneGame::win()
{
    int myAlivePieces = endAlivePieces(myPlayerData);
    int opAlivePieces = endAlivePieces(opPlayerData);

    if (!(myAlivePieces && opAlivePieces))
    {
        if (myAlivePieces == 0)
        {
            opPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * opAlivePieces);
        }
        else if (opAlivePieces == 0)
        {
            myPlayerData.playerHurt(BASICAL_HURT + EACH_CHESS_HURT * myAlivePieces);
        }
        afterWin(myPlayerData.waitingArray);
        afterWin(myPlayerData.battleArray);
        afterWin(opPlayerData.waitingArray);
        afterWin(opPlayerData.battleArray);
        // 音频
        heroExist->unscheduleUpdate();
        myPlayerData.recover();
        opPlayerData.recover();
        // 装备回收

        if (myPlayerData.playerHealth > 0 && opPlayerData.playerHealth > 0) // 双方依然存活
        {
            _director->replaceScene(sceneGame::createScene(name));
        }
        else
        {
            string winner = myPlayerData.playerHealth > 0 ? "You" : "Opponent";
            // 显示胜利图标
            // 计时结束
            // 装备回归

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 10; j++)
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
        crt->removeFromParent();
        crt->recover();
    }
}

void sceneGame::soldHero(playerData& player, Hero* hero, ccArray* Array) 
{
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    myPlayerData.playerMoney += hero->soldMoney;
    ccArrayAppendArray(player.UnequipedEquipment, hero->equipment);
    hero->retain();
    heroExist->removeChild(hero);
    ccArrayRemoveObject(Array, hero);
}

bool sceneGame::mouseInBattleArray(ccArray* Array, EventMouse* e)
{
    int temp = (Array == myPlayerData.battleArray) ? maxHeroNum : 0;

    if ()// 时间合理
    {
        for (int m = 0;m < Array->num; m++)
        {
            double distance = sqrt((e->getCursorX() -
                ((Hero*)(Array->arr[m]))->getPosition().x)
                * (e->getCursorX() - ((Hero*)(Array->arr[m]))->getPosition().x) +
                (e->getCursorY() - ((Hero*)(Array->arr[m]))->getPosition().y)
                * (e->getCursorY() - ((Hero*)(Array->arr[m]))->getPosition().y));
            if (distance < CAN_BE_SELECTED)
            {
                if ((int)e->getMouseButton() == 0) // 左键
                {
                    chessSelected = m + temp;
                }
                else if ((int)e->getMouseButton() == 1 ) // 右键，并且满足时长
                {
                    auto tempHero = static_cast<Hero*>(Array->arr[m]);
                    soldHero(myPlayerData,tempHero, Array);
                    return false;
                }
                ((Hero*)(Array->arr[m]))->setTempPosition();  
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
    ccArrayAppendObject(myPlayerData.waitingArray, hero);  //放入等待区
    ccArrayRemoveObject(myPlayerData.battleArray, hero);   //更新战斗区
}

void sceneGame::toWaitingArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //更改棋子存在情况
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.battleArray, hero);    //放入战斗区
    ccArrayRemoveObject(myPlayerData.waitingArray, hero);   //更新等待区
}

sceneGame* sceneGame::createScene(string& userName)
{
    name = userName;
    return sceneGame::create();
}

string sceneGame::getUserName()
{
    return name;
}

sceneGame::sceneGame()
{

}

sceneGame::~sceneGame()
{

}

/* // initial background
void sceneGame::initBackground()
{
    size = Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // initial chessboard
    board = Node::create();
    board->setPosition(Vec2(size.width / 2, size.height / 2));
    this->addChild(board);

    auto boardSprite = Sprite::create("./game/gameBackground.png");
    boardSprite->setPosition(Vec2(size.width / 2, size.height / 2));
    boardSprite->setScale(0.5);
    this->addChild(boardSprite, -1); // background of the board node

    // initial chess pieces
    for (int i = 0; i < CHESS_IN_A_ROW; i++)
    {
        for (int j = 0; j < CHESS_IN_A_COL; j++)
        {
            board[i][j] = NO_CHESS;
        }
    }

    // my chess selected 
    selected[0] = Sprite::create("./game/my chess selected.png");
    selected[0]->setVisible(false);
    board->addChild(selected[0]);

    // enemy chess selected
    selected[1] = Sprite::create("./game/enemy chess selected2.png");
    selected[1]->setVisible(false);
    board->addChild(selected[1]);

    // add "back to start""beck to menu" or other buttons
}


// initial Listener
void sceneGame::initListener()
{
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [&](Touch* t, Event* e) {
        Vec2 p = convertTouchToNodeSpace(t); // 获取触摸位置

        // 检查是否点击了英雄槽中的英雄
        for (Hero* hero : heroSlots) {
            if (isClickOnHeroSlot(p, hero)) {
                selectedHero = hero; // 选中英雄
                highlightHeroSlot(hero); // 高亮显示选中的英雄槽
                return true;
            }
        }

        // 如果已选中英雄，检查是否点击了棋盘上的空格
        if (selectedHero) {
            int x, y;
            if (getBoardPosition(p, x, y) && board[y][x] == nullptr) {
                moveHeroToBoard(selectedHero, x, y); // 移动英雄到棋盘
                unHighlightHeroSlot(selectedHero); // 取消高亮显示
                selectedHero = nullptr; // 取消选中英雄
            }
        }

        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}*/

/* void sceneGame::gameBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}

*/

/*
if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


auto gameBackGround = Sprite::create("./game/gameBackground.png");

gameBackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
gameBackGround->setScale(visibleSize.width / gameBackGround->getContentSize().width, visibleSize.height / gameBackGround->getContentSize().height);

this->addChild(gameBackGround);

// Split the rectangle into upper and lower parts

float enemyCampUpperLeftWidth = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION;
float enemyCampUpperLeftHeight = visibleSize.height * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT * 2;

float enemyCampUpperRightWidth = visibleSize.width * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_WIDTH;
float enemyCampUpperRightHeight = visibleSize.height * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT * 2;

float enemyCampLowerRightWidth = visibleSize.width * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_WIDTH;
float enemyCampLowerRightHeight = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT;

float enemyCampLowerLeftWidth = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION;
float enemyCampLowerLeftHeight = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT;

auto enemyCamp = DrawNode::create();
Vec2 upperRect[4] = {
    Vec2(enemyCampUpperLeftWidth,enemyCampUpperLeftHeight),  // 左上角
    Vec2(enemyCampUpperRightWidth,enemyCampUpperRightHeight), // 右上角
    Vec2(enemyCampLowerRightWidth,enemyCampLowerRightHeight), // 右下角
    Vec2(enemyCampLowerLeftWidth,enemyCampLowerLeftHeight) // 左下角
};
Color4F black(0.0f, 0.0f, 0.0f, 1.0f); // 黑色
enemyCamp->drawPolygon(upperRect, 4, black, 0, black);
this->addChild(enemyCamp);

// 创建下半部分矩形，并填充为白色

float myCampUpperLeftWidth = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION;
float myCampUpperLeftHeight = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT;

float myCampUpperRightWidth = visibleSize.width * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_WIDTH;
float myCampUpperRightHeight = visibleSize.height / 2 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_HEIGHT;

float myCampLowerRightWidth = visibleSize.width * 3 / 4 - SPATIAL_DEVIATION_CORRECTION + SPATIAL_DEVIATION_CORRECTION_WIDTH;
float myCampLowerRightHeight = visibleSize.height / 4 - SPATIAL_DEVIATION_CORRECTION;

float myCampLowerLeftWidth = visibleSize.width / 4 - SPATIAL_DEVIATION_CORRECTION;
float myCampLowerLeftHeight = visibleSize.height / 4 - SPATIAL_DEVIATION_CORRECTION;

auto myCamp = DrawNode::create();

Vec2 lowerRect[4] = {
    Vec2(myCampUpperLeftWidth,myCampUpperLeftHeight), // 左上角
    Vec2(myCampUpperRightWidth,myCampUpperRightHeight), // 右上角
    Vec2(myCampLowerRightWidth,myCampLowerRightHeight), // 右下角
    Vec2(myCampLowerLeftWidth,myCampLowerLeftHeight) // 左下角
};
Color4F white(1.0f, 1.0f, 1.0f, 1.0f); // 白色
myCamp->drawPolygon(lowerRect, 4, white, 0, white);
this->addChild(myCamp);

// 划分格子并显示轮廓线
float cellWidth = (myCampLowerRightWidth - myCampLowerLeftWidth) / 8;  // 每行8个格子
float cellHeight = (myCampUpperLeftHeight - myCampLowerLeftHeight) / 4;  // 4行格子

for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 8; ++j) {
        DrawNode* cellDrawNode = DrawNode::create();
        Vec2 points[4] = {
            Vec2(j * cellWidth, i * cellHeight), // 左上角
            Vec2((j + 1) * cellWidth, i * cellHeight), // 右上角
            Vec2((j + 1) * cellWidth, (i + 1) * cellHeight), // 右下角
            Vec2(j * cellWidth, (i + 1) * cellHeight) // 左下角
        };
        Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f); // 红色
        cellDrawNode->drawPolygon(points, 4, Color4F::WHITE, 1, outlineColor);
        this->addChild(cellDrawNode);
    }
}
return true;
*/


