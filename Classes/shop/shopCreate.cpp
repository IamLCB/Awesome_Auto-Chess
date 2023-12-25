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

	//create the three buttons, the shopcreator/the shopcloser/the shoprefresher
	shopCreatorButton->setTag(TAG_SCTBTN);
	shopCloserButton->setTag(TAG_SCLBTN);
	shopRefresherButton->setTag(TAG_SRFBTN);

	//the order of the buttons in the first time
	creatorOrder = INT_MAX;
	CaRBO = 1;

	//put the order
	this->addChild(shopCreatorButton, creatorOrder);
	this->addChild(shopCloserButton, CaRBO);
	this->addChild(shopRefresherButton, CaRBO);

	//create the background of shop
	auto backgroundShop = Sprite::create("backgroundofshop.png", Rect(0, 50, 0, 0));
	backgroundShop->setTag(TAG_BG_SHOP);

	//mouse pause
	MenuItemSprite* pauseButton = MenuItemSprite::create(shopCreatorButton, shopCreatorButton, 
		CC_CALLBACK_1(shopCreate::shopReflect, this));


}

//
void shopCreate::shopReflect(cocos2d::Ref* pSender)
{
    //change the order of the buttons
	creatorOrder = 1;
	CaRBO = INT_MAX;

	//put the order
	this->addChild(shopCreatorButton, creatorOrder);
	this->addChild(shopCloserButton, CaRBO);
	this->addChild(shopRefresherButton, CaRBO);
}