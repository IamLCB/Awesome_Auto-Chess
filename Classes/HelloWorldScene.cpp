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
    heros.push_back(hero5);
    heros.push_back(hero6);
    heros.push_back(hero7);
    heros.push_back(hero8);

    ccArrayAppendObject(myPlayerData.battleArray, hero1);
    hero1->ofPlayer = HUMAN;

    ccArrayAppendObject(opPlayerData.battleArray, hero2);
    hero2->ofPlayer = HUMAN;

    ccArrayAppendObject(myPlayerData.battleArray, hero3);
    hero3->ofPlayer = HUMAN;

    ccArrayAppendObject(opPlayerData.battleArray, hero4);
    hero4->ofPlayer = HUMAN;

    ccArrayAppendObject(myPlayerData.battleArray, hero5);
    hero5->ofPlayer = AI;

    ccArrayAppendObject(opPlayerData.battleArray, hero6);
    hero6->ofPlayer = AI;

    ccArrayAppendObject(myPlayerData.battleArray, hero7);
    hero7->ofPlayer = AI;

    ccArrayAppendObject(opPlayerData.battleArray, hero8);
    hero8->ofPlayer = AI;

    hero1->setPosition(100, 800);
    hero2->setPosition(550, 0);
    hero3->setPosition(550, 800);
    hero4->setPosition(550, 0);
    hero5->setPosition(1000, 800);
    hero6->setPosition(1000, 0);
    hero7->setPosition(1500, 800);
    hero8->setPosition(1500, 0);

    this->addChild(hero1, 1);
    this->addChild(hero2, 1);
    this->addChild(hero3, 1);
    this->addChild(hero4, 1);
    this->addChild(hero5, 1);
    this->addChild(hero6, 1);
    this->addChild(hero7, 1);
    this->addChild(hero8, 1);

    for (Hero* tmp : heros) {
        tmp->Play();
    }

    return true;

}



void sceneTest::aboutBack(cocos2d::Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}
