#include "HelloWorldScene.h"
#include "mainMenu/mainMenu.h"
#include "globalResSetting.h"
#include "hero/hero.h"
#include "hero/tfns.h"
#include "hero/mlps.h"
#include "hero/ltzz.h"
#include "hero/bqzs.h"
#include "hero/yn.h"
#include "hero/qxsq.h"
#include "hero/snzx.h"
#include <vector>
#include "inGameTimer/inGameTimer.h"

using std::vector;


USING_NS_CC;

void sceneTest::playAllHeros(float dt) {
    for (Hero* hero : heros) {
        hero->Play();
    }
}

Scene* sceneTest::createScene()
{
    return sceneTest::create();
}

bool sceneTest::init()
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
        CC_CALLBACK_1(sceneTest::aboutBack, this));

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

    /*------------------background setting-------------------*/
    auto sprite1 = Sprite::create("./mainMenu/aboutBG.jpg");

    sprite1->setPosition(800, 460);
    this->addChild(sprite1);
    
  /*      Hero* hero1 = createHero(BQZS);
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
        hero3->setPosition(0, 500);
        hero4->setPosition(1500, 800);

        this->addChild(hero1, 1);
        this->addChild(hero2, 1);
        this->addChild(hero3, 1);
        this->addChild(hero4, 1);

        hero1->Play();
        hero2->Play();
        hero3->Play();
        hero4->Play();*/
    
    return true;

}



void sceneTest::aboutBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}
