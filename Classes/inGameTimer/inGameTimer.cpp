#include "inGameTimer/inGameTimer.h"
#include "AppDelegate.h"

bool inGameTimer::init(float time)
{
	totalTime = time;
	timerLabel = Label::createWithTTF("0", "fonts/Marker Felt.ttf", 24);
	timerLabel->setPosition(200,200);
	this->addChild(timerLabel);
	this->scheduleUpdate();//update the timer
	return true;
}

void inGameTimer::update(float dt)
{
	totalTime -= dt;
	char* displayTime = new char[10];
	sprintf(displayTime, "%02d : %02d", (int)totalTime / 60, (int)totalTime % 60);
	timerLabel->setString(displayTime);
}

inGameTimer* inGameTimer::create(float time)
{
	inGameTimer* gameTimer = new inGameTimer;
	if (gameTimer && gameTimer->init(time))
	{
		gameTimer->autorelease();
		return gameTimer;
	}
	else
	{
		delete gameTimer;
		gameTimer = nullptr;
		return nullptr;
	}
}