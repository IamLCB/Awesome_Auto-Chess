#ifndef _DATA_GAME_H_
#define _DATA_GAME_H_
#include "cocos2d.h"
#include "player/playerData.h"
USING_NS_CC;

#define maxHeroNum 20		// ������Ӣ������
#define designedHeroNum 8	// ���Ӣ������

class gameData : public Scene
{
public:
	int gameTurn;	// ��Ϸ�غ���
	static gameData* createGameData();
	virtual bool init();
	int getGameTurn() { return gameTurn; }
	void changeGameTurn() { gameTurn++; }
	void initGameStart(); // super init

	CREATE_FUNC(gameData);
};

struct heroInfo
{
	int id = 0;
	std::string picName = "";
	int cost = 0;
	bool buy = false;
};

extern gameData* globalGameData;

enum heroType
{
	None = 0,
	tfns,
	bqzs,
	mlps,
	qxsq,
	wlshz,
	ynyn,
	ltzz,
	snzx
};

extern heroInfo heroList[designedHeroNum];

#endif // !_DATA_GAME_H_
