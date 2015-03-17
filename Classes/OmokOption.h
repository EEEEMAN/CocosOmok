#ifndef __OMOK_OPTION_H__
#define __OMOK_OPTION_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "OmokTitleScene.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"

class OmokOption : public cocos2d::Layer
{
private:
	void onTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void setTouchEnable(bool enable);
public:
	virtual bool init();
	CREATE_FUNC(OmokOption);
};

#endif
