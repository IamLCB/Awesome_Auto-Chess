#ifndef _shopCreate_H_
#define _shopCreate_H_
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "cocos2d.h"
#include "globalResSetting.h"
#include "HelloworldScene.h"
#include "sceneAbout.h"

#define CENTER_BUTTON_X RIGHT_WIN_X - 150
#define CENTER_BUTTON_Y BOTTOM_WIN_Y + 100
#define BG_SHOP_X 100
#define BG_SHOP_Y 20
#define SIZE_SHOP_HERO_X 200
#define SIZE_SHOP_HERO_Y 250

//the tag of the three button(shopcreator/shopcloser/shoprefresher)
#define TAG_SCTBTN 73
#define TAG_SCLBTN 74
#define TAG_SRFBTN 75

//the tag of the background of shop
#define TAG_BG_SHOP 76

//the scale of the buttons
#define BT_SCALE 0.5f

//the scale of background
#define BG_SCALE 0.5f

class shopCreate : public cocos2d::Sprite
{
private:
	//define the order of the Sprite
	//the order of the buttons
	int creatorOrder;
	int CaRBO;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//define the buttons Sprite
	Sprite* shopCreatorButton = Sprite::create("shopcreator.png");
	Sprite* shopCloserButton = Sprite::create("shopcloser.png");
	Sprite* shopRefresherButton = Sprite::create("shoprefresher.png");

	//define the background of shop Sprite
	Sprite* shopBackground = Sprite::create("backgroundofshop.png");
public:
	static cocos2d::Sprite* createShop();

	virtual bool init();

	void shopReflect();

	void shopPieces(cocos2d::Ref* pSender);

	void shoprefresh();

	bool openShop(Touch* touch, Event* event);

	CREATE_FUNC(shopCreate);
};

#endif // !_shopCreate_H_