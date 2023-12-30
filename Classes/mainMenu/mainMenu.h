#ifndef _mainMenu_H_
#define _mainMenu_H_
#include "cocos2d.h"

class mainMenu : public cocos2d::Scene
{


public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onNewGame(cocos2d::Ref* pSender);

	void onAbout(cocos2d::Ref* pSender);

	void onSettings(cocos2d::Ref* pSender);

	void onTest(cocos2d::Ref* pSender);

	//void onButtonEffect();


	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(mainMenu);
};






#endif // !_mainMenu_H_

