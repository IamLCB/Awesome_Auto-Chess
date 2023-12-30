#ifndef _SCENES_NAME_H
#define _SCENES_NAME_H

#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"
#include "ui/UIEditBox/UIEditBoxImpl.h"
#include "ui/UIHelper.h"



USING_NS_CC;
using namespace cocos2d::ui;

class sceneName :public Scene, public EditBoxDelegate
{
public:
	static Scene* createScene();
	virtual bool init();
	void returnToMenu(cocos2d::Ref* pSender);
	
	virtual void editBoxEditingDidBegin(EditBox* editBox);
	virtual void editBoxEditingDidEnd(EditBox* editBox);
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(EditBox* editBox);

	void modeAI(cocos2d::Ref* pSender);
	CREATE_FUNC(sceneName);

};



#endif // !_SCENES_NAME_H
