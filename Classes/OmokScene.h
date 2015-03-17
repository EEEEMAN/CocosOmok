#ifndef __OMOK_SCENE_H__
#define __OMOK_SCENE_H__

#define TAG_CURSOR 1004 //터치된 곳을 표시하는 커서의 태그번호
#define TAG_LASTACTION 1005 //마지막으로 돌은 둔 곳을 표시하는 커서의 태그번호

#define STONE_SIZE 25 //바둑알 크기

#define ORDER_STAGE 100 //바둑판
#define ORDER_STAGE_ARROW 300 //바둑판 위 돌을 강조할때 쓰이는 테두리
#define ORDER_STAGE_STONE 200 //바둑판 위 돌
#define ORDER_STATUSBAR 300 //상태창
#define ORDER_GAMEOVER 400 //게임이 끝났을때 나오는 이미지
#define ORDER_MESSAGEBOX 500 //메시지박스

#include "cocos2d.h"
#include "StageSelectScene.h"
#include "OmokTitleScene.h"
#include "omok/GNode.h"
#include "Character/CpuChar.h"
#include "GameManager.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"
#include <thread>
#include "AdmobHelper.h"

class OmokScene : public cocos2d::LayerColor
{
private: //함수
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void msgBoxTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	cocos2d::Vec2 convertGActionToPos(GAction action) const; //GAction을 화면상의 좌표로 변환
	GAction convertPosToGAction(cocos2d::Vec2 vec2) const; //Vec2를 GAction으로 변환 반환된 GAction의 x,y값이 -1이면 없는값임
	void showGameOverAnimation(); //게임이 끝났을때의 애니메이션을 처리
	void showLastAction(); //마지막으로 둔 돌을 표시
	void closeGame(); //게임을 끝내고 이전창으로 돌아감
	void checkTurn(); //상태바의 돌을 현제턴에 맞게 바꿈
	void selfRemover(Node* sender); //자기자신을 자우는 함수
	void setEnemy(CpuChar* enemy);
	cocos2d::Sprite* getActionSprite(GAction action); // action을 위치를 계산한 돌Sprite를 반환
public:
	static void startGame(CpuChar* enemyChar); //enemyChar를 상대로 게임을 시작함
	static void startGame(char* stone1P, char* stone2P); //2p게임을 시작함
	virtual bool init();
	void initStatusBar();
	CREATE_FUNC(OmokScene);
	void cpuThread();

	void doAction(GAction action);
	void checkGameOver(); //게임이 끝났는지 검사하고 끝났다면 상황에따라 처리함

private: //변수
	cocos2d::Size winSize;  //화면 크기

	GNode* gameState;
	cocos2d::Sprite* backGround; //바둑판
	bool isVsCPU = false; //혼자하기면 true, 둘이서하기면 false
	bool isTouched = false; //터치중이면 true
	bool isMessageBoxVisible = false; //메시지박스가 나와있으면 true
	GAction selectedPoint; //선택된 좌표를 저장

	CpuChar* enemy = NULL; //적캐릭터
	cocos2d::EventListenerTouchOneByOne* listener; //터치 리스너

	cocos2d::Node* status; //상태창
	cocos2d::Sprite* statusStone[2]; //상태창에 있는 현재차례를 나타내는 돌 이미지
	cocos2d::Node* statusCharacter; //상태창에 있는 적캐릭터 이미지
	cocos2d::Node* statusThink; //상태창의 cpu가 생각중인것을 표시하는 아이콘

	cocos2d::Node* arrowLastStone; //마지막으로 둔 돌을 가리키는 화살표
	cocostudio::timeline::ActionTimeline* arrowAnim; //화살표 애니메이션

	//2p전일 경우 1p와 2p의 돌 이미지 이름
	char* stoneName1P = 0;
	char* stoneName2P = 0;
public:
	GAction cpuAnswer; //cpu의 답
};

#endif
