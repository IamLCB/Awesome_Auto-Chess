#ifndef _mainMenu_H_
#define _mainMenu_H_
#include "cocos2d.h"

class mainMenu : public cocos2d::Layer
{


public:
	static cocos2d::Scene* scene();

	virtual bool init();
/*
	void onAbout(cocos2d::Ref* pSender);

	void onSettings(cocos2d::Ref* pSender);

	void onButtonEffect();

	void onNewGame();

	virtual void update(float data);
	
	*/

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(mainMenu);
};






#endif // !_mainMenu_H_

