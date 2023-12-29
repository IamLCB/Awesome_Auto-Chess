#include "sceneAbout.h"
#include "mainMenu.h"
#include "globalResSetting.h"
#include "hero/hero.h"
#include "hero/tfns.h"
#include "hero/mlps.h"
#include "hero/ltzz.h"
#include <vector>

using std::vector;

USING_NS_CC;

void sceneAbout::playAllHeros(float dt) {
    for (Hero* hero : heros) {
        hero->Play();
    }
}

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


    
    Hero* hero1 = createHero(TFNS);
    Hero* hero2 = createHero(MLPS);
    Hero* hero3 = createHero(WLSHZ);
    Hero* hero4 = createHero(LTZZ);

    heros.push_back(hero1);
    heros.push_back(hero2);
    heros.push_back(hero3);
    heros.push_back(hero4);

    ccArrayAppendObject(myPlayerData.battleArray, hero1);
    hero1->ofPlayer = HUMAN;

    ccArrayAppendObject(opPlayerData.battleArray, hero2);
    hero2->ofPlayer = AI;

    ccArrayAppendObject(myPlayerData.battleArray, hero3);
    hero3->ofPlayer = HUMAN;

    ccArrayAppendObject(opPlayerData.battleArray, hero4);
    hero4->ofPlayer = AI;

    hero1->setPosition(80, 46);
    hero2->setPosition(800, 460);
    hero2->addChild(hero2->createHealthBar("./hero/backgroundTexture.png", "./hero/foregroundTexture.png", 1, hero2->getPosition()));
    hero3->setPosition(0, 500);
    hero4->setPosition(1500, 800);

    this->addChild(hero1, 1);
    this->addChild(hero2, 1);
    this->addChild(hero3, 1);
    this->addChild(hero4, 1);

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(sceneAbout::playAllHeros), 1 / 60.f);

    return true;

}



void sceneAbout::aboutBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}