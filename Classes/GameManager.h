#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "OmokDefine.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include <algorithm>
#include <random>
#include "Stone\Stone.h"
#include "Stone\Stone_Black.h"
#include "Stone\Stone_Cross.h"
#include "Stone\Stone_Fish.h"
#include "Stone\Stone_Ori.h"
#include "Stone\Stone_Sock.h"
#include "Stone\Stone_Ketchup.h"
#include "Stone\Stone_Ojing.h"
#include "Stone\Stone_Crab.h"

class GameManager
{
private:
	GameManager();
	GameManager(const GameManager &T){}
	GameManager &operator=(const GameManager &other){}
public:
	static GameManager& getInstance();
	float getRandom_0_1() const;
	void setSceneState(SceneState state);
	SceneState getSceneState() const;
	Stone* getCurrentStone() const;
	void setCurrentStone(Stone* stone);
	Stone* getStoneByID(StoneID id) const;
	bool addStone(StoneID id);
	int getMyMoney() const;
	bool setMyMoney(int money); //소지금을 money만큼 증가/감소. 성공하면 true를 리턴
	int getWinCountNormal(CharacterID id) const; //id에 해당하는 캐릭터를 일반룰로 이긴 횟수를 리턴
	int getWinCountRenju(CharacterID id) const; //id에 해당하는 캐릭터를 렌주룰로 이긴 횟수를 리턴
	int getWinCount(CharacterID id) const; //id에 해당하는 캐릭터를 이긴 횟수를 리턴 (일반룰 + 렌주룰)

	bool isRule33() const;
	bool isRule44() const;
	bool isRule6mok() const;
	bool isRuleRenju() const;
	void setRule33(bool s);
	void setRule44(bool s);
	void setRule6mok(bool s);
	void setRuleRenju(bool s);
private:
	int myMoney; //플레이어의 소지금
	SceneState currentScene; //현재 화면 상태
	bool rule33; //쌍삼금지면 true
	bool rule44; //쌍사금지면 true
	bool rule6mok; //육목금지면 true
	bool ruleRenju; //렌주룰이면 true
public:
	CocosDenshion::SimpleAudioEngine* sound; //소리 관련
	std::vector<StoneID> stoneList;
private:
	Stone* currentStone;
};

#endif