#include "shopCreate.h"

USING_NS_CC;

Sprite* shopCreate::createShop() 
{
	return shopCreate::create();
}

//on "init" you need to initialize your instance
bool shopCreate::init()
{
	// 1. 
	if (!Sprite::init())
	{
		return false;
	}


	auto menuLayer = Layer::create();
	menuLayer->setPosition(Vec2::ZERO);
	this->addChild(menuLayer, 1);

	//tag the three buttons, the shopcreator/the shopcloser/the shoprefresher
	shopCreatorButton->setTag(TAG_SCTBTN);
	shopCloserButton->setTag(TAG_SCLBTN);
	shopRefresherButton->setTag(TAG_SRFBTN);

	//tag the background of shop
	shopBackground->setTag(TAG_BG_SHOP);

	//set the position of the buttons
	shopCreatorButton->setPosition(Vec2(CENTER_BUTTON_X, CENTER_BUTTON_Y));
	shopCloserButton->setPosition(Vec2(CENTER_BUTTON_X, CENTER_BUTTON_Y));
	shopRefresherButton->setPosition(Vec2(CENTER_BUTTON_X, CENTER_BUTTON_Y - 150));

	//set the position of the background
	shopBackground->setPosition(Vec2(100, 20));

	//define the size of the shop about
	shopCreatorButton->setScale(BT_SCALE);
	shopCloserButton->setScale(BT_SCALE);
	shopRefresherButton->setScale(BT_SCALE);
	shopBackground->setScale(BG_SCALE);

	//the order of the buttons in the first time
	creatorOrder = INT_MAX;
	CaRBO = 1;

	//put the order
	this->addChild(shopCreatorButton, INT_MAX);
	this->addChild(shopCloserButton, 1);
	this->addChild(shopRefresherButton, 1);
	this->addChild(shopBackground, 1);

	//===================mouse pause to open the shop==========================
	
		//===================mouse pause to close the shop=========================

}

//if the shopCreatorButton has been touched
bool shopCreate::openShop(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode))
	{
		//some controls
		shopReflect();
		shoprefresh();
	}
}

//open the shop
void shopCreate::shopReflect()
{
	//put the order
	shopCreatorButton->setLocalZOrder(1);
	shopCloserButton->setLocalZOrder(INT_MAX);
	shopRefresherButton->setLocalZOrder(INT_MAX);
	shopBackground->setLocalZOrder(INT_MAX - 1);
}

//to refresh the shop
void shopCreate::shoprefresh() 
{
	int rands[5] = { 0 };
	srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		rands[i] = rand() % 8;
	}
}