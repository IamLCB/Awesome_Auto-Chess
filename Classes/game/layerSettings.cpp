#include "game/layerSettings.h"
#include "globalResSetting.h"

layerSettings* layerSettings::createLayer()
{
	auto settingsLayer = layerSettings::create();
	settingsLayer->retain();
	settingsLayer->autorelease();
	return settingsLayer;
}

bool layerSettings::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(0, 0);
	MenuItemImage* back = MenuItemImage::create("CloseNormal.png", "CloseSelected.png",
		CC_CALLBACK_1(layerSettings::onBack, this));
	Menu* menuBack = Menu::create(back, nullptr);
	menuBack->setPosition(Vec2(origin.x + visibleSize.width - 100, origin.y + visibleSize.height - 100));

	return true;
}

void layerSettings::onBack(cocos2d::Ref* pSender)
{
	myPlayerData.playerInit();
	opPlayerData.playerInit();
	_director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}