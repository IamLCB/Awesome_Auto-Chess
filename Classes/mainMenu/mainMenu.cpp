#include "mainMenu.h"


USING_NS_CC;

Scene* mainMenu::scene()
{
    // 'scene' is an autorelease object
    Scene * scene = Scene::create(); 
   
    // 'layer' is an autorelease object
    mainMenu *layer = mainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

// on "init" you need to initialize your instance
bool mainMenu::init()
{
	// 1. super init first
    if (!Layer::init())
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
    auto label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);

    if (label == nullptr)
    {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
    else
    {
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            			        origin.y + visibleSize.height - label->getContentSize().height));

		this->addChild(label, 1);
	}

    auto bground = Sprite::create("mainMenuBackground.png");
    bground->setPosition(800, 460);
    this->addChild(bground, 0);

    return true;
}


void mainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}