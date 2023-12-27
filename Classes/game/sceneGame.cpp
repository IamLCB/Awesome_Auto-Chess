#include "sceneGame.h"
USING_NS_CC;

string name;  // ����ǳ�

/**************��ʼ������*************/
bool sceneGame::init()
{
    if (!mainMenu::init())
    {
        return false;
    }

    // ��ʼ����Ϸ�߼�
    // ���磺���ñ�������ʼ��Ӣ�ۡ�����������ݵ�

    this->addChild(map, 0);

    this->addChild(playerLayer, 1);

     this->addChild(timer, 2); 

    this->addChild(heroLayer, 3);

    this->addChild(shopLayer, 4);

    this->addChild(settingsLayer, 5);

    //װ��
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

/**************������***************/

void sceneGame::mouseInit()
{
    //�ж�ʱ��
    if (chessSelected < maxHeroNum && chessSelected != -1)
    {
        auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
        crt->setPosition(inWhichCell(crt->getTempPosition()));
        crt->set(crt->getTempPosition());
        chessSelected = -1; // �������ӵ�λ�ò����ѡ��״̬
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
    if ((int)e->getMouseButton() == 0) // ���
    {
        if (equipmentSelected != -1)
        {
            if (EquipSearchChess(e->getCursorX(), e->getCursorY(), equipmentSelected))//װ������������������
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
    if ((int)e->getMouseButton() == 0) // �������
    {
        if (chessSelected >= 0 && chessSelected < maxHeroNum)
        {
            auto crt = ((Hero*)(myPlayerData.battleArray->arr[chessSelected]));
            if (haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] == 1)   // �����ظ�ѡ��
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));

            }
            else if (inWhichCell(crt->getPosition()).y != 0 && inWhichCell(crt->getPosition()).y != 9)   //�����ڵȺ���
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
            if (haveChess[inWhichCell(crt->getPosition()).x][inWhichCell(crt->getPosition()).y] == 1)   // �����ظ�ѡ��
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
            }
            else if (pairReturn(crt->getPosition()).y == 0 || pairReturn(crt->getPosition()).y == 9)  //���ڵȺ���
            {
                //Point temppoint = inWhichCell(temp->getPosition());
                crt->setPosition(inWhichCell(crt->getPosition()));
                crt->set(inWhichCell(crt->getPosition()));

                haveChess[pairReturn(crt->getPosition()).x][pairReturn(crt->getPosition()).y] = 1;
                haveChess[pairReturn(crt->getTempPosition()).x][pairReturn(crt->getTempPosition()).y] = 0;
                crt->setTempPosition();
            }
            else if ()//���ʱ������ ����ս����
            {
                if (myPlayerData.battleArray->num < myPlayerData.playerLevel)
                    toBattleArray(crt, myPlayerData);
                else
                {
                    crt->setPosition(inWhichCell(crt->getTempPosition()));
                    crt->set(inWhichCell(crt->getTempPosition()));
                    // ��Ӳ�����������ǩ��

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

    if (!toSelect) // ������ѡȡװ��ʱ��
    {
        for (int i = 0; i < myPlayerData.UnequipedEquipment->num; i++)
        {
            double dx = (e->getCursorX() - ((Equipment*)(myPlayerData.UnequipedEquipment->arr[i]))->getPosition().x);
            double dy = (e->getCursorY() - ((Equipment*)(myPlayerData.UnequipedEquipment->arr[i]))->getPosition().y);
            double distance = sqrt(dx * dx + dy * dy);
            if (distance < 20)
            {
                equipmentSelected = i;   //ȷ��ѡ�е�װ��
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
        if (chessSelected < maxHeroNum)// ��� ѡ�����ӵ�ʱ���Ƿ�������ʱ����
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            crt->setPosition(inWhichCell(crt->getTempPosition()));
            crt->set(inWhichCell(crt->getTempPosition()));
            chessSelected = -1; // ��ɲ��������ص�δѡ��״̬
            return;
        }
        else if (chessSelected < maxHeroNum) // �ȴ���
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected]);
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[0][4].y + height) //  ��ȷ��
                ;
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // ȡ��ѡ��
            }
        }
        else if (chessSelected >= maxHeroNum) // ս����
        {
            auto crt = static_cast<Hero*>(myPlayerData.battleArray->arr[chessSelected-maxHeroNum]);
            auto crtPosition = inWhichCell(crt->getPosition());
            if (crtPosition != Point(-1, -1) && crtPosition.y <= chessMap[0][4].y + height)  // ��ȷ��
                ;
            else
            {
                crt->setPosition(inWhichCell(crt->getTempPosition()));
                crt->set(inWhichCell(crt->getTempPosition()));
                chessSelected = -1; // ȡ��ѡ��
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
            if (q == 0)         // ���ڵȺ���
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
            else if (sqrt((point.x - chessMap[p][q].x) * (point.x - chessMap[p][q].x)    //������ͼ���ж��Ƿ��ڸ�����
                + (point.y - chessMap[p][q].y) * (point.y - chessMap[p][q].y)) < 37.5 * sqrt(2))
                return Point(chessMap[p][q].x, chessMap[p][q].y);
        }

    }
    return Point(-1, -1);
}

