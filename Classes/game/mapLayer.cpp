#include"mapLayer.h"

Point chessMap[6][8];
bool haveChess[6][8] = { false };
const Point chessMap[1][7] = { Point(-1, -1) };
const Point chessMap[4][7] = { Point(-1, -1) };
const bool haveChess[1][7] = { false };
const bool haveChess[4][7] = { false };

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
    gameBackGround->setScale(visibleSize.width / gameBackGround->getContentSize().width, visibleSize.height / gameBackGround->getContentSize().height);

    this->addChild(gameBackGround);
    

    return true;

}

Pair pairReturn(Point point)
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((point.x - chessMap[i][j].x) * (point.x - chessMap[i][j].x) +
                (point.y - chessMap[i][j].y) * (point.y - chessMap[i][j].y) < EFF_RADIUS)
            {
                return Pair(i, j);
            }
        }
    }
    return Pair(-1, -1);
}

