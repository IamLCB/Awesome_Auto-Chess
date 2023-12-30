#include "game/layerHero.h"

layerHero* layerHero::createLayerHero()
{
	auto temp = layerHero::create();
	temp->retain();
	return temp;
}
void layerHero::playerArrayInit(ccArray* Array, int playerInfo)
{
	for (int i = 0; i < Array->num; i++)
	{
		auto temp = static_cast<Hero*>(Array->arr[i]);
		temp->setPosition(temp->getTempPosition());
		temp->set(temp->getTempPosition());

		auto temp1 = createHero(temp->getType());
		if (playerInfo == 0) 
		{
			temp1->setPosition(temp->getTempPosition());
			temp1->set(temp->getTempPosition());
			temp1->setTempPosition();
		}
		else
		{
			temp1->setPosition(temp->getTempPosition());
			temp1->set(temp->getTempPosition());
			temp1->setTempPosition();
			temp1->setPosition(10000, 10000);
			temp1->set(10000, 10000);
		}
		temp1->setPlayer(temp1->ofPlayer);
		if(ccArrayContainsObject(Array,temp))
			ccArrayRemoveObject(Array, temp);
		ccArrayInsertObjectAtIndex(Array, temp1, i);
		this->addChild(temp1);
		haveChess[pairReturn(temp->getTempPosition()).x][pairReturn(temp->getTempPosition()).y] = 1;

	}
}

bool layerHero::init()
{
	playerArrayInit(myPlayerData.waitingArray, 0);
	playerArrayInit(opPlayerData.battleArray, 1);
	playerArrayInit(myPlayerData.battleArray, 0);
	playerArrayInit(opPlayerData.battleArray, 1);

	return true;
}

void layerHero::update(float dt)
{
	for (int i = 0; i < myPlayerData.battleArray->num; i++) 
	{
		(static_cast<Hero*>(myPlayerData.battleArray->arr[i]))->isDead();
	}
	for (int i = 0; i < opPlayerData.battleArray->num; i++)
	{
		(static_cast<Hero*>(opPlayerData.battleArray->arr[i]))->isDead();
	}
}

void layerHero::heroUpgrade(playerData& pData)
{
	//for (int i = 0; i < 18; i++)
	//	{
	//		Hero* temp[3] = { nullptr,nullptr,nullptr };
	//		ccArray* tempArray[3] = {};
	//		int s = 0; //三个待升级棋子
	//		if (pData.heroNum[i] >= 3 && i < 18)
	//		{
	//			for (int j = 0; j < pData.waitingArray->num; j++)
	//			{
	//				if ((static_cast<Hero*>(pData.waitingArray->arr[j]))->getType() == i)
	//				{
	//					if (s < 3)
	//					{
	//						temp[s] = static_cast<Hero*> (pData.waitingArray->arr[j]);
	//						tempArray[s] = pData.waitingArray;
	//						s++;
	//					}
	//					if (s == 3)
	//						break;
	//				}
	//			}
	//			if (s < 3)
	//			{
	//				for (int j = 0; j < pData.battleArray->num; j++)
	//				{
	//					if ((static_cast<Hero*>(pData.battleArray->arr[j]))->getType() == i)
	//					{
	//						if (s < 3)
	//						{
	//							temp[s] = static_cast<Hero*> (pData.battleArray->arr[j]);
	//							tempArray[s] = pData.battleArray;
	//							s++;
	//						}
	//						if (s == 3)
	//							break;

	//					}
	//				}
	//			}
	//			/**/
	//		}
	//	}
}
Hero* layerHero::upgradeHeroInit(int type) {
	return nullptr;
}

/*PC_Player相关*/
void layerHero::aiShowWaitingArray()
{
	for (int i = 0; i < opPlayerData.waitingArray->num; i++)
	{
		static_cast<Hero*>(opPlayerData.waitingArray->arr[i])->setPosition(chessMap[7][i].x, chessMap[7][i].y);
		static_cast<Hero*>(opPlayerData.waitingArray->arr[i])->set(chessMap[7][i].x, chessMap[7][i].y);
	}
}
void layerHero::aiShowBattleArray()
{
	/*位置初始化*/
	for (int i = 0; i < opPlayerData.battleArray->num; i++)
	{
		if (i >= 0 && i <= 7) // 每行八个
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[4][i].x, chessMap[4][i].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->set(chessMap[4][i].x, chessMap[4][i].y);
			haveChess[4][i] = 1;
		}
		else if (i >= 8 && i <= 15)
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[5][i - 8].x, chessMap[5][i - 8].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->set(chessMap[5][i - 8].x, chessMap[5][i - 8].y);
			haveChess[5][i - 8] = 1;
		}
		else if (i >= 16 && i <= 23)
		{
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[6][i - 16].x, chessMap[6][i - 16].y);
			static_cast<Hero*>(opPlayerData.battleArray->arr[i])->setPosition(chessMap[6][i - 16].x, chessMap[6][i - 16].y);
			haveChess[6][i - 16] = 1;
		}
		// 只有最多三行
	}

}

float layerHero::calDistance(Hero* h1, Hero* h2)
{
	return sqrt(pow((h1->getPosition().x - h2->getPosition().x), 2)
		+ pow((h1->getPosition().y - h2->getPosition().y), 2));
}
float layerHero::calDistance(Point p1, Point p2)
{
	return sqrt(pow((p1.x - p2.x), 2)
		+ pow((p1.y - p2.y), 2));
}