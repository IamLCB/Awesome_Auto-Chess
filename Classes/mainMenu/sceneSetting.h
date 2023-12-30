#ifndef _SCENES_SETTINGS_H_
#define _SCENES_SETTINGS_H_
#include "cocos2d.h"

class sceneSettings : public cocos2d::Scene
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();
	void settingsBack(cocos2d::Ref* pSender);

	void soundOn(cocos2d::Ref* pSender);
	void soundOff(cocos2d::Ref* pSender);

	CREATE_FUNC(sceneSettings);

};




#endif // !_SCENES_SETTINGS_H_
