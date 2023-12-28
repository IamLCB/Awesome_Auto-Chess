#include "cocos2d.h"
#include "AppDelegate.h"
#include "mainMenu.h"
#include "globalResSetting.h"
#include "sceneName.h"

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

	/**************Label UserName***************/
	auto label = Label::createWithTTF("Please Enter Your Name", "fonts/Marker Felt.ttf", 48);
	if(label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		label->setPosition(Vec2(CENTER_WIN_X, CENTER_WIN_Y - label->getContentSize().height));
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
	playerName = text;
}

void sceneName::editBoxReturn(EditBox* editBox)
{
	CCLOG("editBox %p was returned !", editBox);
}