/**************��ʱ��***************/
/* ��ʱ+��ʼս�� */

/**************����***************/

// ���Ӣ�۵��ȴ���
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
                    player.heroNum[selected->getType()]++; // ��������
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
        // ��Ƶ
        heroExist->unscheduleUpdate();
        myPlayerData.recover();
        opPlayerData.recover();
        // װ������

        if (myPlayerData.playerHealth > 0 && opPlayerData.playerHealth > 0) // ˫����Ȼ���
        {
            _director->replaceScene(sceneGame::createScene(name));
        }
        else
        {
            string winner = myPlayerData.playerHealth > 0 ? "You" : "Opponent";
            // ��ʾʤ��ͼ��
            // ��ʱ����
            // װ���ع�

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

    if ()// ʱ�����
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
                if ((int)e->getMouseButton() == 0) // ���
                {
                    chessSelected = m + temp;
                }
                else if ((int)e->getMouseButton() == 1 ) // �Ҽ�����������ʱ��
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

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //�������Ӵ������
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.waitingArray, hero);  //����ȴ���
    ccArrayRemoveObject(myPlayerData.battleArray, hero);   //����ս����
}

void sceneGame::toWaitingArray(Hero* hero, playerData& player)
{
    hero->setPosition(inWhichCell(hero->getPosition()));
    hero->set(inWhichCell(hero->getPosition()));

    haveChess[pairReturn(hero->getPosition()).x][pairReturn(hero->getPosition()).y] = 1;      //�������Ӵ������
    haveChess[pairReturn(hero->getTempPosition()).x][pairReturn(hero->getTempPosition()).y] = 0;
    hero->setTempPosition();
    ccArrayAppendObject(myPlayerData.battleArray, hero);    //����ս����
    ccArrayRemoveObject(myPlayerData.waitingArray, hero);   //���µȴ���
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
        Vec2 p = convertTouchToNodeSpace(t); // ��ȡ����λ��

        // ����Ƿ�����Ӣ�۲��е�Ӣ��
        for (Hero* hero : heroSlots) {
            if (isClickOnHeroSlot(p, hero)) {
                selectedHero = hero; // ѡ��Ӣ��
                highlightHeroSlot(hero); // ������ʾѡ�е�Ӣ�۲�
                return true;
            }
        }

        // �����ѡ��Ӣ�ۣ�����Ƿ����������ϵĿո�
        if (selectedHero) {
            int x, y;
            if (getBoardPosition(p, x, y) && board[y][x] == nullptr) {
                moveHeroToBoard(selectedHero, x, y); // �ƶ�Ӣ�۵�����
                unHighlightHeroSlot(selectedHero); // ȡ��������ʾ
                selectedHero = nullptr; // ȡ��ѡ��Ӣ��
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
    Vec2(enemyCampUpperLeftWidth,enemyCampUpperLeftHeight),  // ���Ͻ�
    Vec2(enemyCampUpperRightWidth,enemyCampUpperRightHeight), // ���Ͻ�
    Vec2(enemyCampLowerRightWidth,enemyCampLowerRightHeight), // ���½�
    Vec2(enemyCampLowerLeftWidth,enemyCampLowerLeftHeight) // ���½�
};
Color4F black(0.0f, 0.0f, 0.0f, 1.0f); // ��ɫ
enemyCamp->drawPolygon(upperRect, 4, black, 0, black);
this->addChild(enemyCamp);

// �����°벿�־��Σ������Ϊ��ɫ

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
    Vec2(myCampUpperLeftWidth,myCampUpperLeftHeight), // ���Ͻ�
    Vec2(myCampUpperRightWidth,myCampUpperRightHeight), // ���Ͻ�
    Vec2(myCampLowerRightWidth,myCampLowerRightHeight), // ���½�
    Vec2(myCampLowerLeftWidth,myCampLowerLeftHeight) // ���½�
};
Color4F white(1.0f, 1.0f, 1.0f, 1.0f); // ��ɫ
myCamp->drawPolygon(lowerRect, 4, white, 0, white);
this->addChild(myCamp);

// ���ָ��Ӳ���ʾ������
float cellWidth = (myCampLowerRightWidth - myCampLowerLeftWidth) / 8;  // ÿ��8������
float cellHeight = (myCampUpperLeftHeight - myCampLowerLeftHeight) / 4;  // 4�и���

for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 8; ++j) {
        DrawNode* cellDrawNode = DrawNode::create();
        Vec2 points[4] = {
            Vec2(j * cellWidth, i * cellHeight), // ���Ͻ�
            Vec2((j + 1) * cellWidth, i * cellHeight), // ���Ͻ�
            Vec2((j + 1) * cellWidth, (i + 1) * cellHeight), // ���½�
            Vec2(j * cellWidth, (i + 1) * cellHeight) // ���½�
        };
        Color4F outlineColor(1.0f, 0.0f, 0.0f, 1.0f); // ��ɫ
        cellDrawNode->drawPolygon(points, 4, Color4F::WHITE, 1, outlineColor);
        this->addChild(cellDrawNode);
    }
}
return true;
*/


