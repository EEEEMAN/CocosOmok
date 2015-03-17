#ifndef __OMOK_TITLE_SCENE_H__
#define __OMOK_TITLE_SCENE_H__

#include "cocos2d.h"
#include "OmokScene.h"
#include "StageSelectScene.h"
#include "GameManager.h"
#include "OmokOption.h"
#include "AdmobHelper.h"
#include "VS2PMenu.h"

#define ORDER_TITLE_BACKGROUND 0
#define ORDER_TITLE_OPTION 100

class OmokTitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OmokTitleScene);
	void setTouchEnable(bool enable); //메뉴 버튼들의 터치 가능 여부를 바꿈
};

#endif // __OMOK_TITLE_SCENE_H__
