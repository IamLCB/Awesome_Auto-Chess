#ifndef _IN_GAME_TIMER_H_
#define _IN_GAME_TIMER_H_

#include "cocos2d.h"
USING_NS_CC;

class inGameTimer : public cocos2d::Node
{
public:
	inGameTimer() {}
	virtual ~inGameTimer() {}
	static inGameTimer* create(float time);
	bool init(float time);
	void update(float dt);
	float totalTime = 100;

private:
	cocos2d::Label* timerLabel;
	friend class sceneGame;
	friend class hero;
};

#endif // !_IN_GAME_TIMER_H_
