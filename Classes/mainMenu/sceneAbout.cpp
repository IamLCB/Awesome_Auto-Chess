#include "sceneAbout.h"
#include "mainMenu.h"
#include "globalResSetting.h"
<<<<<<< HEAD
#include"hero/hero.h"
#include"hero/tfns.h"
#include"hero/bqzs.h"
=======
#include "hero/hero.h"
#include "hero/tfns.h"
#include "hero/mlps.h"
#include "hero/ltzz.h"
#include "hero/bqzs.h"
#include "hero/yn.h"
#include "hero/qxsq.h"
#include "hero/snzx.h"
#include <vector>

using std::vector;
>>>>>>> 44cc8347f8d726de9fc6de592d7e1f43ed58c0e5

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
    Hero* sprite = createHero(1);
    Hero* sprite22 = createHero(1);
    ccArrayAppendObject(myPlayerData.battleArray, sprite);
    ccArrayAppendObject(opPlayerData.battleArray, sprite22);
    sprite1->setPosition(800, 460);
    sprite22->setPosition(80, 46);
    sprite->setPosition(0, 500);
    this->addChild(sprite1);
<<<<<<< HEAD
    this->addChild(sprite22, 3);
    this->addChild(sprite, 2);
    sprite->Play();
    sprite22->Play();
=======


    

    Hero* hero1 = createHero(BQZS);
    Hero* hero2 = createHero(QXSQ);
    Hero* hero3 = createHero(YN);
    Hero* hero4 = createHero(SNZX);
    Hero* hero5 = createHero(TFNS);
    Hero* hero6 = createHero(MLPS);
    Hero* hero7 = createHero(WLSHZ);
    Hero* hero8 = createHero(LTZZ);

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

    hero1->Play();
    hero2->Play();
    hero3->Play();
    hero4->Play();

    return true;

>>>>>>> 44cc8347f8d726de9fc6de592d7e1f43ed58c0e5
}



void sceneAbout::aboutBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}
