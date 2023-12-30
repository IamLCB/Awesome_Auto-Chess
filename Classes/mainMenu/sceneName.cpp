#include "cocos2d.h"
#include "AppDelegate.h"
#include "mainMenu.h"
#include "globalResSetting.h"
#include "sceneName.h"
#include "game/sceneGame.h"

USING_NS_CC;
using namespace cocos2d::ui;

typedef std::string string;

string playerName;

Scene* sceneName::createScene()
{
	return sceneName::create();
}

bool sceneName::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/**************Background****************/
	auto bg = Sprite::create("./mainMenu/aboutBG.jpg");
	bg->setPosition(800, 460);
	this->addChild(bg);

	/**************Label Name***************/
	auto label2 = Label::createWithTTF("Login", "fonts/betterFont.ttf", 48);
	if (label2 == nullptr)
	{
		problemLoading("'fonts/betterFont.ttf'");
	}
	else
	{
		label2->setPosition(Vec2(CENTER_WIN_X, TOP_WIN_Y - label2->getContentSize().height));
		label2->setColor(Color3B::BLACK);
		this->addChild(label2, 1);
	}

	/**************Label UserName***************/
	auto label = Label::createWithTTF("Please Enter Your Name", "fonts/betterFont.ttf", 48);
	if(label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		label->setPosition(Vec2(CENTER_WIN_X, CENTER_WIN_Y + label->getContentSize().height + 20));
		label->setColor(Color3B::BLACK);
		this->addChild(label, 1);
	}



	/**************EditBox UserName***************/
	auto nameEditBox = EditBox::create(Size(300, 60), Scale9Sprite::create("./mainMenu/nameEditBox.png"));

	nameEditBox->setAnchorPoint(Point(0, 0));
	nameEditBox->setPosition(Vec2(CENTER_WIN_X - nameEditBox->getContentSize().width / 2, CENTER_WIN_Y - nameEditBox->getContentSize().height / 2));
	nameEditBox->setFontColor(Color3B::BLACK);
	nameEditBox->setDelegate(this);
	nameEditBox->setMaxLength(100);
	nameEditBox->setPlaceHolder("Enter Your Username");
	nameEditBox->setPlaceholderFontColor(Color3B::GRAY);
	nameEditBox->setPlaceholderFontSize(30);
	nameEditBox->setFontSize(30);
	nameEditBox->setTag(1);
	this->addChild(nameEditBox, 1);

	/**************Button Return***************/
	 /*----------------MenuItemSprite aboutBack---------------------*/
	Sprite* aboutBackNormal = Sprite::create("./mainMenu/backToMenuNormal.png");
	Sprite* aboutBackSelected = Sprite::create("./mainMenu/backToMenuSelected.png");

	MenuItemSprite* aboutBack = MenuItemSprite::create(aboutBackNormal, aboutBackSelected,
		CC_CALLBACK_1(sceneName::returnToMenu, this));

	if (aboutBack == nullptr ||
		aboutBack->getContentSize().width <= 0 ||
		aboutBack->getContentSize().height <= 0)
	{
		problemLoading("'backToMenuNormal.png' and 'backToMenuSelected.png'");
	}
	else
	{
		float x = CENTER_WIN_X;
		float y = BOTTOM_WIN_Y + aboutBack->getContentSize().height / 2 + 5;
		aboutBack->setPosition(Vec2(x, y));
	}

	auto menuAboutBack = Menu::create(aboutBack, nullptr);
	menuAboutBack->setPosition(Vec2::ZERO);
	this->addChild(menuAboutBack, 1);

	/**************Button AI***************/
	Sprite* aiNormal = Sprite::create("./mainMenu/modeAiNormal.png");
	Sprite* aiSelected = Sprite::create("./mainMenu/modeAiSelected.png");

	MenuItemSprite* aiMode = MenuItemSprite::create(aiNormal, aiSelected,
		CC_CALLBACK_1(sceneName::modeAI, this));

	if (aiMode == nullptr ||
		aiMode->getContentSize().width <= 0 ||
		aiMode->getContentSize().height <= 0)
	{
		problemLoading("'modeAiNormal.png' and 'modeAiSelected.png'");
	}
	else
	{
		aiMode->setPosition(CENTER_WIN_X, CENTER_WIN_Y - aiMode->getContentSize().height-150);
	}

	auto menuaiMode = Menu::create(aiMode, nullptr);
	menuaiMode->setPosition(Vec2::ZERO);
	this->addChild(menuaiMode, 1);
	/**************Label Mode***************/
	auto mode = Label::createWithTTF("Mode:", "fonts/betterFont.ttf", 48);
	if (mode == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		mode->setPosition(CENTER_WIN_X, aiMode->getPosition().y + mode->getContentSize().height + 20);
		mode->setColor(Color3B::BLACK);
		this->addChild(mode, 1);
	}

	return true;
}

void sceneName::editBoxEditingDidBegin(EditBox* editBox)
{
	CCLOG("editBox %p DidBegin !", editBox);
}

void sceneName::editBoxEditingDidEnd(EditBox* editBox)
{
	CCLOG("editBox %p DidEnd !", editBox);
}

void sceneName::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	CCLOG("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void sceneName::editBoxReturn(EditBox* editBox)
{
	CCLOG("editBox %p was returned !", editBox);
	playerName = editBox->getText();
}

void sceneName::returnToMenu(Ref* pSender)
{
	_director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}

void sceneName::modeAI(Ref* pSender) {
	globalGameData->initGameStart();
	_director->pushScene(TransitionFade::create(1.0f, sceneGame::createScene(playerName)));
}