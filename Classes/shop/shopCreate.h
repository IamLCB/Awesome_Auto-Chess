#ifndef _shopCreate_H_
#define _shopCreate_H_
#include "cocos2d.h"
#include "globalResSetting.h"
#include "HelloworldScene.h"
#include "sceneAbout.h"
#include "sceneSetting.h"
#include "sceneGame.h"
#include "mainMenu.h"

#define CENTER_BUTTON_X CENTER_WIN_X + 450
#define CENTER_BUTTON_Y CENTER_WIN_Y + 200

//the tag of the three button(shopcreator/shopcloser/shoprefresher)
#define TAG_SCTBTN 73
#define TAG_SCLBTN 74
#define TAG_SRFBTN 75

//the tag of the background of shop
#define TAG_BG_SHOP 76

class shopCreate : public cocos2d::Sprite
{
private:
	//define the order of the Sprite
	//the order of the buttons
	int creatorOrder;
	int CaRBO;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* shopCreatorButton = Sprite::create("shopcreator.png", Rect(CENTER_BUTTON_X, CENTER_BUTTON_Y, 0, 0));
	Sprite* shopCloserButton = Sprite::create("shopcloser.png", Rect(CENTER_BUTTON_X, CENTER_BUTTON_Y, 0, 0));
	Sprite* shopRefresherButton = Sprite::create("shoprefresher.png", Rect(CENTER_BUTTON_X, CENTER_BUTTON_Y - 250, 0, 0));

public:
	static cocos2d::Sprite* createShop();

	virtual bool init();

	void shopReflect(cocos2d::Ref* pSender);

	CREATE_FUNC(shopCreate);
};

#endif // !_shopCreate_H_