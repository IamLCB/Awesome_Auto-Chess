#include "mainMenu.h"
#include "globalResSetting.h"
#include "sceneAbout.h"
#include "sceneSetting.h"
#include "game/sceneGame.h"
#include "sceneName.h"
//#include "hero.h"

USING_NS_CC;

Scene* mainMenu::createScene()
{
    return mainMenu::create();
}

// on "init" you need to initialize your instance
bool mainMenu::init()
{
	// 1. super init first
    if (!Scene::init())
    {
		return false;
	}

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /*----------------MenuItemImage closeItem---------------------*/
    auto closeItem = MenuItemImage::create(
                                             "CloseNormal.png",
                                             "CloseSelected.png",
                                              CC_CALLBACK_1(mainMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    /*----------------MenuBackground---------------------*/

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create(BG_PNG);
    if (sprite == nullptr)
    {
        problemLoading("'mainMenuBackground.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setScale(BG_SCALE);
        sprite->setPosition(CENTER_WIN);


        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    int singalHeight = 36 / BG_SCALE + 1;
    int singalWidth = 123 / BG_SCALE + 1;

    /*----------------MenuItemSprite newGame--------------------*/
    Sprite* newGameNormal = Sprite::create(BG_BTNS, Rect(0, 0, singalWidth, singalHeight));
    Sprite* newGameSelected = Sprite::create(BG_BTNS, Rect(0, singalHeight, singalWidth, singalHeight));

    MenuItemSprite* newGame = MenuItemSprite::create(newGameNormal, newGameSelected, 
        CC_CALLBACK_1(mainMenu::onNewGame, this));

    if (newGame == nullptr ||
        newGame->getContentSize().width <= 0 ||
        newGame->getContentSize().height <= 0)
    {
        problemLoading("'newGameNormal.png' and 'newGameSelected.png'");
    }
    else
    {
        float x = CENTER_WIN_X;
        float y = CENTER_WIN_Y - 300;
        newGame->setPosition(Vec2(x, y));
        newGame->setScale(BG_SCALE);
    }

    auto menuNewGame = Menu::create(newGame, nullptr);
    menuNewGame->setPosition(Vec2::ZERO);
    this->addChild(menuNewGame, 1);
   
    
    /*----------------MenuItemSprite gameSettings--------------------*/
    Sprite* gameSettingsNormal = Sprite::create(BG_BTNS, Rect(singalWidth, 0, singalWidth, singalHeight));
    Sprite* gameSettingsSelected = Sprite::create(BG_BTNS, Rect(singalWidth, singalHeight, singalWidth, singalHeight));

    MenuItemSprite* gameSettings = MenuItemSprite::create(gameSettingsNormal, gameSettingsSelected,
        CC_CALLBACK_1(mainMenu::onSettings, this));

    if (gameSettings == nullptr ||
        gameSettings->getContentSize().width <= 0 ||
        gameSettings->getContentSize().height <= 0)
    {
        problemLoading("'gameSettingsNormal.png' and 'gameSettingsSelected.png'");
    }
    else
    {
        float x = CENTER_WIN_X;
        float y = CENTER_WIN_Y - 300 - singalHeight - 15;
        gameSettings->setPosition(Vec2(x, y));
        gameSettings->setScale(BG_SCALE);
    }

    auto menuGameSettings = Menu::create(gameSettings, nullptr);
    menuGameSettings->setPosition(Vec2::ZERO);
    this->addChild(menuGameSettings, 1);
 
    
    /*----------------MenuItemSprite about--------------------*/
    Sprite* aboutNormal = Sprite::create(BG_BTNS, Rect(singalWidth * 2, 0, singalWidth, singalHeight));
    Sprite* aboutSelected = Sprite::create(BG_BTNS, Rect(singalWidth * 2, singalHeight, singalWidth, singalHeight));

    MenuItemSprite* about = MenuItemSprite::create(aboutNormal, aboutSelected, 
        CC_CALLBACK_1(mainMenu::onAbout, this));

    //“关于”按钮tag为21
    about->setTag(21);

    if (about == nullptr ||
        about->getContentSize().width <= 0 ||
        about->getContentSize().height <= 0)
    {
		problemLoading("'aboutNormal.png' and 'aboutSelected.png'");
	}
    else
    {
		float x = CENTER_WIN_X;
        float y = CENTER_WIN_Y - 300 - singalHeight * 2 - 30;
		about->setPosition(Vec2(x, y));
        about->setScale(BG_SCALE);
	}

    auto menuAbout = Menu::create(about, nullptr);
    menuAbout->setPosition(Vec2::ZERO);
    this->addChild(menuAbout, 1);

    return true;
}


void mainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}

void mainMenu::onNewGame(Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, sceneName::createScene()));
}

void mainMenu::onSettings(Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, sceneSettings::createScene()));
}

void mainMenu::onAbout(Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, sceneAbout::createScene()));
}
