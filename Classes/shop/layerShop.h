#ifndef _LAYERS_SHOP_H_
#define _LAYERS_SHOP_H_

#include "hero/allheros.h"
#include "player/playerData.h"
#include "cocos2d.h"
#include <stdlib.h>
#include <random>
using namespace std;
USING_NS_CC;

class layerShop : public Layer
{
	int x = 470;
	const string heroValue[6] =
	{ "","1 coin","2 coins","3 coins","4 coins","5 coins" };

	cocos2d::Layer* subLayer = Layer::create();

public:
	static layerShop* createLayerShop();

	CREATE_FUNC(layerShop);
	virtual bool init();
	layerShop();

	void refresh1(cocos2d::Ref* pSender);
	void refresh(playerData& playerData);
	
	void shop();
	void openShop();
	void closeShop();
	void heroShop(int i);
	void closeLayer(cocos2d::Ref* pSender);
	void openLayer(cocos2d::Ref* pSender);

	void cover(float x, float y);
	void buy1(cocos2d::Ref* pSender);
	void buy2(cocos2d::Ref* pSender);
	void buy3(cocos2d::Ref* pSender);
	void buy4(cocos2d::Ref* pSender);
	void buy5(cocos2d::Ref* pSender);
	bool canBuy(int x,playerData& playerData);

	cocos2d::MenuItemImage* closeShopButton;
	cocos2d::MenuItemImage* openShopButton;
};



#endif // !_LAYERS_SHOP_H_
