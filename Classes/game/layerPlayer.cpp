#include "game/layerPlayer.h"

const Point myBloodPos = Point(250, 610);
const Point myExpPos = Point(250, 590);

const Point opBloodPos = Point(250, 710);
const Point opExpPos = Point(250, 690);

layerPlayer* layerPlayer::createPlayer(string& name)
{
	auto player = layerPlayer::create();

	/**********myPlayer nickName and avatar************/
	Sprite* myAvatar = Sprite::create("./player/avatar1.png");
	myAvatar->setPosition(50, 600);
	myAvatar->setScale(0.03f);
	player->addChild(myAvatar);

	Label* myName = Label::createWithTTF(name, "./fonts/Marker Felt.ttf", 24);
	myName->setPosition(80 + myName->getContentSize().width, 640);
	player->addChild(myName, 1);

	/**********opPlayer nickName and avatar************/
	Sprite* opAvatar = Sprite::create("./player/avatar2.png");
	opAvatar->setPosition(50, 700);
	player->addChild(opAvatar);

	Label* opName = Label::createWithTTF("opPlayer", "./fonts/Marker Felt.ttf", 24);
	opName->setPosition(60 + opName->getContentSize().width, 740);
	opAvatar->setScale(0.03f);
	player->addChild(opName, 1);

	player->retain(); // retain the player
	player->Coins->retain();
	player->Levels->retain();
	player->autorelease();

	return player;

}

bool layerPlayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/*************buyExp***************/
	MenuItemImage* buyExp = MenuItemImage::create("./player/buyExpNormal.png", "./player/buyExpSelected.png", 
		CC_CALLBACK_1(layerPlayer::buyExp, this));
	Menu* menuBuyExp = Menu::create(buyExp, nullptr);
	menuBuyExp->setPosition(-590, -250);
	this->addChild(menuBuyExp, 1);

	/*************myPlayer UIs***************/
	/**************BloodBar**************/
	this->setPosition(0,0);
	playerHPBarBg->setPosition(myBloodPos);
	playerHPBarBg->setScale(0.5f);
	this->addChild(playerHPBarBg, 1);

	playerHPBar->setType(ProgressTimer::Type::BAR);
	playerHPBar->setBarChangeRate(Point(1, 0));
	playerHPBar->setMidpoint(Point(0, 1));
	playerHPBar->setPosition(myBloodPos);
	playerHPBar->setPercentage(myPlayerData.playerHealth);
	this->addChild(playerHPBar, 2);

	playerHP->setPosition(myBloodPos.x+180, myBloodPos.y);
	this->addChild(playerHP, 3);

	/**************Level**************/
	playerExpBarBg->setPosition(myExpPos);
	playerExpBarBg->setScale(0.5f);
	this->addChild(playerExpBarBg, 1);

	playerExpBar->setType(ProgressTimer::Type::BAR);
	playerExpBar->setBarChangeRate(Point(1, 0));
	playerExpBar->setMidpoint(Point(0, 1));
	playerExpBar->setPosition(myExpPos);
	playerExpBar->setPercentage(myPlayerData.playerExp * 100 / myPlayerData.expToLevelUp);
	this->addChild(playerExpBar, 2);

	Levels->setPosition(myExpPos.x + 190, myExpPos.y);
	this->addChild(Levels, 3);

	/**************Coins**************/
	Coins->setPosition(300,640);
	this->addChild(Coins, 3);

	/*************opPlayer UIs***************/
	/**************BloodBar**************/
	this->setPosition(0, 0);
	opplayerHPBarBg->setPosition(opBloodPos);
	opplayerHPBarBg->setScale(0.5f);
	this->addChild(opplayerHPBarBg, 1);
	
	opplayerHPBar->setType(ProgressTimer::Type::BAR);
	opplayerHPBar->setBarChangeRate(Point(1, 0));
	opplayerHPBar->setMidpoint(Point(0, 1));
	opplayerHPBar->setPosition(opBloodPos);
	opplayerHPBar->setPercentage(opPlayerData.playerHealth);
	this->addChild(opplayerHPBar, 2);

	opplayerHP->setPosition(opBloodPos.x + 180, opBloodPos.y);
	this->addChild(opplayerHP, 3);

	/**************Level**************/
	opplayerExpBarBg->setPosition(opExpPos);
	opplayerExpBarBg->setScale(0.5f);
	this->addChild(opplayerExpBarBg, 1);

	opplayerExpBar->setType(ProgressTimer::Type::BAR);
	opplayerExpBar->setBarChangeRate(Point(1, 0));
	opplayerExpBar->setMidpoint(Point(0, 1));
	opplayerExpBar->setPosition(opExpPos);
	opplayerExpBar->setPercentage(opPlayerData.playerExp * 100 / opPlayerData.expToLevelUp);
	this->addChild(opplayerExpBar, 2);

	opLevels->setPosition(opExpPos.x + 190, opExpPos.y);
	this->addChild(opLevels, 3);

	/**************Coins**************/
	opCoins->setPosition(300,740);
	this->addChild(opCoins, 3);

	return true;
}

void layerPlayer::buyExp(Ref* pSender)
{
	if (myPlayerData.playerMoney >= 4)
	{
		myPlayerData.playerMoney -= 4;
		myPlayerData.playerExp += 4;
		myPlayerData.calExp();
	}
	else
	{
		Label* label = Label::createWithTTF("Not enough money!", "./fonts/Marker Felt.ttf", 36);
		label->setPosition(800,400);
		this->addChild(label, 1);
		auto action = FadeOut::create(2.0f);
		label->runAction(action);
	}
}

void layerPlayer::update(float dt)
{
	/*************myPlayer UIs***************/
	/**************BloodBar**************/
	playerHPBar->setPercentage(myPlayerData.playerHealth);
	playerHPBar->setTag(myPlayerData.playerHealth);
	playerHP->setString(to_string(myPlayerData.playerHealth));

	/**************Coins**************/
	Coins->setString("Coins: " + to_string(myPlayerData.playerMoney));

	/**************Level**************/
	playerExpBar->setPercentage(myPlayerData.playerExp * 100 / myPlayerData.expToLevelUp);
	Levels->setString("Level: " + to_string(myPlayerData.playerLevel));

	/*************opPlayer UIs***************/
	/**************BloodBar**************/
	opplayerHPBar->setPercentage(opPlayerData.playerHealth);
	opplayerHPBar->setTag(opPlayerData.playerHealth);
	opplayerHP->setString(to_string(opPlayerData.playerHealth));

	/**************Coins**************/
	opCoins->setString("Coins: " + to_string(opPlayerData.playerMoney));

	/**************Level**************/
	opplayerExpBar->setPercentage(opPlayerData.playerExp * 100 / opPlayerData.expToLevelUp);
	opLevels->setString("Level: " + to_string(opPlayerData.playerLevel));
}