#include "./aiPlayer/aiPlayer.h"

Hero* aiPlayer::soldHero()
{
	Hero* sold = nullptr;
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		sold = static_cast<Hero*> (opPlayerData.waitingArray->arr[i]);
		if (sold->level == 1)
			return sold;
	}
	return sold;
}

void aiPlayer::judgeGold()
{
	refresh();					//刷新商店
	opPlayerData.playerMoney += 2;
	checkUpgrade();
	judgeExp();					//买经验
	if (checkLimit() && checkHighGoldHero() && opPlayerData.playerMoney >= 2)//不超过人数限制且购买了高费英雄
		refresh();//刷新商店
}

bool aiPlayer::checkUpgrade()
{
	bool ifUpgrade = false;
	for (int i = 1; i < maxHeroNum; i++)//遍历
	{
		if (opPlayerData.heroNum[i] % 3 == 2 && checkLimit())	//如果有升级条件并且不会超过人数限制
			if (aiBuy(i))	//如果能够成功买入，则返回能够升级
				ifUpgrade = true;
	}
	return ifUpgrade;
}

bool aiPlayer::checkLimit()
{
	int totalHero = opPlayerData.waitingArray->num + opPlayerData.battleArray->num;
	if (totalHero <= opPlayerData.playerLevel && opPlayerData.playerMoney > 5)
	{
		int tmpMoney = 0, tmpId = -1;
		for (int i = 0; i < 5; i++)
		{
			if (opPlayerData.heroForBuy[i].cost >= tmpMoney && opPlayerData.heroForBuy[i].buy == false)
			{
				tmpMoney = opPlayerData.heroForBuy[i].cost;
				tmpId = i;
			}
		}
		if (tmpId != -1)
			if (aiBuy(tmpId))
				return true;
			else
				return false;
	}
	return false;
}

void aiPlayer::judgeExp()
{
	int expGap = myPlayerData.playerExp - opPlayerData.playerExp;
	//?????????//while可用否？
	//while (expGap > 5 && opPlayerData.playerMoney >= 4)
	//{
	if (expGap > 5 && opPlayerData.playerMoney >= 4) {
		opPlayerData.playerMoney -= 4;
		opPlayerData.playerExp += 4;
		opPlayerData.calExp();
		expGap = myPlayerData.playerExp - opPlayerData.playerExp;
		if (opPlayerData.playerMoney < 0)
			opPlayerData.playerMoney = 0;
	}
	//}
}

bool aiPlayer::checkHighGoldHero()
{
	int tmpMoney = 0, tmpId = -1;
	for (int i = 0; i < 5; i++)
	{
		if (opPlayerData.heroForBuy[i].cost >= tmpMoney && !opPlayerData.heroForBuy[i].buy)
		{
			tmpMoney = opPlayerData.heroForBuy[i].cost;
			tmpId = i;
		}
	}
	if (aiBuy(tmpId))
		return true;
	return false;
}

bool aiPlayer::aiBuy(int id)
{
	if (opPlayerData.waitingArray->num + opPlayerData.battleArray->num < opPlayerData.playerLevel + designedHeroNum)
	{
		if (opPlayerData.playerMoney >= opPlayerData.heroForBuy[id].cost && !opPlayerData.heroForBuy[id].buy)
		{
			Hero* newHero = createHero(opPlayerData.heroForBuy[id].id);
			ccArrayAppendObject(opPlayerData.waitingArray, newHero);
			opPlayerData.playerHaveNewHero = true;
			opPlayerData.heroForBuy[id].buy = true;
			opPlayerData.playerMoney -= opPlayerData.heroForBuy[id].cost;
			opPlayerData.heroNum[id]++;
			if (opPlayerData.playerMoney < 0)
				opPlayerData.playerMoney = 0;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

void aiPlayer::refresh()
{
	int hero = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 5; i++)
	{
		hero = rand() % 7 + 1;
		opPlayerData.heroForBuy[i].buy = false;
		opPlayerData.heroForBuy[i].id = heroList[hero - 1].id;
		opPlayerData.heroForBuy[i].picName = heroList[hero - 1].picName;
		opPlayerData.heroForBuy[i].cost = heroList[hero - 1].cost;
	}
	opPlayerData.playerMoney -= 2;
	if (opPlayerData.playerMoney < 0)
		opPlayerData.playerMoney = 0;
}

void aiPlayer::creatBattleArray()
{
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		if (opPlayerData.playerLevel > 0 && opPlayerData.battleArray->num < opPlayerData.playerLevel)
		{
			ccArrayAppendObject(opPlayerData.battleArray, opPlayerData.waitingArray->arr[i]);
			ccArrayRemoveObject(opPlayerData.waitingArray, opPlayerData.waitingArray->arr[i]);
		}
	}
	for (int j = opPlayerData.battleArray->num; j < opPlayerData.playerLevel; j++)
	{
		ccArrayAppendObject(opPlayerData.battleArray, opPlayerData.waitingArray->arr[j]);
		ccArrayRemoveObject(opPlayerData.waitingArray, opPlayerData.waitingArray->arr[j]);
	}
}

aiPlayer AIPlayer;