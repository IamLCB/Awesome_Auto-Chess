#pragma once
#include "cocos2d.h"
#include "./hero/hero.h"
#include "./player/playerData.h"

class aiPlayer
{
public:
	Hero* soldHero();
protected:
	void judgeGold();
	bool checkUpgrade();
	bool checkLimit();
	void judgeExp();
	bool checkHighGoldHero();
	bool aiBuy(int id);
	void refresh();
	void creatBattleArray();

	friend class sceneGame;

};
extern aiPlayer AIPlayer;