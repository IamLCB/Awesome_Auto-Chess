#ifndef _SCENES_GAME_H_
#define _SCENES_GAME_H_

#include"AppDelegate.h"
#include "cocos2d.h"
#include "mainMenu/mainMenu.h"
#include "player/playerData.h"
#include "hero.h"
#include "AudioEngine.h"
#include "game/mapLayer.h"
#include <vector>
#include <string>
#include "cocos-ext.h"             
USING_NS_CC;

#define BASICAL_HURT 3
#define EACH_CHESS_HURT 2
#define CAN_BE_SELECTED 50
//using namespace cocos2d::extension; 

using std::string;
using std::vector;
class sceneGame : public mainMenu
{
public:
	static sceneGame* createScene(string& userName);
	virtual bool init();
	string getUserName();
	sceneGame();
	~sceneGame();

private:
	/***********计时器************/
	/*	RoundTimer* test_timer = RoundTimer::create(10);
	void update(float dt);
	void TurnInfoInit();
	CREATE_FUNC(sceneGame);
*/

	/***********鼠标操作************/
	void mouseInit(); //鼠标初始化
	void mouseMainEvent(); //鼠标事件
	void mouseMove(Event* event); //鼠标移动
	void mouseUp(Event* event);   //鼠标弹起
	void mouseDown(Event* event); //鼠标按下
	Point inWhichCell(Point point); // 判断当前位置在哪一个棋盘格
	int chessSelected = -1;
	/***********局面************/
	bool mouseInBattleArray(ccArray* Array, EventMouse* e);    // 判断鼠标是否在等待区
	void addHeroToWaiting(playerData& player, int playerInfo); //添加英雄到等待区
	void soldHero(playerData& player,Hero* hero, ccArray* Array); //出售英雄

	int endAlivePieces( playerData& player); //判断胜利
	void win(); //胜利触发
	void afterWin(ccArray* crtArray); //胜利后的操作

	void toBattleArray(Hero* hero, playerData& player); //英雄上阵
	void toWaitingArray(Hero* hero, playerData& player); //英雄下阵

	/***********子Layer们************/
	mapLayer* map = mapLayer::createMapLayer(); //地图层
	layerplayer* playerLayer = layerplayer::createPlayerLayer(); //玩家层
	layerHero* heroExist = layerHero::createHeroLayer(); //英雄层
	layerShop* shopLayer = layerShop::createShopLayer(); //商店层
	layerSettings* settingsLayer = layerSettings::createSettingsLayer(); //设置层

	int gameTurn = 0; //游戏回合数

	int equipmentSelected = -1;

	friend class hero;
};

#endif // !_SCENES_GAME_H_
