#ifndef _LAYERS_HERO_H_
#define _LAYERS_HERO_H_

#include "cocos2d.h"
#include "player/playerData.h"
#include "hero/allheros.h"
USING_NS_CC;
using namespace std;

class layerHero : public cocos2d::Layer
{
public:
	static layerHero* createLayerHero();
	CREATE_FUNC(layerHero);

	void playerArrayInit(ccArray* Array, int playerInfo);
	virtual bool init();
	void update(float dt);

	/****aiœ‡πÿ****/
	void aiShowWaitingArray();
	void aiShowBattleArray();

private:
	void heroUpgrade(playerData& pData);
	Hero* layerHero::upgradeHeroInit(int type);

	friend class sceneGame;
	float calDistance(Hero* h1, Hero* h2);
	float calDistance(Point p1, Point p2);
};


#endif // !_LAYERS_HERO_H_
