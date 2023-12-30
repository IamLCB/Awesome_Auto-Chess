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
	/***********��ʱ��************/


	/***********������************/
	void mouseInit(); //����ʼ��
	void mouseMainEvent(); //����¼�
	void mouseMove(Event* event); //����ƶ�
	void mouseDown(Event* event); //��갴��
	void mouseUP(Event* event); //���̧��
	bool vagueMouseTarget(ccArray* Array, EventMouse* event); //���ģ��ѡȡ

	/***********����************/
	void addHeroToWaiting(playerData& player, int playerInfo); //���Ӣ�۵���ս��
	void soldHero(playerData& player, int playerInfo); //����Ӣ��

	void win(); //ʤ������
	bool isWin(); //�ж�ʤ��
	void afterWin(); //ʤ����Ĳ���

	void toBattleArray(Hero* hero, playerData& player); //Ӣ������
	void toWaitingArray(Hero* hero, playerData& player); //Ӣ������

	/***********��Layer��************/

	/*layerMap* mapLayer = layerMap::createMapLayer(); //��ͼ��
	layerplayer* playerLayer = layerplayer::createPlayerLayer(); //��Ҳ�
	layerHero* heroLayer = layerHero::createHeroLayer(); //Ӣ�۲�
	layerShop* shopLayer = layerShop::createShopLayer(); //�̵��
	layerSettings* settingsLayer = layerSettings::createSettingsLayer(); //���ò�
*/
	int gameTurn = 0; //��Ϸ�غ���

	friend class hero;


};

#endif // !_SCENES_GAME_H_
