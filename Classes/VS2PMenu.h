#ifndef __VS2PMENU_H__
#define __VS2PMENU_H__

#include "cocos2d.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "StoneSelect.h"

USING_NS_CC;

class VS2PMenu : public cocos2d::Layer
{
private:
	void onTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
public:
	bool isWaiting1pSel() const;
	bool isWaiting2pSel() const;
	virtual bool init();
	CREATE_FUNC(VS2PMenu);
	void setTouchEnable(bool enable);
	void set1PStone(char* imgName);
	void set2PStone(char* imgName);
private:
	bool waiting1pSel; //1p의 돌 선택을 기다리는중이면 true
	bool waiting2pSel; //2p의 돌 선택을 기다리는중이면 true
	char* stoneName1P;
	char* stoneName2P;
};

#endif