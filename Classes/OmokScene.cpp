#include "OmokScene.h"

USING_NS_CC;

void OmokScene::startGame(CpuChar* enemyChar) {
	//admob 가리기
	if (AdmobHelper::isAdShowing){
		AdmobHelper::hideAd();
	}
	//현재씬 변경
	GameManager::getInstance().setSceneState(SCENE_OMOK);
	auto scene = Scene::create();
	auto layer = OmokScene::create();
	//적캐릭터 세팅
	if (enemyChar != NULL) {
		layer->setEnemy(enemyChar);
	}
	layer->initStatusBar();
	scene->addChild(layer);
	TransitionScene* transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);
}

void OmokScene::startGame(char* stone1P, char* stone2P) {
	//admob 가리기
	if (AdmobHelper::isAdShowing){
		AdmobHelper::hideAd();
	}
	//현재씬 변경
	GameManager::getInstance().setSceneState(SCENE_OMOK);
	auto scene = Scene::create();
	auto layer = OmokScene::create();
	//돌 세팅
	layer->stoneName1P = stone1P;
	layer->stoneName2P = stone2P;
	//2p전 세팅
	layer->enemy = NULL;
	layer->isVsCPU = false;

	layer->initStatusBar();
	scene->addChild(layer);
	TransitionScene* transition = TransitionFade::create(1.0f, scene);
	Director::getInstance()->replaceScene(transition);
}

void OmokScene::setEnemy(CpuChar* enemy){
	this->enemy = enemy;
	this->isVsCPU = true;
}

