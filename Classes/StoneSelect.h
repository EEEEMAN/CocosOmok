#ifndef __STONE_SELECT_H__
#define __STONE_SELECT_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "OmokTitleScene.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "Stone\Stone.h"

class StoneSelect : public cocos2d::Layer
{
private:
	void onTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
	void addStone(Stone* stone);
public:
	virtual bool init();
	CREATE_FUNC(StoneSelect);
};

#endif __STONE_SELECT_H__