#include "playerData.h"

playerData myPlayerData;
playerData opPlayerData;

void playerData::updateMoneyAndExp()
{
	this->playerMoney = this->playerMoney + std::min(this->playerMoney / 10 + 5, 12); // 玩家金钱增加
	this->playerExp += 2; // 玩家经验增加
	this->calExp();

}

void playerData::calExp()
{
	for (int i = 0; i < 100; i++)
	{
		int thisLevelExp = i * i * i * 2 / 5 + 2 * i;
		int nextLevelExp = (i + 1) * (i + 1) * (i + 1) * 2 / 5 + 2 * (i + 1);
		if (this->playerExp >= thisLevelExp && this->playerExp < nextLevelExp)
		{
			this->playerLevel = i + 1;
			this->expToLevelUp = nextLevelExp;
			return;
		}
	}
	return;
}

void playerData::playerInit()
{
	this->battleArray = ccArrayNew(100);
	this->waitingArray = ccArrayNew(100);
	this->playerMaxHealth = 100;
	this->playerHealth = this->playerMaxHealth;
	this->playerLevel = 1;
	this->playerExp = 0;
	this->playerMoney = 10;
	this->expToLevelUp = 2;
	for (int i = 0; i < maxHeroNum; i++) this->heroNum[i] = 0;
}