#include "GNode.h"
#include <math.h>
#include "cocos2d.h"

USING_NS_CC;

GNode::GNode()
{
	stoneNum = 0;
	for (int y = 0; y < ROW; y++){
		for (int x = 0; x < ROW; x++){
			state[y][x] = S_EMPTY;
		}
	}
}

GNode::GNode(GNode *T)
{
	this->stoneNum = T->stoneNum;
	this->didAction.x = T->didAction.x;
	this->didAction.y = T->didAction.y;
	for (int y = 0; y < ROW; y++){
		for (int x = 0; x < ROW; x++){
			this->state[y][x] = T->state[y][x];
		}
	}
}

bool GNode::isTerminal(){
	int count = 0;
	int i = 1;
	auto checkCount = ([&](int count){
		//렌주룰일경우
		if (GameManager::getInstance().isRuleRenju()){
			if (this->getTurn() * 2 == 1){ //마지막에둔돌이 1p일경우
				if (count == 4){
					return true;
				}
			}
			else{ //마지막에둔돌이 2p일경우
				if (count >= 4){
					return true;
				}
			}
		}
		else{
			if (GameManager::getInstance().isRule6mok()){
				if (count == 4){
					return true;
				}
			}
			else{
				if (count >= 4){
					return true;
				}
			}
		}
		return false;
	});
	//가로 검사
	while (didAction.x + i < ROW && state[didAction.y][didAction.x + i] == state[didAction.y][didAction.x]){
		count++;
		i++;
	}
	i = 1;
	while (didAction.x - i >= 0 && state[didAction.y][didAction.x - i] == state[didAction.y][didAction.x]){
		count++;
		i++;
	}
	if (checkCount(count)) return true;

	//세로 검사
	count = 0;
	i = 1;
	while (didAction.y + i < ROW && state[didAction.y + i][didAction.x] == state[didAction.y][didAction.x]){
		count++;
		i++;
	}
	i = 1;
	while (didAction.y - i >= 0 && state[didAction.y - i][didAction.x] == state[didAction.y][didAction.x]){
		count++;
		i++;
	}
	if (checkCount(count)) return true;

	//73대각선 검사
	count = 0;
	i = 1;
	while (didAction.x + i < ROW
		&& didAction.y + i < ROW
		&& state[didAction.y + i][didAction.x + i] == state[didAction.y][didAction.x]){ //3방향
		count++;
		i++;
	}
	i = 1;
	while (didAction.x - i >= 0
		&& didAction.y - i >= 0
		&& state[didAction.y - i][didAction.x - i] == state[didAction.y][didAction.x]){ //7방향
		count++;
		i++;
	}
	if (checkCount(count)) return true;

	//91대각선 검사
	count = 0;
	i = 1;
	while (didAction.x - i >= 0
		&& didAction.y + i < ROW
		&& state[didAction.y + i][didAction.x - i] == state[didAction.y][didAction.x]){ //1방향
		count++;
		i++;
	}
	i = 1;
	while (didAction.x + i < ROW
		&& didAction.y - i >= 0
		&& state[didAction.y - i][didAction.x + i] == state[didAction.y][didAction.x]){ //9방향
		count++;
		i++;
	}
	if (checkCount(count)) return true;

	return false;
}

char GNode::stateToChar(int x, int y){
	if (x < 0 || x >= ROW || y < 0 || y >= ROW){
		return '?';
	}
	switch (state[y][x]){
	case S_BLACK:
		return 'x';
		break;
	case S_WHITE:
		return 'o';
		break;
	case S_EMPTY:
		return '-';
		break;
	default:
		return '?';
		break;
	}
}

