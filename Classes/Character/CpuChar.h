#ifndef __CPU_CHAR_H__
#define __CPU_CHAR_H__

#include "cocos2d.h"
#include "omok\GNode.h"
#include "GameManager.h"
#include "Stone\Stone.h"
#include <string>

class CpuChar
{
protected:
	int readTurn = 0; //몇 수 앞까지 읽는지를 정함
	int searchLength = ROW; //얼마나 넓게 읽는지를 정함
	Stone* stone = NULL; //사용하는 돌
	char* imageName = 0; //캐릭터 이미지 파일 이름
	char* name = 0; //캐릭터 이름
	CharacterID characterID; //캐릭터 고유 번호
	int winCountNormal; //이 캐릭터에게 보통룰로 이긴 횟수
	int winCountRenju; //이 캐릭터에게 렌주룰로 이긴 횟수
	int money; //이 캐릭터를 이기면 얻을 수 있는 금액
	float stoneProbability; //오목알을 얻는 확률. 0~1
public:
	CpuChar();
	~CpuChar();
	virtual int alpha_beta(GNode* state, int alpha, int beta, int length);
	virtual GAction getBestAction(GNode* state);
	virtual int utility(GNode* node) const;
	virtual int seachString(char* str) const = 0; //오목판 한줄을 검사하여 점수를 매김
	char* getStoneImageName() const; //캐릭터가 사용하는 돌의 이미지 이름을 가져옴
	char* getImageName() const; //캐릭터 이미지를 가져옴
	char* getName() const; //캐릭터 이름을 가져옴
	Stone* getStone() const; //돌 객체를 가져옴
	CharacterID getCharacterID() const;
	int getWinCountNormal() const;
	int getWinCountRenju() const;
	int getWinCount() const;
	int getMoney() const;
	void raiseWinCountNormal(); //보통 룰로 이긴 횟수를 1 증가
	void raiseWinCountRenju(); //렌주 룰로 이긴 횟수를 1 증가
	float getStoneProbability() const;
	bool searchStone(GNode* state, GAction action) const; //state에서 action의 주변 8칸에 돌이 있는지 확인
};

#endif
