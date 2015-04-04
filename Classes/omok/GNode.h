#ifndef __GNODE_H__
#define __GNODE_H__

#define ROW 15 //오목판 가로,세로 길이
#define READ_TURN 0  //CPU가 탐색할 수의 깊이
#define g_max(a,b) (a>b)?a:b
#define g_min(a,b) (a<b)?a:b
#define INF 9999

#include "GAction.h"
#include "GameManager.h"
#include <vector>
#include <string>

class GNode
{
public:
	GState state[ROW][ROW]; //state[y][x]
	std::vector<GAction> actionList; //cpu가 둘 수 있는 수 집합
private:
	int stoneNum; //놓여있는 총 돌의 수
	GAction didAction; //이 상태가 되기 위해 놓은 수
public:
	GNode();
	GNode(GNode *T);

	bool isTerminal(); // 종료상태인지 검사
	bool isSsangsam(); //쌍삼인지 검사
	GNode* result(GAction action); // action을 적용시킨 상태를 반환
	bool isPlayer(); // 다음이 플레이어의 차례면 참, CPU차례면 거짓
	void doAction(GAction action); // action을 적용
	int getTurn() const; //경과 턴을 반환
	GAction getAction() const; //마지막 액션(didAction)을 반환
	std::vector<GAction> getTerminalAction() const; //종료상태로 만든 5알을 vector에 담아서 반환
	bool searchAction(GAction action) const; //action이 이미 actionList에 있으면 true
	bool searchAction(int x, int y) const;
private:
	char stateToChar(int x, int y); //x,y좌표에 있는 상태를 char로 변환하여 반환
	bool search33Pattern(char* str); //문자열로 변환한 상태에서 쌍삼이 될만한 패턴을 찾는다.
	bool search44Pattern(char* str); //문자열로 변환한 상태에서 쌍사가 될만한 패턴을 찾는다.
	bool search6mokPattern(char* str); //문자열로 변환한 상태에서 육목이 되는 패턴을 찾는다.
};

#endif
