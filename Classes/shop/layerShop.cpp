#include "layerShop.h"

layerShop::layerShop() {
	shop();
}
layerShop* layerShop::createLayerShop() {
	auto tmp = layerShop::create();
	tmp->retain();
	return tmp;
}
bool layerShop::init() {
	if (!Layer::init()) {
		return false;
	}
	srand(time(NULL));
	return true;
}
bool layerShop::canBuy(int x, playerData& playerData) {
	int sum = 0;
	if (playerData.heroForBuy[x].cost > myPlayerData.playerMoney) {
		auto tmp = Label::createWithTTF("Not enough money!", "fonts/arial.ttf", 36);
		this->addChild(tmp);
		tmp->setTextColor(Color4B::WHITE);
		tmp->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		tmp->runAction(fade);
		return false;
	}
	for (int i = 0; i < CHESS_IN_A_ROW; i++) {
		sum += haveChess[0][i];
	}
	if (sum == 8) {
		auto tmp = Label::createWithTTF("You have too many heroes!", "fonts/arial.ttf", 36);
		this->addChild(tmp);
		tmp->setTextColor(Color4B::WHITE);
		tmp->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		tmp->runAction(fade);
		return false;
	}
	return true;
}
void layerShop::openShop() {
	openShopButton = MenuItemImage::create("./shop/openShop.png", "./shop/openShop.png",
		CC_CALLBACK_1(layerShop::openLayer, this));
	auto Open = Menu::create(openShopButton, nullptr);
	Open->setPosition(-250, 150);
	Open->setScale(0.1f);
	this->addChild(Open, 1);
}

void layerShop::closeShop() {
	closeShopButton = MenuItemImage::create("./shop/closeShop.png", "./shop/closeShop.png",
		CC_CALLBACK_1(layerShop::closeLayer, this));
	auto Close = Menu::create(closeShopButton, nullptr);
	Close->setPosition(-250, 200);
	Close->setScale(0.1f); 
	this->addChild(Close, 1);
}

void layerShop::openLayer(cocos2d::Ref* pSender) {
	subLayer->setPosition(650, 350);
	if (openShopButton != nullptr) {
		openShopButton->setVisible(false);
	}
	if (closeShopButton != nullptr) {
		closeShopButton->setVisible(true);
	}
}

void layerShop::closeLayer(cocos2d::Ref* pSender) 
{
	subLayer->setPosition(20000, 20000);
	openShop();
	if (openShopButton != nullptr) {
		openShopButton->setVisible(true);
	}
	if (closeShopButton != nullptr) {
		// Òþ²Ø°´Å¥
		closeShopButton->setVisible(false);
	}
}

void layerShop::heroShop(int i) 
{
	auto label1 = Label::createWithTTF(heroValue[myPlayerData.heroForBuy[i].cost], "fonts/arial.ttf", 28);
	subLayer->addChild(label1);
	label1->setPosition(790 - 350 * (4 - i), 420);
}

void layerShop::cover(float x, float y) {
	auto cover = Sprite::create("./shop/cover.png");
	subLayer->addChild(cover, 3);
	cover->setPosition(x, y);
}

void layerShop::buy1(cocos2d::Ref* pSender) {
	if (myPlayerData.heroForBuy[0].buy == false && canBuy(0, myPlayerData))
	{
		auto sprite = createHero(myPlayerData.heroForBuy[0].id);
		myPlayerData.heroForBuy[0].buy = true;
		ccArrayAppendObject(myPlayerData.waitingArray, sprite);
		myPlayerData.playerHaveNewHero = true;
		myPlayerData.playerMoney -= myPlayerData.heroForBuy[0].cost;
		cover(790 - 350 * 4, 250);
	}
}

void layerShop::buy2(cocos2d::Ref* pSender) {
	if (myPlayerData.heroForBuy[1].buy == false && canBuy(1, myPlayerData))
	{
		auto sprite = createHero(myPlayerData.heroForBuy[1].id);
		myPlayerData.heroForBuy[1].buy = true;
		ccArrayAppendObject(myPlayerData.waitingArray, sprite);
		myPlayerData.playerHaveNewHero = true;
		myPlayerData.playerMoney -= myPlayerData.heroForBuy[1].cost;
		cover(790 - 350 * 3, 250);
	}
}

void layerShop::buy3(cocos2d::Ref* pSender) {
	if (myPlayerData.heroForBuy[2].buy == false && canBuy(2, myPlayerData))
	{
		auto sprite = createHero(myPlayerData.heroForBuy[2].id);
		myPlayerData.heroForBuy[2].buy = true;
		ccArrayAppendObject(myPlayerData.waitingArray, sprite);
		myPlayerData.playerHaveNewHero = true;
		myPlayerData.playerMoney -= myPlayerData.heroForBuy[2].cost;
		cover(790 - 350 * 2, 250);
	}
}

void layerShop::buy4(cocos2d::Ref* pSender) {
	if (myPlayerData.heroForBuy[3].buy == false && canBuy(3, myPlayerData))
	{
		auto sprite = createHero(myPlayerData.heroForBuy[3].id);
		myPlayerData.heroForBuy[3].buy = true;
		ccArrayAppendObject(myPlayerData.waitingArray, sprite);
		myPlayerData.playerHaveNewHero = true;
		myPlayerData.playerMoney -= myPlayerData.heroForBuy[3].cost;
		cover(790 - 350 * 1, 250);
	}
}

