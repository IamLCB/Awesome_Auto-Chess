#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_
#include "cocos2d.h"
#include "game/mapLayer.h"
USING_NS_CC;

#define designedHeroNum 8	// 设计英雄数量

struct heroInfo
{
	int id = 0;
	std::string picName = "";
	int cost = 0;
	bool buy = false;
};

class gameData : public Scene
{
public:
	int gameTurn;	// 游戏回合数
	static gameData* createGameData();
	virtual bool init();
	int getGameTurn() { return gameTurn; }
	void changeGameTurn() { gameTurn++; }
	void initGameStart(); // super init

	CREATE_FUNC(gameData);
};

extern gameData* globalGameData;

enum heroType
{
	None = 0,
	TFNS,
	BQZS,
	MLPS,
	QXSQ,
	WLSHZ,
	YN,
	LTZZ,
	SNZX
};

extern heroInfo heroList[designedHeroNum];

#endif // !_DATA_GAME_H_
