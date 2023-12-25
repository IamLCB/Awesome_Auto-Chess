#include "sceneSetting.h"
#include "globalResSetting.h"
#include "mainMenu.h"
#include "AudioEngine.h"

USING_NS_CC;

Scene* sceneSettings::createScene()
{
    return sceneSettings::create();
}

bool sceneSettings::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*----------------MenuItemSprite settingsBack---------------------*/
    Sprite* settingsBackNormal = Sprite::create("./mainMenu/backToMenuNormal.png");
    Sprite* settingsBackSelected = Sprite::create("./mainMenu/backToMenuSelected.png");

    MenuItemSprite* settingsBack = MenuItemSprite::create(settingsBackNormal, settingsBackSelected,
        CC_CALLBACK_1(sceneSettings::settingsBack, this));

    if (settingsBack == nullptr ||
        settingsBack->getContentSize().width <= 0 ||
        settingsBack->getContentSize().height <= 0)
    {
        problemLoading("'backToMenuNormal.png' and 'backToMenuSelected.png'");
    }
    else
    {
        float x = CENTER_WIN_X;
        float y = BOTTOM_WIN_Y + settingsBack->getContentSize().height / 2 + 5;
        settingsBack->setPosition(Vec2(x, y));
    }

    auto menuSettingsBack = Menu::create(settingsBack, nullptr);
    menuSettingsBack->setPosition(Vec2::ZERO);
    this->addChild(menuSettingsBack, 1);

    /*-------------------Label Settings---------------*/
    auto labelSettings = Label::createWithTTF("Settings", "./fonts/Marker Felt.ttf", 60);
    if (labelSettings == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        labelSettings->setPosition(Vec2(CENTER_WIN_X, TOP_WIN_Y - labelSettings->getContentSize().height + 15));

        // add the label as a child to this layer
        this->addChild(labelSettings, 1);
    }

    /*------------------background setting-------------------*/
    auto sprite1 = Sprite::create("./mainMenu/aboutBG.jpg");

    sprite1->setPosition(800, 460);
    this->addChild(sprite1);

    /*----------------MenuItemSprite switchSound---------------------*/
    auto* labelSound = Label::createWithTTF("Sound", "./fonts/Marker Felt.ttf", 60);
    Sprite* soundOffNormal = Sprite::create("./mainMenu/soundOffNormal.png");
    Sprite* soundOffSelected = Sprite::create("./mainMenu/soundOffSelected.png");
    Sprite* soundOnNormal = Sprite::create("./mainMenu/soundOnNormal.png");
    Sprite* soundOnSelected = Sprite::create("./mainMenu/soundOnSelected.png");

    MenuItemSprite* soundOff = MenuItemSprite::create(soundOffNormal, soundOffSelected,
        		            CC_CALLBACK_1(sceneSettings::soundOff, this));
    MenuItemSprite* soundOn = MenuItemSprite::create(soundOnNormal, soundOnSelected,
                            CC_CALLBACK_1(sceneSettings::soundOn, this));
    if (labelSound == nullptr ||
        labelSound->getContentSize().width <= 0 ||
        labelSound->getContentSize().height <= 0)
    {
		problemLoading("'fonts/Marker Felt.ttf'");
	}
    else
    {
		float x = CENTER_WIN_X;
        float y = CENTER_WIN_Y + labelSound->getContentSize().height;
        labelSound->setPosition(Vec2(x, y));
        labelSound->setColor(Color3B::BLACK);
        this->addChild(labelSound, 1);
	}


    if (soundOff == nullptr ||
        soundOff->getContentSize().width <= 0 ||
        soundOff->getContentSize().height <= 0)
    {
		problemLoading("'soundOffNormal.png' and 'soundOffSelected.png'");
	}
    else
    {
        float x = CENTER_WIN_X - soundOff->getContentSize().width / 2 - 10;
        float y = CENTER_WIN_Y - 20;
		soundOff->setPosition(Vec2(x, y));
	}
    auto menuSoundOff = Menu::create(soundOff, nullptr);
    menuSoundOff->setPosition(Vec2::ZERO);
    this->addChild(menuSoundOff, 1);

    if (soundOn == nullptr ||
        soundOn->getContentSize().width <= 0 ||
        soundOn->getContentSize().height <= 0)
    {
        problemLoading("'soundOnNormal.png' and 'soundOnSelected.png'");
    }
    else
    {
        float x = CENTER_WIN_X + soundOn->getContentSize().width / 2 + 10;
        float y = CENTER_WIN_Y - 20;
        soundOn->setPosition(Vec2(x, y));
    }
    auto menuSoundOn = Menu::create(soundOn, nullptr);
    menuSoundOn->setPosition(Vec2::ZERO);
    this->addChild(menuSoundOn, 1);


    return true;
}

void sceneSettings::settingsBack(Ref* pSender)
{
    _director->pushScene(TransitionFade::create(1.0f, mainMenu::createScene()));
}

void sceneSettings::soundOff(Ref* pSender)
{
	AudioEngine::pauseAll();
}

void sceneSettings::soundOn(Ref* pSender)
{
	AudioEngine::resumeAll();
}
