#ifndef __OMOK_DEFINE_H__
#define __OMOK_DEFINE_H__

enum SceneState{
	SCENE_OMOK,
	SCENE_STAGESELECT,
	SCENE_TITLE
};

enum CharacterID{
	CHAR_OMOK = 0, //오징어목사
	CHAR_MYEOLCHI = 1, //멸치
	CHAR_ORI = 2, //오리
	CHAR_JANGGAB = 3, //장갑
	CHAR_KETCHUP = 4, //케찹
	CHAR_OJING = 5, //오징어
	CHAR_CRAB = 6 //게
};

enum StoneID{ //새로운 돌을 추가할 때 여기에 돌 ID를 추가하고 GameManager의 getStoneID함수도 수정해야함
	BLACK_AND_WHITE = 0, //오목알
	CROSS = 1, //십자가
	FISH = 2, //물고기
	ORIBAL = 3, //오리발
	SOCK = 4, //양말
	KETCHUP = 5, //케찹
	OJING = 6, //오징어
	CRAB_HAND = 7 //집게발
};

enum GState
{
	S_BLACK,  //흑돌
	S_WHITE,  //백돌
	S_EMPTY  //빈공간
};

#define POSITION_CENTER Vec2(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2)
#define ANCHER_CENTER Vec2(0.5,0.5)

//게임 진행데이터 저장
#define DATA_INT_CURRENTSTONE "currentStone" //장착중인 돌 ID
#define DATA_STRING_STONELIST "stoneList" //획득한 돌들의 id를 string으로 나열하여 저장. "|"가 구분자
#define DATA_INT_WINCOUNT_NORMAL "winCountNormal_" //보통룰로 이긴 횟수. 뒤에 캐릭터별 ID를 붙여서 사용
#define DATA_INT_WINCOUNT_RENJU "winCountRenju_" //렌주룰로 이긴 횟수
#define DATA_INT_STAGE_SELECT_PAGEINDEX "stageSelectPageIndex" //스테이지선택창의 현제페이지를 기억
#define DATA_INT_MYMONEY "myMoney" //소지금

//옵션 데이터 저장
#define OPTION_BOOL_INITED "inited" //처음시작할땐 false
#define OPTION_FLOAT_BGM "BGM"
#define OPTION_FLOAT_EFFECT "Efect"
#define OPTION_BOOL_RULE33 "isRule33"
#define OPTION_BOOL_RULE44 "isRule44"
#define OPTION_BOOL_RULE6MOK "isRule6mok"
#define OPTION_BOOL_RULERENJU "isRuleRenju"

//사운드파일 경로
#define BGM_TITLE "Sounds/Payday.mp3" //타이틀 화면
#define BGM_GAMESCENE "Sounds/Mr._Turtle.mp3" //오목게임중에 나오는 음악
#define EFFECT_SELECT "Sounds/effect_select.mp3" //선택 효과음
#define EFFECT_GAMEOVER "Sounds/effect_ice.wav" //게임이 끝나면 나는 소리
#define EFFECT_WARNING "Sounds/effect_change.mp3" //경고음
#define EFFECT_DOACTION "Sounds/effect_tac.mp3" //돌을 둘 때 나는 소리
#define EFFECT_CANCEL "Sounds/effect_cancel.mp3" //취소 효과음

#endif