#ifndef _SCENES_GAME_H_
#define _SCENES_GAME_H_

#include"AppDelegate.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "cocos-ext.h"             

#include "mainMenu/mainMenu.h"
#include"mainMenu/sceneName.h"
#include "player/playerData.h"
#include "inGameTimer/inGameTimer.h"

#include "game/mapLayer.h"
#include"game/layerPlayer.h"
#include"game/layerHero.h"
#include"shop/layerShop.h"
#include"game/layerSettings.h"
#include"aiPlayer/aiPlayer.h"
#include "hero/allheros.h"
#include "hero/smallhero.h"
#include <string>
USING_NS_CC;

#define BASICAL_HURT 5 // 基础伤害
#define EACH_CHESS_HURT 3 // 每存留一个英雄，造成两点伤害
#define CAN_BE_SELECTED 50
#define SEPARATION 20 //用于区分棋子位于战斗区还是备战区,小于为战斗区，大于为备战区

//using namespace cocos2d::extension; 

using std::string;
extern string playerName;
class sceneGame : public mainMenu
{
public:
	static sceneGame* createScene(string& userName);
	virtual bool init();
	string getUserName()const ;
	sceneGame();
	~sceneGame();

private:
	CREATE_FUNC(sceneGame);
	/***********初始化************/
	void mapInit();   // 地图初始化
	void audioInit(); // 音频初始化
	void mouseInit(); // 鼠标初始化

	/***********计时器************/
	inGameTimer* afterFight = inGameTimer::create(15);//10?
	void update(float dt);
	void startBattle(); //开始战斗
	bool battleStarted = false;

/***********鼠标操作************/
	void mouseMainEvent(); //鼠标事件
	void mouseMove(Event* event); //鼠标移动
	void mouseUp(Event* event);   //鼠标弹起
	void mouseDown(Event* event); //鼠标按下
	Point inWhichCell(const Point point) const; // 判断当前位置在哪一个棋盘格
	int chessSelected = -1; // 判断哪个棋子选中
	/***********局面************/
	void whichTurn();
	bool mouseInBattleArray(ccArray* Array, EventMouse* e);    // 判断鼠标是否在等待区
	void addHeroToWaiting(playerData& player, int playerInfo); //添加英雄到等待区
	void soldHero(playerData& player, Hero* hero, ccArray* Array); //出售英雄

	int endAlivePieces(const playerData& player) const ; //判断胜利
	void win(); //胜利触发
	void afterWin(ccArray* crtArray); //胜利后的操作

	void toBattleArray(Hero* hero, playerData& player); //英雄上阵
	void toWaitingArray(Hero* hero, playerData& player); //英雄下阵

	/***********子Layer们************/
	mapLayer* map = mapLayer::createMapLayer(); //地图层
	layerPlayer* playerLayer = layerPlayer::createPlayer(playerName); //玩家层
	layerHero* heroExist = layerHero::createLayerHero(); //英雄层
	layerShop* shopLayer = layerShop::createLayerShop(); //商店层
	layerSettings* settingsLayer = layerSettings::createLayer(); //设置层
	smallHero* myyhero;



	int gameTurn = 0; //游戏回合数
	void addTurn() { gameTurn++; }

	bool isAI = true; //是否为AI

	friend class hero;
};

#endif // !_SCENES_GAME_H_
