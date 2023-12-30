#ifndef _SCENES_TEST_H
#define _SCENES_TEST_H
#include "hero/hero.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

class sceneTest : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void aboutBack(cocos2d::Ref* pSender);
	void playAllHeros(float dt);
	vector<Hero*> heros;

	CREATE_FUNC(sceneTest);

};



#endif // !_SCENES_ABOUT_H
