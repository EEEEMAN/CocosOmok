#ifndef __STAGE_SELECT_SCENE_H__
#define __STAGE_SELECT_SCENE_H__

#include "cocos2d.h"
#include "OmokScene.h"
#include "OmokTitleScene.h"
#include "Character\CpuChar.h"
#include "GameManager.h"
#include "ui\CocosGUI.h"
#include "cocostudio\CocoStudio.h"
#include "AdmobHelper.h"
#include "StoneSelect.h"

#include "Character\CpuOmok.h"
#include "Character\CpuMyeolchi.h"
#include "Character\CpuOri.h"
#include "Character\CpuJanggab.h"
#include "Character\CpuKetchup.h"
#include "Character\CpuOjing.h"
#include "Character\CpuCrab.h"

#include <vector>

#define ORDER_STAGESELECT_BACKGROUND 0
#define ORDER_STAGESELECT_CHANGESTONE 100

USING_NS_CC;

class StageSelectScene : public cocos2d::Layer
{
private:
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void btnTouch(cocos2d::Ref* sender, ui::Widget::TouchEventType type);
	void startStage(); //선택한 적캐릭터와 게임을 시작함
	void addCharacter(CpuChar*ch); //캐릭터선택창에 캐릭터 추가
	void goToTitleScene(); //타이틀화면으로
	void setCharName(); //CC_CALLBACK_0으로 호출하는 캐릭터이름부분은 갱신하는 함수
	void saveStagePos() const; //캐릭터 선택 화면에서 커서 위치를 저장
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(StageSelectScene);
	void updateCurrentStone(); //현재 장착중인 돌을 갱신
	void updateMyMoney(); //현제 소지금 갱신
	void setTouchEnable(bool enable); //화면 터치 가능 여부 설정
private:
	std::vector<CpuChar*> charList;
};

#endif
