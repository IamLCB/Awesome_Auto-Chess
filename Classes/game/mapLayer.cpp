#include"game/mapLayer.h"

Point chessMap[CHESS_IN_A_COL + 2][CHESS_IN_A_ROW];
bool haveChess[CHESS_IN_A_COL + 2][CHESS_IN_A_ROW] = { false };

mapLayer* mapLayer::createMapLayer()
{
    auto temp = mapLayer::create();
    temp->retain();
    return temp;
}

bool mapLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto gameBackGround = Sprite::create("./game/gameBackground.png");

    gameBackGround->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    gameBackGround->setScale(visibleSize.width / gameBackGround->getContentSize().width,
        visibleSize.height / gameBackGround->getContentSize().height);

    this->addChild(gameBackGround);


    return true;

}

Pair pairReturn(Point point)
{
    for (int i = 0; i < CHESS_IN_A_COL + 2; i++)
    {
        for (int j = 0; j < CHESS_IN_A_ROW; j++)
        {
            if (((point.x - chessMap[i][j].x) * (point.x - chessMap[i][j].x) +
                (point.y - chessMap[i][j].y) * (point.y - chessMap[i][j].y)) < EFF_RADIUS * EFF_RADIUS)
            {
                return Pair(i, j);
            }
        }
    }
    return Pair(-1, -1);
}

