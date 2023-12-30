#ifndef _SCENES_LOADING_H_
#define _SCENES_LOADING_H_
#include "cocos2d.h"
USING_NS_CC;

class sceneLoading : public Scene
{
private:
	int totalResources;
	int loadedResources;
	ProgressTimer* loadingBar;
public:
	static sceneLoading* createScene();
	virtual bool init();
	void loadResources();
	void loadingCallBack(Texture2D* texture);

	CREATE_FUNC(sceneLoading);
};


#endif // !_SCENES_LOADING_H_
