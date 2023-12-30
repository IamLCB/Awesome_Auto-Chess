#ifndef _DATA_PLAYER_H_
#define _DATA_PLAYER_H_

#include "cocos2d.h"
#include "game/gameData.h"

#define maxHeroNum 20		// 最大玩家英雄数量
USING_NS_CC;



class playerData : public Ref
{
private:
	/*********玩家基本信息**********/
	int playerMaxHealth = 100;					//玩家生命值
	int playerHealth = playerMaxHealth;			//玩家当前生命值
	int playerLevel = 1;						//玩家等级
	int playerExp = 0;							//玩家经验值
	int playerMoney = 10;						//玩家金钱
	int expToLevelUp = 2;						//升级所需经验值
	void calExp();								//计算经验值
	bool playerHaveNewHero = false;				//玩家是否拥有新英雄

	friend class sceneGame;
	friend class layerPlayer;
	friend class layerHero;
	friend class aiPlayer;
	friend class layerSettings;

public:
	void playerHurt(int damageBlood) { this->playerHealth -= damageBlood; }		//玩家受伤
	void updateMoneyAndExp();													//更新金钱和经验值
	void playerInit();															//玩家初始化

	/*********玩家英雄信息**********/
	ccArray* waitingArray = ccArrayNew(100);	//玩家备战阵容
	ccArray* battleArray = ccArrayNew(100);		//玩家战斗阵容
	int heroNum[maxHeroNum] = { 0 };			//玩家拥有英雄数量
	heroInfo heroForBuy[5];				//玩家可购买英雄



	/*********玩家装备信息**********/
	//ccArray* equippedArray = ccArrayNew(100);		//玩家装备阵容（已装备）
	//ccArray* unequippedArray = ccArrayNew(100);		//玩家装备背包（未装备）
	//int equippedNum = 0;							//玩家已装备装备数量

};

extern playerData myPlayerData;
extern playerData opPlayerData;


#endif // !_DATA_PLAYER_H_