bool OmokScene::init() {
	if (!LayerColor::initWithColor(Color4B(255, 120, 120, 255))) {
		return false;
	}
	//bgm
	GameManager::getInstance().sound->stopBackgroundMusic();
	GameManager::getInstance().sound->playBackgroundMusic(BGM_GAMESCENE, true);

	//화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	//키 이벤트
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(OmokScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	//오목판 상태 초기화
	gameState = new GNode();

	//오목판 초기화
	Layer* stageScroll = NULL;
	if (ROW == 15){
		stageScroll = (Layer*)CSLoader::getInstance()->createNode(
			"OmokLayer_15.csb");
	}
	backGround =
		(Sprite*)stageScroll->getChildByName("scroll")->getChildByName(
		"stage");
	stageScroll->setName("stageScroll");
	stageScroll->setPosition(Vec2(0, 0));
	stageScroll->setAnchorPoint(Vec2(0, 0));
	stageScroll->setScaleX(winSize.width / stageScroll->getContentSize().width);
	stageScroll->setScaleY(
		winSize.height * 0.9 / stageScroll->getContentSize().height);
	this->addChild(stageScroll, ORDER_STAGE);
	//오목판을 가운데로 스크롤
	dynamic_cast<ui::ScrollView*>(stageScroll->getChildByName("scroll"))->scrollToPercentBothDirection(Vec2(50, 50), 1, true);

	//터치 이벤트
	auto eDispatcher = Director::getInstance()->getEventDispatcher();
	listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(OmokScene::onTouchBegan, this);
	listener->onTouchCancelled = CC_CALLBACK_2(OmokScene::onTouchCancelled,
		this);
	listener->onTouchEnded = CC_CALLBACK_2(OmokScene::onTouchEnded, this);
	listener->onTouchMoved = CC_CALLBACK_2(OmokScene::onTouchMoved, this);
	eDispatcher->addEventListenerWithSceneGraphPriority(listener, backGround);

	arrowLastStone = CSLoader::createNode("LastStone.csb");
	arrowAnim = CSLoader::createTimeline("LastStone.csb");
	arrowAnim->gotoFrameAndPlay(0, true);
	arrowLastStone->runAction(arrowAnim);
	enemy = NULL;
	isVsCPU = false;
	this->scheduleUpdate();
	return true;
}

//상태창 초기화
void OmokScene::initStatusBar() {
	status = CSLoader::getInstance()->createNode("StatusBar.csb");
	status->setPosition(Vec2(winSize.width * 0.5, winSize.height));
	status->setAnchorPoint(Vec2(0.5f, 1.0f));
	status->setScaleX(winSize.width / status->getContentSize().width);
	status->setScaleY(winSize.height * 0.1 / status->getContentSize().height);
	//돌이미지 초기화
	auto stonePanel = status->getChildByName("stonePanel");
	if (isVsCPU){
		statusStone[0] = Sprite::create(GameManager::getInstance().getCurrentStone()->getImgName1P());
		statusStone[1] = Sprite::create(enemy->getStoneImageName());
	}
	else{
		statusStone[0] = Sprite::create(stoneName1P);
		statusStone[1] = Sprite::create(stoneName2P);
	}
	statusStone[0]->setAnchorPoint(Vec2(0, 0));
	statusStone[0]->setPosition(Vec2(0, 0));
	stonePanel->addChild(statusStone[0]);
	statusStone[1]->setAnchorPoint(Vec2(0, 0));
	statusStone[1]->setPosition(Vec2(0, 0));
	stonePanel->addChild(statusStone[1]);
	this->checkTurn();

	//생각중이미지 초기화
	statusThink = status->getChildByName("think");
	statusThink->setVisible(false);
	//적이미지 초기화
	if (enemy != NULL) { //enemy가 NULL일 경우는 VS 2P모드일 때
		statusCharacter = status->getChildByName("charPanel");
		status->setPosition(Vec2(winSize.width * 0.5, winSize.height));
		status->setAnchorPoint(Vec2(0.5f, 1.0f));

		auto img = Sprite::create(enemy->getImageName());
		statusCharacter->addChild(img);
		img->setAnchorPoint(Vec2(1.0, 0.0));
		img->setPosition(Vec2(statusCharacter->getContentSize().width, 0));
		img->setScale(statusCharacter->getContentSize().width / img->getContentSize().width);
	}
	else{
		statusCharacter = status->getChildByName("charPanel");
		status->setPosition(Vec2(winSize.width * 0.5, winSize.height));
		status->setAnchorPoint(Vec2(0.5f, 1.0f));

		auto img = Sprite::create("2p.png");
		statusCharacter->addChild(img);
		img->setAnchorPoint(Vec2(1.0, 0.0));
		img->setPosition(Vec2(statusCharacter->getContentSize().width, 0));
	}
	this->addChild(status, ORDER_STATUSBAR);
}

bool OmokScene::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void OmokScene::onTouchCancelled(Touch* touch, Event* event) {
}

void OmokScene::onTouchMoved(Touch* touch, Event* event) {
}

void OmokScene::onTouchEnded(Touch* touch, Event* event) {
	if (!touch->getStartLocation().equals(touch->getLocation())) return;
	if (!gameState->isPlayer() && isVsCPU && !gameState->isTerminal()){
		return;
	}
	isTouched = true;
	auto node = event->getCurrentTarget();
	Point pos = node->convertToNodeSpace(touch->getLocation());
	//터치한 좌표를 GAction으로 변환
	GAction action = convertPosToGAction(pos);
	if (action.x == -1 && action.y == -1)
		return;

	//변환한 좌표에 돌을 둘 수 있는지 검사하고 둘 수 없으면 리턴
	if (gameState->state[action.y][action.x] != S_EMPTY) {
		return;
	}

	//좌표가 선택상태가 아니라면 선택상태로 만듬
	if (!action.isEqual(selectedPoint)) {
		if (backGround->getChildByTag(TAG_CURSOR) != NULL) {
			backGround->removeChildByTag(TAG_CURSOR);
		}
		selectedPoint = action;
		Sprite* cursor = Sprite::create("cursor.png");
		cursor->setTag(TAG_CURSOR);
		cursor->setAnchorPoint(Vec2(0.0, 1.0));
		cursor->setPosition(
			Vec2(action.x * STONE_SIZE,
			(STONE_SIZE * ROW) - (action.y * STONE_SIZE)));
		backGround->addChild(cursor);
	}
	else { //터치한 좌표가 선택상태라면
		//좌표가 쌍삼인지 검사한뒤
		if (gameState->result(action)->isSsangsam()) {
			//쌍삼이면 메시지 출력후 종료
			GameManager::getInstance().sound->playEffect(EFFECT_WARNING);
			auto ssangsam = Sprite::create("ssangsam.png");
			ssangsam->setName("ssangsam");
			this->addChild(ssangsam, ORDER_GAMEOVER);
			ssangsam->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.7));
			ssangsam->setAnchorPoint(Vec2(0.5, 0.5));
			auto action_delay = DelayTime::create(1.0f);
			auto action_remove = CallFuncN::create(CC_CALLBACK_1(OmokScene::selfRemover, this));
			ssangsam->runAction(Sequence::create(action_delay, action_remove, NULL));
			return;
		}
		//돌을 둔다
		doAction(action);
		backGround->removeChildByTag(TAG_CURSOR);

		//마지막으로 둔 돌을 표시
		showLastAction();

		//현재 상태가 종료 상태인지 검사
		checkGameOver();

		//cpu戰이면 cpu 차례
		if (isVsCPU && !gameState->isTerminal()) {
			statusThink->setVisible(true);
			auto th = std::thread([this](CpuChar* enemy, GNode* gameState){
				this->cpuAnswer = enemy->getBestAction(gameState);
				Director::getInstance()->getScheduler()->performFunctionInCocosThread(CC_CALLBACK_0(OmokScene::cpuThread, this));
			}, enemy, gameState);
			th.detach();
		}
	}
}

void OmokScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	if (gameState->isTerminal()) return;
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE){
		if (!isMessageBoxVisible){
			//오목판 터치를 막음
			Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(backGround);
			//오목판 스크롤을 막음
			auto stageScroll = dynamic_cast<ui::ScrollView*>(this->getChildByName("stageScroll")->getChildByName("scroll"));
			stageScroll->setTouchEnabled(false);
			//메시지박스 출력
			auto msgBox = CSLoader::createNode("MessageBox.csb");
			dynamic_cast<ui::Button*>(msgBox->getChildByName("btn_yes"))->addTouchEventListener(CC_CALLBACK_2(OmokScene::msgBoxTouch, this));
			dynamic_cast<ui::Button*>(msgBox->getChildByName("btn_no"))->addTouchEventListener(CC_CALLBACK_2(OmokScene::msgBoxTouch, this));
			auto message = dynamic_cast<ui::Text*>(msgBox->getChildByName("message"));
			message->setText("이전 화면으로 돌아갈까요?");
			msgBox->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			addChild(msgBox, ORDER_MESSAGEBOX);
			//애니메이션
			auto anim = CSLoader::createTimeline("MessageBox.csb");
			anim->gotoFrameAndPlay(0, false);
			msgBox->runAction(anim);

			isMessageBoxVisible = true;
		}
	}
}

void OmokScene::msgBoxTouch(cocos2d::Ref* sender, ui::Widget::TouchEventType type){
	auto node = dynamic_cast<Node*>(sender);
	if (type == ui::Widget::TouchEventType::ENDED){
		if (node->getName().compare("btn_yes") == 0){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			closeGame();
		}
		else if (node->getName().compare("btn_no") == 0){
			isMessageBoxVisible = false;
			Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(backGround);
			auto stageScroll = dynamic_cast<ui::ScrollView*>(this->getChildByName("stageScroll")->getChildByName("scroll"));
			stageScroll->setTouchEnabled(true);
			selfRemover(node->getParent());
		}
		else if (node->getName().compare("btn_ok") == 0){
			closeGame();
		}
	}
}

void OmokScene::cpuThread(){
	if (GameManager::getInstance().getSceneState() == SCENE_OMOK){
		doAction(cpuAnswer);
		showLastAction();
		statusThink->setVisible(false);
		checkGameOver();
		isTouched = false;
	}
}