bool GNode::search33Pattern(char* str){
	if (!GameManager::getInstance().isRule33()) return false;
	if (!isPlayer()){ //플레이어의 쌍삼 체크
		if (strstr(str, "--xxx-")){
			return true;
		}
		if (strstr(str, "-xxx--")){
			return true;
		}
		if (strstr(str, "-xx-x-")){
			return true;
		}
		if (strstr(str, "-x-xx-")){
			return true;
		}
	}
	else{ //cpu의 쌍삼 체크
		if (GameManager::getInstance().isRuleRenju()){ //렌주룰이면 체크안함
			return false;
		}
		if (strstr(str, "-ooo--")){
			return true;
		}
		if (strstr(str, "--ooo-")){
			return true;
		}
		if (strstr(str, "-oo-o-")){
			return true;
		}
		if (strstr(str, "-o-oo-")){
			return true;
		}
	}
	return false;
}

bool GNode::search44Pattern(char* str){
	if (!GameManager::getInstance().isRule44()) return false;
	if (!isPlayer()){
		if (strstr(str, "-xxxx")){
			return true;
		}
		if (strstr(str, "xxx-x")){
			return true;
		}
		if (strstr(str, "xx-xx")){
			return true;
		}
		if (strstr(str, "x-xxx")){
			return true;
		}
		if (strstr(str, "xxxx-")){
			return true;
		}
	}
	else{
		if (GameManager::getInstance().isRuleRenju()){ //렌주룰이면 체크안함
			return false;
		}
		if (strstr(str, "-oooo")){
			return true;
		}
		if (strstr(str, "ooo-o")){
			return true;
		}
		if (strstr(str, "oo-oo")){
			return true;
		}
		if (strstr(str, "o-ooo")){
			return true;
		}
		if (strstr(str, "oooo-")){
			return true;
		}
	}
	return false;
}

bool GNode::search6mokPattern(char* str){
	if (!GameManager::getInstance().isRule6mok()) return false;
	if (!isPlayer()){
		if (strstr(str, "xxxxxx")){
			return true;
		}
	}
	else{
		if (GameManager::getInstance().isRuleRenju()){ //렌주룰이면 체크안함
			return false;
		}
		if (strstr(str, "oooooo")){
			return true;
		}
	}
	return false;
}

bool GNode::isSsangsam(){
	int count33 = 0; //2이상이면 쌍삼
	int count44 = 0; //2이상이면 쌍사
	char str[9];

	//문자열로 만든 오목판 상태를 검사하는 함수
	auto check = [&](char* str){
		if (search44Pattern(str)){
			count44++;
			if (count44 >= 2){
				return true;
			}
		}
		else if (search33Pattern(str)){
			count33++;
			if (count33 >= 2){
				return true;
			}
		}
		else if (search6mokPattern(str)){
			return true;
		}
		return false;
	};

	//가로검사
	for (int i = -4; i <= 4; i++){
		if (didAction.x + i < 0 || didAction.x + i >= ROW){
			str[i + 4] = '?';
		}
		else{
			str[i + 4] = stateToChar(didAction.x + i, didAction.y);
		}
	}
	if (str[4] != '-'){
		if (check(str)) return true;
	}
	//세로검사
	for (int i = -4; i <= 4; i++){
		if (didAction.y + i < 0 || didAction.y + i >= ROW){
			str[i + 4] = '?';
		}
		else{
			str[i + 4] = stateToChar(didAction.x, didAction.y + i);
		}
	}
	if (str[4] != '-'){
		if (check(str)) return true;
	}
	//19대각선 검사
	for (int i = -4; i <= 4; i++){
		if (didAction.y - i < 0 || didAction.y - i >= ROW || didAction.x + i < 0 || didAction.x + i >= ROW){
			str[i + 4] = '?';
		}
		else{
			str[i + 4] = stateToChar(didAction.x + i, didAction.y - i);
		}
	}
	if (str[4] != '-'){
		if (check(str)) return true;
	}
	//37대각선 검사
	for (int i = -4; i <= 4; i++){
		if (didAction.y + i < 0 || didAction.y + i >= ROW || didAction.x + i < 0 || didAction.x + i >= ROW){
			str[i + 4] = '?';
		}
		else{
			str[i + 4] = stateToChar(didAction.x + i, didAction.y + i);
		}
	}
	if (str[4] != '-'){
		if (check(str)) return true;
	}
	return false;
}

