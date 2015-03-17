#include "GameManager.h"

USING_NS_CC;
using namespace std;

GameManager::GameManager(){
	sound = CocosDenshion::SimpleAudioEngine::sharedEngine();
	auto userDefault = UserDefault::getInstance();
	//저장된 소지금 가져옴
	myMoney = userDefault->getIntegerForKey(DATA_INT_MYMONEY);
	//처음 시작하는게 아니면 이전에 저장한 값들을 불러옴
	if (userDefault->getBoolForKey(OPTION_BOOL_INITED)){
		//옵션 설정
		rule33 = userDefault->getBoolForKey(OPTION_BOOL_RULE33);
		rule44 = userDefault->getBoolForKey(OPTION_BOOL_RULE44);
		rule6mok = userDefault->getBoolForKey(OPTION_BOOL_RULE6MOK);
		ruleRenju = userDefault->getBoolForKey(OPTION_BOOL_RULERENJU);
		sound->setBackgroundMusicVolume(userDefault->getFloatForKey(OPTION_FLOAT_BGM));
		sound->setEffectsVolume(userDefault->getFloatForKey(OPTION_FLOAT_EFFECT));
		//오목알 설정
		currentStone = getStoneByID((StoneID)userDefault->getIntegerForKey(DATA_INT_CURRENTSTONE)); //장착중인 오목알
		auto str = userDefault->getStringForKey(DATA_STRING_STONELIST); //획득한 오목알 리스트
		char* list = new char[str.length() + 1];
		strcpy(list, str.c_str());
		char* tok;
		tok = strtok(list, "|");
		while (tok != NULL)
		{
			StoneID id = (StoneID)atoi(tok);
			stoneList.push_back(id);
			tok = strtok(NULL, "|");
		}
	}
	else{ //처음 시작하는거면 변수 초기화
		//옵션 설정
		userDefault->setBoolForKey(OPTION_BOOL_INITED, true);
		userDefault->flush();
		setRule33(true);
		setRule44(true);
		setRule6mok(true);
		setRuleRenju(false);
		userDefault->setFloatForKey(OPTION_FLOAT_BGM, 0.5f);
		userDefault->setFloatForKey(OPTION_FLOAT_EFFECT, 0.5f);
		sound->setEffectsVolume(0.5f);
		sound->setBackgroundMusicVolume(0.5f);
		//오목알 설정
		addStone(StoneID::BLACK_AND_WHITE);
		setCurrentStone(new Stone_Black());
	}
}

GameManager& GameManager::getInstance() {
	static GameManager instance;
	return instance;
}

float GameManager::getRandom_0_1() const{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(0.0, 1.0);
	return dist(mt);
}

void GameManager::setSceneState(SceneState state){
	this->currentScene = state;
}

SceneState GameManager::getSceneState() const{
	return currentScene;
}

Stone* GameManager::getCurrentStone() const{
	return currentStone;
}

void GameManager::setCurrentStone(Stone* stone){
	for (int i = 0; i < stoneList.size(); i++){
		if (stone->getStoneID() == stoneList.at(i)){
			delete currentStone;
			currentStone = stone;
			UserDefault::getInstance()->setIntegerForKey(DATA_INT_CURRENTSTONE, stone->getStoneID());
			return;
		}
	}
}

Stone* GameManager::getStoneByID(StoneID id) const{
	switch (id){
	case StoneID::BLACK_AND_WHITE:
		return new Stone_Black();
		break;
	case StoneID::CROSS:
		return new Stone_Cross();
		break;
	case StoneID::FISH:
		return new Stone_Fish();
		break;
	case StoneID::ORIBAL:
		return new Stone_Ori();
		break;
	case StoneID::SOCK:
		return new Stone_Sock();
		break;
	case StoneID::KETCHUP:
		return new Stone_Ketchup();
		break;
	case StoneID::OJING:
		return new Stone_Ojing();
		break;
	case StoneID::CRAB_HAND:
		return new Stone_Crab();
		break;
	default:
		return NULL;
		break;
	}
}

bool GameManager::addStone(StoneID id){
	for (int i = 0; i < stoneList.size(); i++){
		if (stoneList.at(i) == id){
			return false;
		}
	}
	stoneList.push_back(id);
	//저장
	auto str = UserDefault::getInstance()->getStringForKey(DATA_STRING_STONELIST);
	char buff[8];
	sprintf(buff, "|%d", id);
	str.append(buff);
	UserDefault::getInstance()->setStringForKey(DATA_STRING_STONELIST, str);
	UserDefault::getInstance()->flush();
	return true;
}

int GameManager::getMyMoney() const{
	return myMoney;
}

bool GameManager::setMyMoney(int money){
	if (myMoney + money < 0){
		return false;
	}
	else{
		myMoney += money;
		UserDefault::getInstance()->setIntegerForKey(DATA_INT_MYMONEY, myMoney);
		return true;
	}
}

int GameManager::getWinCountNormal(CharacterID id) const {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_NORMAL, id);
	int count = ud->getIntegerForKey(str);
	return count;
}

int GameManager::getWinCountRenju(CharacterID id) const {
	auto ud = cocos2d::UserDefault::getInstance();
	//키를 만듬
	char str[32];
	sprintf(str, "%s%d", DATA_INT_WINCOUNT_RENJU, id);
	int count = ud->getIntegerForKey(str);
	return count;
}

int GameManager::getWinCount(CharacterID id) const {
	auto ud = cocos2d::UserDefault::getInstance();
	//렌주룰 키를 만듬
	char strRenju[32];
	sprintf(strRenju, "%s%d", DATA_INT_WINCOUNT_RENJU, id);
	//보통룰 키를 만듬
	char strNormal[32];
	sprintf(strNormal, "%s%d", DATA_INT_WINCOUNT_NORMAL, id);
	//합침
	int count = ud->getIntegerForKey(strRenju);
	count += ud->getIntegerForKey(strNormal);
	return count;
}

bool GameManager::isRule33() const{
	return rule33;
}
bool GameManager::isRule44() const{
	return rule44;
}
bool GameManager::isRule6mok() const{
	return rule6mok;
}
bool GameManager::isRuleRenju() const{
	return ruleRenju;
}
void GameManager::setRule33(bool s){
	rule33 = s;
	UserDefault::getInstance()->setBoolForKey(OPTION_BOOL_RULE33, s);
	UserDefault::getInstance()->flush();
}
void GameManager::setRule44(bool s){
	rule44 = s;
	UserDefault::getInstance()->setBoolForKey(OPTION_BOOL_RULE44, s);
	UserDefault::getInstance()->flush();
}
void GameManager::setRule6mok(bool s){
	rule6mok = s;
	UserDefault::getInstance()->setBoolForKey(OPTION_BOOL_RULE6MOK, s);
	UserDefault::getInstance()->flush();
}
void GameManager::setRuleRenju(bool s){
	ruleRenju = s;
	UserDefault::getInstance()->setBoolForKey(OPTION_BOOL_RULERENJU, s);
	UserDefault::getInstance()->flush();
	if (s){
		setRule33(s);
		setRule44(s);
		setRule6mok(s);
	}
}