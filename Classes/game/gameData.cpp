#include "game/gameData.h"

gameData* globalGameData = gameData::createGameData();

gameData* gameData::createGameData()
{
	auto game = gameData::create();
	game->retain();
	return game;
}

bool gameData::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;

	heroList[tfns].picName;
}

void gameData::initGameStart()
{
	gameTurn = 0;
}

heroInfo heroList[designedHeroNum] = {
	{ 1, "./hero/tfns.png", 1, false },
	{ 2, "./hero/bqzs.png", 1, false },
	{ 3, "./hero/mlps.png", 1, false },
	{ 4, "./hero/qxsq.png", 2, false },
	{ 5, "./hero/wlshz.png", 2, false },
	{ 6, "./hero/yn.png", 3, false },
	{ 7, "./hero/ltzz.png", 3, false },
	{ 8, "./hero/snzx.png", 4, false }
};