#include "mainMenu.h"
#include "globalResSetting.h"
#include "layerAbout.h"
#include "layerSetting.h"
#include "layerGame.h"

USING_NS_CC;

Scene* mainMenu::createScene()
{
    return mainMenu::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
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



    /*----------------MenuItemLabel and Background---------------------*/

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
    Sprite* newGameNormal = Sprite::create(BG_BTNS, Rect(0, 0, singalWidth, singalHeight));
    Sprite* newGameSelected = Sprite::create(BG_BTNS, Rect(0, singalHeight, singalWidth, singalHeight));
    Sprite* newGameDisabled = Sprite::create(BG_BTNS, Rect(0, singalHeight * 2, singalWidth, singalHeight));

    Sprite* gameSettingsNormal = Sprite::create(BG_BTNS, Rect(singalWidth, 0, singalWidth, singalHeight));
    Sprite* gameSettingsSelected = Sprite::create(BG_BTNS, Rect(singalWidth, singalHeight, singalWidth, singalHeight));
    Sprite* gameSettingsDisabled = Sprite::create(BG_BTNS, Rect(singalWidth, singalHeight * 2, singalWidth, singalHeight));

    Sprite* aboutNormal = Sprite::create(BG_BTNS, Rect(singalWidth * 2, 0, singalWidth, singalHeight));
    Sprite* aboutSelected = Sprite::create(BG_BTNS, Rect(singalWidth * 2, singalHeight, singalWidth, singalHeight));
    Sprite* aboutDesabled = Sprite::create(BG_BTNS, Rect(singalWidth * 2, singalHeight * 2, singalWidth, singalHeight));

    MenuItemSprite* newGame = MenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled,
        CC_CALLBACK_1(mainMenu::onNewGame, this));

    MenuItemSprite* gameSetting = MenuItemSprite::create(gameSettingsNormal, gameSettingsSelected, gameSettingsDisabled,
        CC_CALLBACK_1(mainMenu::onSettings, this));
    //“设置”按钮tag为20
    gameSetting->setTag(20);

    MenuItemSprite* about = MenuItemSprite::create(aboutNormal, aboutSelected, aboutDesabled,
        CC_CALLBACK_1(mainMenu::onAbout, this));
    //“关于”按钮tag为21
    about->setTag(21);


    return true;
}


void mainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

}


void mainMenu::onNewGame(Ref* pSender)
{
    Scene* scene = Scene::create();
    //scene->addChild(layerGame::create());

    //Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));

}

void mainMenu::onSettings(Ref* pSender)
{
    //转到"SettingsLayer"
   // Scene* scene = layerSetting::scene();
    //Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));

}

void mainMenu::onAbout(Ref* pSender)
{
    //Scene* scene = layerAbout::scene();
   // Director::getInstance()->replaceScene(TransitionFade::create(1.2, scene));
}