void OmokScene::selfRemover(Node* sender){
	sender->removeFromParentAndCleanup(true);
}

void OmokScene::showLastAction() {
	auto lastPos = convertGActionToPos(gameState->getAction());
	//화살표 위치 조정
	arrowLastStone->setPosition(Vec2(lastPos.x + STONE_SIZE / 2, lastPos.y - STONE_SIZE / 2));
	arrowLastStone->setTag(TAG_LASTACTION);
	//화면에 화살표가 없으면 새로 addChild
	if (!backGround->getChildByTag(TAG_LASTACTION) != NULL) {
		backGround->addChild(arrowLastStone, ORDER_STAGE_ARROW);
	}
	auto scroll = dynamic_cast<ui::ScrollView*>(getChildByName("stageScroll")->getChildByName("scroll"));
	auto backSize = backGround->getContentSize();
	auto percent = Vec2(lastPos.x / backSize.width * 100, 100 - (lastPos.y / backSize.height * 100));
	scroll->scrollToPercentBothDirection(percent, 0.3f, true);
}

void OmokScene::checkGameOver() {
	if (gameState->isTerminal()) {
		std::vector<GAction> winstones = gameState->getTerminalAction();
		for (auto act : winstones) {
			Sprite* stone = Sprite::create("win_stone.png");
			stone->setAnchorPoint(Vec2(0.0, 1.0));
			stone->setPosition(convertGActionToPos(act));
			backGround->addChild(stone, ORDER_STAGE_ARROW);
		}

		if (!gameState->isPlayer()) {
			listener->setEnabled(false);
			showGameOverAnimation();
		}
		else {
			listener->setEnabled(false);
			showGameOverAnimation();
		}
	}
}

//게임이 끝나면 종료 누가 이겼는지 애니매이션으로 표시
void OmokScene::showGameOverAnimation() {
	auto gameover = CSLoader::getInstance()->createNode("P1WinAnim.csb");
	auto star = gameover->getChildByName("win"); //글씨 뒤의 별 이미지
	if (gameState->getTurn() % 2 == 1) { //1p가 이겼을 경우
		auto sprite = Sprite::create("p1win.png");
		sprite->setPosition(Vec2(star->getContentSize().width / 2, star->getContentSize().height / 2));
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		star->addChild(sprite);

		//cpu전이면 보상을 얻음
		if (isVsCPU){
			char txt[255];
			sprintf(txt, "");
			//돌 획득
			//캐릭터의 확률(0~1)이 랜덤으로 얻은 확률(0~1)보다 크면 돌을 얻음
			float val = GameManager::getInstance().getRandom_0_1();
			if (val < enemy->getStoneProbability()){
				cocos2d::log("stineID : %d", enemy->getStone()->getStoneID());
				if (GameManager::getInstance().addStone(enemy->getStone()->getStoneID())){
					sprintf(txt, "%s\n새로운 오목알 획득!", txt);
				}
			}
			//이긴횟수증가, 돈획득
			if (GameManager::getInstance().isRuleRenju()){
				//렌주룰이면 렌주룰로 이긴 횟수를 1 증가, 얻는돈1.5배
				enemy->raiseWinCountRenju();
				//int money = enemy->getMoney() * 1.5;
				//GameManager::getInstance().setMyMoney(money);
				//sprintf(txt, "%s\n돈 %d원 획득!", txt, money);
			}
			else{
				enemy->raiseWinCountNormal();
				//int money = enemy->getMoney();
				//GameManager::getInstance().setMyMoney(money);
				//sprintf(txt, "%s\n돈 %d원 획득!", txt, money);
			}
			//메시지 출력
			auto txt_msg = dynamic_cast<ui::Text*>(gameover->getChildByName("txt_result"));
			txt_msg->setText(txt);
		}

	}
	else{ //2p가 이겼을 경우
		auto sprite = Sprite::create("p2win.png");
		sprite->setPosition(Vec2(star->getContentSize().width / 2, star->getContentSize().height / 2));
		sprite->setAnchorPoint(Vec2(0.5, 0.5));
		star->addChild(sprite);
	}
	GameManager::getInstance().sound->playEffect(EFFECT_GAMEOVER);
	gameover->setAnchorPoint(Vec2(0.5, 0.5));
	gameover->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	gameover->setName("gameover");
	this->addChild(gameover, ORDER_GAMEOVER);

	//애니메이션 재생
	auto anim = CSLoader::getInstance()->createTimeline("P1WinAnim.csb");
	anim->gotoFrameAndPlay(0, false);
	anim->setTimeSpeed(0.9);
	gameover->runAction(anim);

	//확인 버튼 이벤트 추가
	auto btn = dynamic_cast<ui::Button*>(gameover->getChildByName("btn_ok"));
	btn->addTouchEventListener(CC_CALLBACK_2(OmokScene::msgBoxTouch, this));
}

