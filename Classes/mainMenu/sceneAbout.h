#ifndef _SCENES_ABOUT_H
#define _SCENES_ABOUT_H
#include "hero/hero.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

class sceneAbout : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void aboutBack(cocos2d::Ref* pSender);
	void playAllHeros(float dt);
	vector<Hero*> heros;
	
	CREATE_FUNC(sceneAbout);

};



#endif // !_SCENES_ABOUT_H
