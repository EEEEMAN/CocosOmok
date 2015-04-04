#include "CpuEnemy.h"

CpuEnemy::CpuEnemy(){
	characterID = CharacterID::CHAR_OJING;
	readTurn = 0;
	imageName = "ojing.png";
	name = "";
	stone = new Stone_Ojing();
	money = 50;
	stoneProbability = 1.0;
}

int CpuEnemy::alpha_beta(GNode* state, int alpha, int beta, int length) {
	if (state->isTerminal() || length <= 0
		|| GameManager::getInstance().getSceneState() != SCENE_OMOK) {
		return utility(state);
	}
	if (!state->isPlayer()) { //max일 경우
		for (int i = 0; i < state->actionList.size(); i++){
			GAction* act = &state->actionList.at(i);
			if (!state->isPlayer() && state->result(*act)->isSsangsam())
				continue;
			if (state->state[act->y][act->x] == S_EMPTY) {
				int value = alpha_beta(state->result(*act), alpha, beta,
					length - 1);
				if (value > alpha) {
					alpha = value;
				}
				if (alpha >= beta) {
					break;
				}
			}
		}
		return alpha;
	}
	else { //min일 경우
		for (int i = 0; i < state->actionList.size(); i++){
			GAction* act = &state->actionList.at(i);
			if (!state->isPlayer() && state->result(*act)->isSsangsam())
				continue;
			if (state->state[act->y][act->x] == S_EMPTY) {
				int value = alpha_beta(state->result(*act), alpha, beta,
					length - 1);
				if (value < beta) {
					beta = value;
				}
				if (alpha >= beta) {
					break;
				}
			}
		}return beta;
	}
}

GAction CpuEnemy::getBestAction(GNode* state) {
	int alpha = -INF, beta = INF; //알파베타값 초기화
	GAction ans;//리턴할 값

	GAction da = state->getAction();

	for (int i = 0; i < state->actionList.size(); i++){
		GAction* act = &state->actionList.at(i);
		if (state->result(*act)->isSsangsam()) continue;
		if (state->state[act->y][act->x] == S_EMPTY){
			int value = alpha_beta(state->result(*act), alpha, beta, readTurn);
			if (value > alpha) {
				alpha = value;
				ans = GAction(act->x, act->y);
			}
		}
	}

	return ans;
}

int CpuEnemy::seachString(char* str) const {
	int util = 0;

	if (strstr(str, "--o--")) {
		util += 1;
	}
	if (strstr(str, "--oo-")) {
		util += 2;
	}
	if (strstr(str, "-o-o-")) {
		util += 2;
	}
	if (strstr(str, "-oo--")) {
		util += 2;
	}
	if (strstr(str, "-ooo-")) {
		util += 10;
	}
	if (strstr(str, "oooo-")) {
		util += 15;
	}
	if (strstr(str, "ooo-o")) {
		util += 15;
	}
	if (strstr(str, "oo-oo")) {
		util += 15;
	}
	if (strstr(str, "o-ooo")) {
		util += 15;
	}
	if (strstr(str, "-oooo")) {
		util += 15;
	}
	if (strstr(str, "ooooo")) {
		util += 1000;
	}

	if (strstr(str, "--x--")) {
		util -= 1;
	}
	if (strstr(str, "--xx-")) {
		util -= 2;
	}
	if (strstr(str, "-x-x-")) {
		util -= 2;
	}
	if (strstr(str, "-xx--")) {
		util -= 2;
	}
	if (strstr(str, "-xxx-")) {
		util -= 10;
	}
	if (strstr(str, "xxxx-")) {
		util -= 15;
	}
	if (strstr(str, "xxx-x")) {
		util -= 15;
	}
	if (strstr(str, "xx-xx")) {
		util -= 15;
	}
	if (strstr(str, "x-xxx")) {
		util -= 15;
	}
	if (strstr(str, "-xxxx")) {
		util -= 15;
	}
	if (strstr(str, "xxxxx")) {
		util -= 1000;
	}

	if (strstr(str, "oxxxxo")) {
		util += 1000;
	}
	if (strstr(str, "xxxox")) {
		util += 100;
	}
	if (strstr(str, "xxoxx")) {
		util += 100;
	}
	if (strstr(str, "xoxxx")) {
		util += 100;
	}
	if (strstr(str, "oxxxx-")) {
		util += 50;
	}
	if (strstr(str, "-xxxxo")) {
		util += 50;
	}
	return util;
}