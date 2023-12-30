#include "game/gameData.h"
#include"game/mapLayer.h"
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
}

void gameData::initGameStart()
{
	gameTurn = 0;
}

heroInfo heroList[designedHeroNum] = {
	{ 1, "TFNS", 1, false },
	{ 2, "BQZS", 1, false },
	{ 3, "MLPS", 1, false },
	{ 4, "QXSQ", 1, false },
	{ 5, "WLSHZ", 1, false },
	{ 6, "YN", 1, false },
	{ 7, "LTZZ", 1, false },
	{ 8, "SNZX", 1, false }
};