GNode* GNode::result(GAction action){
	GNode* nextNode = new GNode(this);
	nextNode->doAction(action);
	return nextNode;
}

bool GNode::isPlayer(){
	if (stoneNum % 2 == 0){
		return true;
	}
	else{
		return false;
	}
}

void GNode::doAction(GAction action){
	if (isPlayer()){
		state[action.y][action.x] = S_BLACK;
	}
	else{
		state[action.y][action.x] = S_WHITE;
	}
	stoneNum++;
	didAction.x = action.x;
	didAction.y = action.y;
}

int GNode::getTurn() const{
	return stoneNum;
}

GAction GNode::getAction() const{
	return didAction;
}

std::vector<GAction> GNode::getTerminalAction() const{
	int count = 0;
	int i = 1;
	std::vector<GAction> ans;

	//가로 검사
	while (didAction.x + i < ROW && state[didAction.y][didAction.x + i] == state[didAction.y][didAction.x]){ //오른쪽검사
		count++;
		ans.push_back(GAction(didAction.x + i, didAction.y));
		i++;
	}
	i = 1;
	while (didAction.x - i >= 0 && state[didAction.y][didAction.x - i] == state[didAction.y][didAction.x]){ //왼쪽검사
		count++;
		ans.push_back(GAction(didAction.x - i, didAction.y));
		i++;
	}
	if (count == 4){
		ans.push_back(didAction);
		return ans;
	}

	//세로 검사
	count = 0;
	i = 1;
	ans.clear();
	while (didAction.y + i < ROW && state[didAction.y + i][didAction.x] == state[didAction.y][didAction.x]){ //아래검사
		count++;
		ans.push_back(GAction(didAction.x, didAction.y + i));
		i++;
	}
	i = 1;
	while (didAction.y - i >= 0 && state[didAction.y - i][didAction.x] == state[didAction.y][didAction.x]){ //위검사
		count++;
		ans.push_back(GAction(didAction.x, didAction.y - i));
		i++;
	}
	if (count == 4){
		ans.push_back(didAction);
		return ans;
	}

	//73대각선 검사
	count = 0;
	i = 1;
	ans.clear();
	while (didAction.x + i < ROW
		&& didAction.y + i < ROW
		&& state[didAction.y + i][didAction.x + i] == state[didAction.y][didAction.x]){ //3방향
		count++;
		ans.push_back(GAction(didAction.x + i, didAction.y + i));
		i++;
	}
	i = 1;
	while (didAction.x - i >= 0
		&& didAction.y - i >= 0
		&& state[didAction.y - i][didAction.x - i] == state[didAction.y][didAction.x]){ //7방향
		count++;
		ans.push_back(GAction(didAction.x - i, didAction.y - i));
		i++;
	}
	if (count == 4){
		ans.push_back(didAction);
		return ans;
	}

	//91대각선 검사
	count = 0;
	i = 1;
	ans.clear();
	while (didAction.x - i >= 0
		&& didAction.y + i < ROW
		&& state[didAction.y + i][didAction.x - i] == state[didAction.y][didAction.x]){ //1방향
		count++;
		ans.push_back(GAction(didAction.x - i, didAction.y + i));
		i++;
	}
	i = 1;
	while (didAction.x + i < ROW
		&& didAction.y - i >= 0
		&& state[didAction.y - i][didAction.x + i] == state[didAction.y][didAction.x]){ //9방향
		count++;
		ans.push_back(GAction(didAction.x + i, didAction.y - i));
		i++;
	}
	if (count == 4){
		ans.push_back(didAction);
		return ans;
	}

	ans.clear();
	return ans;
}
