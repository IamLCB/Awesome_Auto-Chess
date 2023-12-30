#ifndef _SCENES_GAME_H_
#define _SCENES_GAME_H_

#include "cocos2d.h"
#include "mainMenu/mainMenu.h"
#include "player/playerData.h"
#include "hero/hero.h"
#include "AudioEngine.h"
#include <vector>
#include <string>
USING_NS_CC;
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


	/***********鼠标操作************/
	void mouseInit(); //鼠标初始化
	void mouseMainEvent(); //鼠标事件
	void mouseMove(Event* event); //鼠标移动
	void mouseDown(Event* event); //鼠标按下
	void mouseUP(Event* event); //鼠标抬起
	bool vagueMouseTarget(ccArray* Array, EventMouse* event); //鼠标模糊选取

	/***********局面************/
	void addHeroToWaiting(playerData& player, int playerInfo); //添加英雄到备战区
	void soldHero(playerData& player, int playerInfo); //出售英雄

	void win(); //胜利触发
	bool isWin(); //判断胜利
	void afterWin(); //胜利后的操作

	void toBattleArray(Hero* hero, playerData& player); //英雄上阵
	void toWaitingArray(Hero* hero, playerData& player); //英雄下阵

	/***********子Layer们************/

	/*layerMap* mapLayer = layerMap::createMapLayer(); //地图层
	layerplayer* playerLayer = layerplayer::createPlayerLayer(); //玩家层
	layerHero* heroLayer = layerHero::createHeroLayer(); //英雄层
	layerShop* shopLayer = layerShop::createShopLayer(); //商店层
	layerSettings* settingsLayer = layerSettings::createSettingsLayer(); //设置层
*/
	int gameTurn = 0; //游戏回合数

	friend class hero;


};

#endif // !_SCENES_GAME_H_
