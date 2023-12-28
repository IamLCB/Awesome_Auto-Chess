#include "sceneAbout.h"
#include "mainMenu.h"
#include "globalResSetting.h"
#include "inGameTimer/inGameTimer.h"

USING_NS_CC;

Scene* sceneAbout::createScene()
{
	return sceneAbout::create();
}

bool sceneAbout::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /*----------------MenuItemSprite aboutBack---------------------*/
    Sprite* aboutBackNormal = Sprite::create("./mainMenu/backToMenuNormal.png");
    Sprite* aboutBackSelected = Sprite::create("./mainMenu/backToMenuSelected.png");

    MenuItemSprite* aboutBack = MenuItemSprite::create(aboutBackNormal, aboutBackSelected, 
                                                        CC_CALLBACK_1(sceneAbout::aboutBack, this));

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

    /*-------------------Label About---------------*/
    auto labelAbout = Label::createWithTTF("About", "./fonts/Marker Felt.ttf", 60);
    if (labelAbout == nullptr)
    {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
    else
    {
		// position the label on the center of the screen
        labelAbout->setPosition(Vec2(CENTER_WIN_X, TOP_WIN_Y - labelAbout->getContentSize().height + 10));

		// add the label as a child to this layer
		this->addChild(labelAbout, 1);
	}

    /*-------------------Label aboutText---------------*/

    auto labelAboutText = Label::createWithTTF("This is a FXXKING AWESOME auto-chess.", "./fonts/Marker Felt.ttf", 70);
    if (labelAboutText == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelAboutText->setPosition(Vec2(CENTER_WIN_X, CENTER_WIN_Y));

        // add the label as a child to this layer
        this->addChild(labelAboutText, 1);
    }

    /*------------------background setting-------------------*/
    auto sprite1 = Sprite::create("./mainMenu/aboutBG.jpg");

    sprite1->setPosition(800, 460);
    this->addChild(sprite1);

    return true;

}

void sceneAbout::aboutBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}