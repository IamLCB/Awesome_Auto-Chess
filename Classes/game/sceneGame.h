#ifndef _SCENES_GAME_H_
#define _SCENES_GAME_H_

#include"AppDelegate.h"
#include "cocos2d.h"
#include "AudioEngine.h"
#include "cocos-ext.h"             

#include "mainMenu/mainMenu.h"
#include"mainMenu/sceneName.h"
#include "player/playerData.h"
#include"inGameTimer.h"

#include "game/mapLayer.h"
#include"game/layerPlayer.h"
//#include"game/layerHero.h"
#include"shop/shopCreate.h"
#include"game/layerSettings.h"

#include "hero.h"
#include <string>
USING_NS_CC;

#define BASICAL_HURT 3 // �����˺�
#define EACH_CHESS_HURT 2 // ÿ����һ��Ӣ�ۣ���������˺�
#define CAN_BE_SELECTED 50
#define SEPARATION 20 //������������λ��ս�������Ǳ�ս��,С��Ϊս����������Ϊ��ս��
string name;  // ����ǳ�

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
	/***********��ʼ��************/
	void mapInit();   // ��ͼ��ʼ��
	void audioInit(); // ��Ƶ��ʼ��
	void mouseInit(); // ����ʼ��

	/***********��ʱ��************/
	inGameTimer* afterFight = inGameTimer::create(10);//10?
	void update(float dt);

/***********������************/
	void mouseMainEvent(); //����¼�
	void mouseMove(Event* event); //����ƶ�
	void mouseUp(Event* event);   //��굯��
	void mouseDown(Event* event); //��갴��
	Point inWhichCell(const Point point) const; // �жϵ�ǰλ������һ�����̸�
	int chessSelected = -1; // �ж��ĸ�����ѡ��
	/***********����************/
	void whichTurn();
	bool mouseInBattleArray(ccArray* Array, EventMouse* e);    // �ж�����Ƿ��ڵȴ���
	void addHeroToWaiting(playerData& player, int playerInfo); //���Ӣ�۵��ȴ���
	void soldHero(playerData& player, Hero* hero, ccArray* Array); //����Ӣ��

	int endAlivePieces(const playerData& player) const ; //�ж�ʤ��
	void win(); //ʤ������
	void afterWin(ccArray* crtArray); //ʤ����Ĳ���

	void toBattleArray(Hero* hero, playerData& player); //Ӣ������
	void toWaitingArray(Hero* hero, playerData& player); //Ӣ������

	/***********��Layer��************/
	mapLayer* map = mapLayer::createMapLayer(); //��ͼ��
	layerPlayer* playerLayer = layerPlayer::createPlayer(playerName); //��Ҳ�
	layerHero* heroExist = layerHero::createHeroLayer(); //Ӣ�۲�
	shopCreate* shopLayer = shopCreate::createShop(); //�̵��
	layerSettings* settingsLayer = layerSettings::createLayer(); //���ò�

	int gameTurn = 0; //��Ϸ�غ���
	void addTurn() { gameTurn++; }

	friend class hero;
};

#endif // !_SCENES_GAME_H_