#ifndef _LAYERS_SETTINGS_H_
#define _LAYERS_SETTINGS_H_

#include "cocos2d.h"
#include "mainMenu/mainMenu.h"
#include "player/playerData.h"
USING_NS_CC;

class layerSettings : public cocos2d::Layer
{
public:
	virtual bool init();
	static layerSettings* createLayer();
	void onBack(cocos2d::Ref* pSender);

	CREATE_FUNC(layerSettings);
};



#endif // !_LAYERS_SETTINGS_H_