void layerShop::buy5(cocos2d::Ref* pSender) {
	if (myPlayerData.heroForBuy[4].buy == false && canBuy(4, myPlayerData))
	{
		auto sprite = createHero(myPlayerData.heroForBuy[4].id);
		myPlayerData.heroForBuy[4].buy = true;
		ccArrayAppendObject(myPlayerData.waitingArray, sprite);
		myPlayerData.playerHaveNewHero = true;
		myPlayerData.playerMoney -= myPlayerData.heroForBuy[4].cost;
		cover(790 - 350 * 0, 250);
	}
}

void layerShop::shop() {
	static int x, y;
	x = 650;
	y = 350;
	subLayer = Layer::create();
	subLayer->setPosition(x,y);
	subLayer->setScale(0.6f);
	this->addChild(subLayer, 2);

	/*-------------------set background----------------------*/
	auto sprite = Sprite::create("./shop/backgroundofshop.png");
	sprite->setPosition(80, 250);
	subLayer->addChild(sprite);

	/*-------------------set label-------------------------*/
	auto label = Label::createWithTTF("SHOP", "fonts/Marker Felt.ttf", 24);
	label->setPosition(80, 490);
	subLayer->addChild(label);
	/*------------------refresh----------------------------*/
	auto Refresh = MenuItemImage::create("./shop/refresh.png", "./shop/refresh.png",
		CC_CALLBACK_1(layerShop::refresh1, this));
	auto reFresh = Menu::create(Refresh, nullptr);
	reFresh->setPosition(110, 570);
	subLayer->addChild(reFresh, 1);
	refresh(myPlayerData);

	/*------------------buy----------------------------*/
	heroShop(0);
	auto buy1 = MenuItemImage::create(myPlayerData.heroForBuy[0].picName, myPlayerData.heroForBuy[0].picName,
		CC_CALLBACK_1(layerShop::buy1, this));
	auto Buy1 = Menu::create(buy1, nullptr);
	subLayer->addChild(Buy1, 1);
	Buy1->setPosition(790 - 350 * 4, 250);
	buy1->setScale(0.5f);

	heroShop(1);
	auto buy2 = MenuItemImage::create(myPlayerData.heroForBuy[1].picName, myPlayerData.heroForBuy[1].picName,
		CC_CALLBACK_1(layerShop::buy2, this));
	auto Buy2 = Menu::create(buy2, NULL);
	subLayer->addChild(Buy2, 1);
	Buy2->setPosition(790 - 350 * 3, 250);
	buy2->setScale(0.5f);

	heroShop(2);
	auto buy3 = MenuItemImage::create(myPlayerData.heroForBuy[2].picName, myPlayerData.heroForBuy[2].picName,
		CC_CALLBACK_1(layerShop::buy3, this));
	auto Buy3 = Menu::create(buy3, NULL);
	subLayer->addChild(Buy3, 1);
	Buy3->setPosition(790 - 350 * 2, 250);
	buy3->setScale(0.5f);

	heroShop(3);
	auto buy4 = MenuItemImage::create(myPlayerData.heroForBuy[3].picName, myPlayerData.heroForBuy[3].picName,
		CC_CALLBACK_1(layerShop::buy4, this));
	auto Buy4 = Menu::create(buy4, NULL);
	subLayer->addChild(Buy4, 1);
	Buy4->setPosition(790 - 350 * 1, 250);
	buy4->setScale(0.5f);

	heroShop(4);
	auto buy5 = MenuItemImage::create(myPlayerData.heroForBuy[4].picName, myPlayerData.heroForBuy[4].picName,
		CC_CALLBACK_1(layerShop::buy5, this));
	auto Buy5 = Menu::create(buy5, NULL);
	subLayer->addChild(Buy5, 1);
	Buy5->setPosition(790 - 350 * 0, 250);
	buy5->setScale(0.5f);

	/*----------------------close store-----------------*/
	closeShop();

	/*-----------------------reset buy status-----------*/
	for (int i = 0; i < 5; i++)
	{
		myPlayerData.heroForBuy[i].buy = false;
	}
}

void layerShop::refresh1(cocos2d::Ref* pSender) {
	srand(time(NULL));
	if (myPlayerData.playerMoney >= 2)
	{
		myPlayerData.playerMoney -= 2;
		subLayer->removeAllChildren();
		shop();
	}
	else
	{
		auto label = Label::createWithTTF("Not enough money!", "fonts/arial.ttf", 36);
		this->addChild(label);
		label->setTextColor(Color4B::WHITE);
		label->setPosition(800, 400);
		auto fade = FadeOut::create(2.0f);
		label->runAction(fade);
		return;
	}
}

void layerShop::refresh(playerData& playerdata) {
	srand(time(NULL));
	for (int i = 0; i < 5; i++)
	{
		int tmp = rand() % 8 + 1;
		myPlayerData.heroForBuy[i].buy = false;
		myPlayerData.heroForBuy[i].id = heroList[tmp - 1].id;
		myPlayerData.heroForBuy[i].picName = heroList[tmp - 1].picName;
		myPlayerData.heroForBuy[i].cost = heroList[tmp - 1].cost;
	}
}