void OmokScene::closeGame() {
	if (isVsCPU){
		GameManager::getInstance().setSceneState(SCENE_STAGESELECT);
		GameManager::getInstance().sound->stopBackgroundMusic();
		GameManager::getInstance().sound->playBackgroundMusic(BGM_TITLE, true);
		TransitionScene* transition = TransitionFade::create(1.0f, StageSelectScene::createScene());
		Director::getInstance()->replaceScene(transition);
	}
	else{
		GameManager::getInstance().setSceneState(SCENE_TITLE);
		GameManager::getInstance().sound->stopBackgroundMusic();
		GameManager::getInstance().sound->playBackgroundMusic(BGM_TITLE, true);
		TransitionScene* transition = TransitionFade::create(1.0f, OmokTitleScene::createScene());
		Director::getInstance()->replaceScene(transition);
	}
}

Sprite* OmokScene::getActionSprite(GAction action){
	char fileName[20] = { '\n', };
	if (gameState->isPlayer()) {
		if (isVsCPU){ //cpu전일경우 자신의돌
			strcpy(fileName, GameManager::getInstance().getCurrentStone()->getImgName1P());
		}
		else{ //2p전일경우 자신의돌
			strcpy(fileName, stoneName1P);
		}
	}
	else {
		if (isVsCPU){//cpu전일경우 적의돌
			strcpy(fileName, enemy->getStoneImageName());
		}
		else{ //2p전일경우 2p의돌
			strcpy(fileName, stoneName2P);
		}
	}
	Sprite* stone = Sprite::create(fileName);
	stone->setAnchorPoint(Vec2(0.0, 1.0));
	stone->setPosition(convertGActionToPos(action));

	return stone;
}

void OmokScene::doAction(GAction action) {
	//뷰
	auto stone = getActionSprite(action);
	backGround->addChild(stone, ORDER_STAGE_STONE);

	GameManager::getInstance().sound->playEffect(EFFECT_DOACTION);

	//모델
	gameState->doAction(action);
	checkTurn();
}

Vec2 OmokScene::convertGActionToPos(GAction action) const {
	return Vec2(action.x * STONE_SIZE,
		(STONE_SIZE * ROW) - (action.y * STONE_SIZE));
}

GAction OmokScene::convertPosToGAction(Vec2 vec2) const {
	if (vec2.x > ROW * STONE_SIZE || vec2.y > ROW * STONE_SIZE || vec2.x < 0
		|| vec2.y < 0) {
		return GAction();
	}
	Vec2* pos = new Vec2(vec2.x, (float)(ROW * STONE_SIZE) - vec2.y);
	GAction action;
	action.x = (int)(pos->x / STONE_SIZE);
	action.y = (int)(pos->y / STONE_SIZE);
	return action;
}

void OmokScene::checkTurn() {
	if (statusStone == NULL)
		return;
	if (gameState->isPlayer()) {
		statusStone[0]->setVisible(true);
		statusStone[1]->setVisible(false);
	}
	else {
		statusStone[0]->setVisible(false);
		statusStone[1]->setVisible(true);
	}
}
