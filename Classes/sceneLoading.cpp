#include "sceneLoading.h"
#include "mainMenu/mainMenu.h"
#include "globalResSetting.h"

sceneLoading* sceneLoading::createScene()
{
	return sceneLoading::create();
}

bool sceneLoading::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	totalResources = 5;
	loadedResources = 0;

	/**************MenuBackground**************/
	Sprite* bg = Sprite::create("sceneLoading.png");
	if (bg == nullptr)
	{
		problemLoading("sceneLoading.png");
	}
	else
	{
		bg->setPosition(CENTER_WIN);
		bg->setScale(BG_SCALE);
		this->addChild(bg, 0);
	}

	loadingBar = ProgressTimer::create(Sprite::create("loadingBar.png"));
	loadingBar->setScaleX(2.0);
	loadingBar->setType(ProgressTimer::Type::BAR);
	loadingBar->setMidpoint(Vec2(0, 0));
	loadingBar->setBarChangeRate(Vec2(1, 0));
	loadingBar->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	loadingBar->setPercentage(0);
	this->addChild(loadingBar, 1);

	loadResources();

	return true;

}

void sceneLoading::loadResources()
{
	Director::getInstance()->getTextureCache()->addImageAsync("./mainMenu/mainMenuBackground.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./mainMenu/aboutBG.jpg", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./gameScene/gameBackground.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./player/avatar1.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./player/avatar2.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("./hero/bqzs.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/ltzz.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/mlps.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/qxsq.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/snzx.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/tfns.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/wlshz.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/yn.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("./hero/bomb.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/lightning.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("./hero/dizzy.png", CC_CALLBACK_1(sceneLoading::loadingCallBack, this));
}

void sceneLoading::loadingCallBack(Texture2D* texture)
{
	loadedResources++;
	loadingBar->setPercentage((float)loadedResources * 100 / totalResources);
	if (loadedResources == totalResources)
	{
		_director->pushScene(TransitionFade::create(2.0f, mainMenu::createScene()));
	}
}