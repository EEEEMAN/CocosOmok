#include "CpuChar.h"

using namespace std;

CpuChar::CpuChar() {
}

CpuChar::~CpuChar() {
	if (stone != NULL) {
		delete stone;
	}
}

int CpuChar::alpha_beta(GNode* state, int alpha, int beta, int length) {
	if (state->isTerminal() || length <= 0
		|| GameManager::getInstance().getSceneState() != SCENE_OMOK) {
		return utility(state);
	}
	if (!state->isPlayer()) { //max일 경우
		GAction da = state->getAction();
		for (int y = ((da.y < ROW / 2) ? 0 : ROW - 1); y >= 0 && y < ROW;
			y = ((da.y < ROW / 2) ? y + 1 : y - 1)) {
			for (int x = ((da.x < ROW / 2) ? 0 : ROW - 1); x >= 0 && x < ROW;
				x = ((da.x < ROW / 2) ? x + 1 : x - 1)) {
				GAction act;
				act.x = x;
				act.y = y;
				//탐색범위 밖이면 탐색하지않고 넘어감
				if (!searchStone(state, act))
					continue;
				if (!state->isPlayer() && state->result(act)->isSsangsam())
					continue;
				if (state->state[y][x] == S_EMPTY) {
					int value = alpha_beta(state->result(act), alpha, beta,
						length - 1);
					if (value > alpha) {
						alpha = value;
					}
					if (alpha >= beta) {
						goto ALPHA_CUT;
					}
				}
			}
		}
	ALPHA_CUT: return alpha;
	}
	else { //min일 경우
		GAction da = state->getAction();
		for (int y = ((da.y < ROW / 2) ? 0 : ROW - 1); y >= 0 && y < ROW;
			y = ((da.y < ROW / 2) ? y + 1 : y - 1)) {
			for (int x = ((da.x < ROW / 2) ? 0 : ROW - 1); x >= 0 && x < ROW;
				x = ((da.x < ROW / 2) ? x + 1 : x - 1)) {
				GAction act;
				act.x = x;
				act.y = y;
				if (!searchStone(state, act))
					continue;
				if (!state->isPlayer() && state->result(act)->isSsangsam())
					continue;
				if (state->state[y][x] == S_EMPTY) {
					int value = alpha_beta(state->result(act), alpha, beta,
						length - 1);
					if (value < beta) {
						beta = value;
					}
					if (alpha >= beta) {
						goto BETA_CUT;
					}
				}
			}
		}
	BETA_CUT: return beta;
	}
}

GAction CpuChar::getBestAction(GNode* state) {
	auto func = [&](GAction *answers, int *score, int start, int end) {
		int alpha = -INF, beta = INF; //알파베타값 초기화
		GAction ans;//리턴할 값

		GAction da = state->getAction();

		for (int y = start; y < end; y++) {
			for (int x = 0; x < ROW; x++) {
				GAction act;
				act.x = x;
				act.y = y;
				if (state->result(act)->isSsangsam()) continue;
				if (state->state[act.y][act.x] == S_EMPTY //빈 공간이고
					&& act.getLength(state->getAction()) < searchLength//탐색 범위 내에 있고
					&& searchStone(state, act))//주위 8방향에 돌이 하나 이상 있을 경우에만 점수 계산
				{
					int value = alpha_beta(state->result(act), alpha, beta, readTurn);
					if (value > alpha) {
						alpha = value;
						ans = GAction(act.x, act.y);
					}
				}
			}
		}
		*score = alpha;
		answers->x = ans.x;
		answers->y = ans.y;
	};

	//시간을 단축하기 위해 여러개의 스레드로 병렬처리
	GAction answers[ROW];
	int score[ROW];
	std::thread th[ROW];
	for (int i = 0; i < ROW; i++) {
		th[i] = std::thread(func, answers + i, score + i, i, i + 1);
	}
	for (int i = 0; i < ROW; i++) {
		th[i].join();
	}
	//각 스레드가 가져온 결과중에서 제일 높은 값을 채택
	int s = 0;
	int sco = -INF;
	for (int i = 0; i < ROW; i++) {
		if (sco < score[i]) {
			sco = score[i];
			s = i;
		}
	}
	return answers[s];
}

