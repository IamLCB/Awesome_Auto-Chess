#ifndef _SCENES_ABOUT_H
#define _SCENES_ABOUT_H

#include "cocos2d.h"

class sceneAbout : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void aboutBack(cocos2d::Ref* pSender);
	
	CREATE_FUNC(sceneAbout);

};



#endif // !_SCENES_ABOUT_H
