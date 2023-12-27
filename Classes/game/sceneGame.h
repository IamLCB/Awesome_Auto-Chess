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
	/***********��ʱ��************/
	/*	RoundTimer* test_timer = RoundTimer::create(10);
	void update(float dt);
	void TurnInfoInit();
	CREATE_FUNC(sceneGame);
*/

	/***********������************/
	void mouseInit(); //����ʼ��
	void mouseMainEvent(); //����¼�
	void mouseMove(Event* event); //����ƶ�
	void mouseUp(Event* event);   //��굯��
	void mouseDown(Event* event); //��갴��
	Point inWhichCell(Point point); // �жϵ�ǰλ������һ�����̸�
	int chessSelected = -1;
	/***********����************/
	bool mouseInBattleArray(ccArray* Array, EventMouse* e);    // �ж�����Ƿ��ڵȴ���
	void addHeroToWaiting(playerData& player, int playerInfo); //���Ӣ�۵��ȴ���
	void soldHero(playerData& player,Hero* hero, ccArray* Array); //����Ӣ��

	int endAlivePieces( playerData& player); //�ж�ʤ��
	void win(); //ʤ������
	void afterWin(ccArray* crtArray); //ʤ����Ĳ���

	void toBattleArray(Hero* hero, playerData& player); //Ӣ������
	void toWaitingArray(Hero* hero, playerData& player); //Ӣ������

	/***********��Layer��************/
	mapLayer* map = mapLayer::createMapLayer(); //��ͼ��
	layerplayer* playerLayer = layerplayer::createPlayerLayer(); //��Ҳ�
	layerHero* heroExist = layerHero::createHeroLayer(); //Ӣ�۲�
	layerShop* shopLayer = layerShop::createShopLayer(); //�̵��
	layerSettings* settingsLayer = layerSettings::createSettingsLayer(); //���ò�

	int gameTurn = 0; //��Ϸ�غ���

	int equipmentSelected = -1;

	friend class hero;
};

#endif // !_SCENES_GAME_H_