int CpuChar::utility(GNode* node) const {
	int util = 0;

	//가로
	for (int y = 0; y < ROW; y++) {
		char str[ROW + 1] = { '\n' };
		for (int x = 0; x < ROW; x++) {
			switch (node->state[y][x]) {
			case S_BLACK:
				str[x] = 'x';
				break;
			case S_WHITE:
				str[x] = 'o';
				break;
			case S_EMPTY:
				str[x] = '-';
				break;
			default:
				str[x] = '?';
			}
		}
		util += seachString(str);
	}
	//세로
	for (int x = 0; x < ROW; x++) {
		char str[ROW + 1] = { '\n' };
		for (int y = 0; y < ROW; y++) {
			switch (node->state[y][x]) {
			case S_BLACK:
				str[y] = 'x';
				break;
			case S_WHITE:
				str[y] = 'o';
				break;
			case S_EMPTY:
				str[y] = '-';
				break;
			default:
				str[y] = '?';
			}
		}
		util += seachString(str);
	}
	//73대각선
	for (int y = ROW - 1; y >= 0; y--){ //왼쪽부터 중간까지
		char str[ROW + 1] = { '\n' };
		for (int x = 0; x <= (ROW - 1) - y; x++){
			switch (node->state[y + x][x])
			{
			case S_BLACK:
				str[x] = 'x';
				break;
			case S_WHITE:
				str[x] = 'o';
				break;
			case S_EMPTY:
				str[x] = '-';
				break;
			default:
				str[x] = '?';
			}
		}
		util += seachString(str);
	}
	for (int i = 1; i < ROW; i++){ //중간부터 오른쪽까지
		char str[ROW + 1] = { '\n' };
		for (int y = 0; y < ROW - i; y++){
			switch (node->state[y][y + i])
			{
			case S_BLACK:
				str[y] = 'x';
				break;
			case S_WHITE:
				str[y] = 'o';
				break;
			case S_EMPTY:
				str[y] = '-';
				break;
			default:
				str[y] = '?';
			}
		}
		util += seachString(str);
	}
	//19대각선
	for (int i = 0; i < ROW; i++){ //왼쪽부터 중간까지
		char str[ROW + 1] = { '\n' };
		for (int x = 0; x <= i; x++){
			switch (node->state[i - x][x])
			{
			case S_BLACK:
				str[x] = 'x';
				break;
			case S_WHITE:
				str[x] = 'o';
				break;
			case S_EMPTY:
				str[x] = '-';
				break;
			default:
				str[x] = '?';
			}
		}
		util += seachString(str);
	}
	for (int y = 1; y < ROW; y++){ //중간부터 오른쪽까지
		char str[ROW + 1] = { '\n' };
		for (int x = y; x < ROW; x++){
			switch (node->state[(ROW - 1) - (x - y)][x])
			{
			case S_BLACK:
				str[x - y] = 'x';
				break;
			case S_WHITE:
				str[x - y] = 'o';
				break;
			case S_EMPTY:
				str[x - y] = '-';
				break;
			default:
				str[x - y] = '?';
			}
		}
		util += seachString(str);
	}

	//금수검사
	if (node->isSsangsam()) {
		if (node->getTurn() % 2 == 1) {
			util += 100;
		}
		else {
			util -= 100;
		}
	}
	return util;
}

char* CpuChar::getStoneImageName() const {
	if (GameManager::getInstance().getCurrentStone()->getStoneID()
		== stone->getStoneID())
		return stone->getImgName2P();
	else
		return stone->getImgName1P();
}

int CpuChar::getWinCountNormal() const {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_NORMAL, characterID);
	int count = ud->getIntegerForKey(str);
	return count;
}

int CpuChar::getWinCountRenju() const {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_RENJU, characterID);
	int count = ud->getIntegerForKey(str);
	return count;
}

int CpuChar::getWinCount() const {
	auto ud = cocos2d::UserDefault::getInstance();
	//렌주룰 키를 만듬
	char strRenju[32];
	sprintf(strRenju, "%s%d", DATA_INT_WINCOUNT_RENJU, characterID);
	//보통룰 키를 만듬
	char strNormal[32];
	sprintf(strNormal, "%s%d", DATA_INT_WINCOUNT_NORMAL, characterID);
	//합침
	int count = ud->getIntegerForKey(strRenju);
	count += ud->getIntegerForKey(strNormal);
	return count;
}

void CpuChar::raiseWinCountNormal() {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_NORMAL, characterID);
	int count = ud->getIntegerForKey(str); //이긴 횟수 불러옴
	count++; //하나 증가
	ud->setIntegerForKey(str, count); //증가한 값을 저장
}

void CpuChar::raiseWinCountRenju() {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_RENJU, characterID);
	int count = ud->getIntegerForKey(str); //이긴 횟수 불러옴
	count++; //하나 증가
	ud->setIntegerForKey(str, count); //증가한 값을 저장
}

char* CpuChar::getImageName() const {
	return imageName;
}

char* CpuChar::getName() const {
	return name;
}

Stone* CpuChar::getStone() const {
	return stone;
}

CharacterID CpuChar::getCharacterID() const {
	return characterID;
}

int CpuChar::getMoney() const {
	return money;
}

float CpuChar::getStoneProbability() const {
	return stoneProbability;
}

bool CpuChar::searchStone(GNode* state, GAction action) const {
	for (int y = action.y - 1; y <= action.y + 1; y++) {
		for (int x = action.x - 1; x <= action.x + 1; x++) {
			if (x >= 0 && x < ROW && y >= 0 && y < ROW) {
				if (state->state[y][x] != GState::S_EMPTY) {
					if (!(action.y == y && action.x == x))
						return true;
				}
			}
		}
	}
	return false;
}
