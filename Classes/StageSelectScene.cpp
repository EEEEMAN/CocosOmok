#include "StageSelectScene.h"

USING_NS_CC;

Scene* StageSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StageSelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool StageSelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size winSize = Director::getInstance()->getVisibleSize();

	//admob 나타내기
	if (!AdmobHelper::isAdShowing){
		AdmobHelper::showAd();
	}

	this->setName("StageSelectScene");

	//키 입력
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(StageSelectScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	//GameManager 설정
	GameManager::getInstance().setSceneState(SCENE_STAGESELECT);

	//씬 로드
	auto backGround = Sprite::create("background.png");
	backGround->setScale(winSize.height / backGround->getContentSize().height);
	backGround->setAnchorPoint(Vec2(0.5, 0.5));
	backGround->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(backGround, ORDER_STAGESELECT_BACKGROUND);
	auto scene = CSLoader::createNode("StageSelect.csb");
	scene->setName("scene");
	auto pageView = dynamic_cast<ui::PageView*>(scene->getChildByName("pageView"));
	pageView->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::btnTouch, this));
	addChild(scene, ORDER_STAGESELECT_BACKGROUND);

	//버튼 터치
	auto btn_start = dynamic_cast<ui::Button*>(scene->getChildByName("btn_start"));
	btn_start->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::btnTouch, this));
	auto btn_goTitle = dynamic_cast<ui::Button*>(scene->getChildByName("btn_return"));
	btn_goTitle->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::btnTouch, this));
	auto btn_changeStone = dynamic_cast<ui::Button*>(scene->getChildByName("btn_changeStone"));
	btn_changeStone->addTouchEventListener(CC_CALLBACK_2(StageSelectScene::btnTouch, this));

	//현재 장착중인 돌 표시
	updateCurrentStone();

	//현제 소지금 표시
	//updateMyMoney();

	//캐릭터 추가
	auto gm = &GameManager::getInstance();
	addCharacter(new CpuEnemy());
	addCharacter(new CpuOjing());
	if (gm->getWinCount(CharacterID::CHAR_OJING) > 0){
		addCharacter(new CpuCrab());
		addCharacter(new CpuMyeolchi());
	}
	if (gm->getWinCount(CharacterID::CHAR_CRAB) > 0 && gm->getWinCount(CharacterID::CHAR_MYEOLCHI) > 0){
		addCharacter(new CpuOri());
	}
	if (gm->getWinCount(CharacterID::CHAR_ORI) > 0){
		addCharacter(new CpuJanggab());
	}
	if (gm->getWinCount(CharacterID::CHAR_JANGGAB) > 0){
		addCharacter(new CpuKetchup());
	}
	if (gm->getWinCount(CharacterID::CHAR_KETCHUP) > 0){
		addCharacter(new CpuOmok());
	}

	//기억해둔 페이지로 이동
	auto pageIndex = UserDefault::getInstance()->getIntegerForKey(DATA_INT_STAGE_SELECT_PAGEINDEX);
	dynamic_cast<ui::PageView*>(scene->getChildByName("pageView"))->scrollToPage(pageIndex);

	setCharName();

	return true;
}

void StageSelectScene::addCharacter(CpuChar* ch){
	ch->getWinCountNormal();
	auto pageview = dynamic_cast<ui::PageView*>(getChildByName("scene")->getChildByName("pageView")); //스크롤하는 공간
	auto fence = CSLoader::createNode("Fence.csb"); //캐릭터 정보를 띄울 칸
	if (!pageview || !fence){
		return;
	}
	auto panel = fence->getChildByName("panel"); //캐릭터 이미지를 띄울위치
	auto panel2 = fence->getChildByName("panel2"); //캐릭터 설명을 띄울위치

	auto sprite = Sprite::create(ch->getImageName()); //panel에 넣을 캐릭터 이미지
	sprite->setAnchorPoint(Vec2(1.0, 0.0));
	sprite->setPosition(Vec2(panel->getContentSize().width, 0));
	sprite->setScaleX(panel->getContentSize().width / sprite->getContentSize().width);
	sprite->setScaleY(panel->getContentSize().height / sprite->getContentSize().height);
	panel->addChild(sprite);

	//보통룰 승리 여부 표시
	if (ch->getWinCountNormal() >= 1){
		auto starNormal = Sprite::create("star.png"); //보통룰 승리 여부를 나타내는 별
		starNormal->setAnchorPoint(Vec2(1.0, 0));
		starNormal->setPosition(Vec2(panel2->getContentSize().width / 2, panel2->getContentSize().height * 0.05));
		starNormal->setScaleY(0.5);
		panel2->addChild(starNormal);
	}
	//렌주룰 승리 여부 표시
	if (ch->getWinCountRenju() >= 1){
		auto starRenju = Sprite::create("star2.png"); //보통룰 승리 여부를 나타내는 별
		starRenju->setAnchorPoint(Vec2(0, 0));
		starRenju->setPosition(Vec2(panel2->getContentSize().width / 2, panel2->getContentSize().height * 0.05));
		starRenju->setScaleY(0.5);
		panel2->addChild(starRenju);
	}

	auto layout = ui::Layout::create();
	layout->setSize(pageview->getSize());
	layout->addChild(fence);
	fence->setPosition(Vec2(pageview->getSize().width / 2, pageview->getSize().height / 2));

	pageview->addPage(layout);
	charList.push_back(ch);
}

void StageSelectScene::startStage(){
	auto index = dynamic_cast<ui::PageView*>(getChildByName("scene")->getChildByName("pageView"))->getCurPageIndex();
	CpuChar* cpu = NULL;
	for (int i = 0; i < charList.size(); i++){
		if (i == index){
			cpu = charList.at(i);
		}
		else{
			delete charList.at(i);
		}
	}
	OmokScene::startGame(cpu);
}

void StageSelectScene::goToTitleScene(){
	for (int i = 0; i < charList.size(); i++){
		delete charList.at(i);
	}
	saveStagePos();
	TransitionScene* transition = TransitionFade::create(1.0f, OmokTitleScene::createScene());
	Director::getInstance()->replaceScene(transition);
}

void StageSelectScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event){
	if (keyCode == EventKeyboard::KeyCode::KEY_BACK || keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE){
		goToTitleScene();
	}
}

void StageSelectScene::btnTouch(Ref* sender, ui::Widget::TouchEventType type){
	auto node = dynamic_cast<Node*>(sender);
	if (type == ui::Widget::TouchEventType::ENDED){
		//타이틀화면으로
		if (node->getName().compare("btn_return") == 0){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			goToTitleScene();
		}
		//게임시작
		else if (node->getName().compare("btn_start") == 0){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			saveStagePos();
			startStage();
		}
		//오목알 바꾸기
		else if (node->getName().compare("btn_changeStone") == 0){
			//현제화면 터치를 막음
			setTouchEnable(false);
			//효과음
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			//새로운 창 생성
			auto menuWindow = StoneSelect::create();
			addChild(menuWindow, ORDER_STAGESELECT_CHANGESTONE);
		}
	}
	//페이지 넘김
	if (type == ui::Widget::TouchEventType::ENDED || type == ui::Widget::TouchEventType::CANCELED){
		if (node->getName().compare("pageView") == 0){
			auto name = dynamic_cast<ui::Text*>(getChildByName("scene")->getChildByName("Name"));
			auto delay = DelayTime::create(0.4f);
			auto func = CallFunc::create(CC_CALLBACK_0(StageSelectScene::setCharName, this));
			name->runAction(Sequence::createWithTwoActions(delay, func));
		}
	}
}

void StageSelectScene::setCharName(){
	auto scene = getChildByName("scene");
	auto name = dynamic_cast<ui::Text*>(scene->getChildByName("Name"));
	auto pageview = dynamic_cast<ui::PageView*>(scene->getChildByName("pageView"));
	auto ch = charList.at(pageview->getCurPageIndex());
	name->setText(ch->getName());
}

void StageSelectScene::updateCurrentStone(){
	auto stonePanel = getChildByName("scene")->getChildByName("stonePanel");
	if (stonePanel->getChildByName("curStone") != NULL){
		stonePanel->removeChildByName("curStone");
	}
	auto curstone = GameManager::getInstance().getCurrentStone();
	auto imgName = curstone->getImgName1P();
	auto currentStone = Sprite::create(imgName);
	currentStone->setAnchorPoint(ANCHER_CENTER);
	currentStone->setName("curStone");
	currentStone->setPosition(stonePanel->getContentSize().width / 2, stonePanel->getContentSize().height / 2);
	stonePanel->addChild(currentStone);
}

void StageSelectScene::updateMyMoney(){
	auto txt_money = dynamic_cast<ui::Text*>(getChildByName("scene")->getChildByName("txt_money"));
	char msg[32];
	sprintf(msg, "%d원", GameManager::getInstance().getMyMoney());
	txt_money->setText(msg);
}

void StageSelectScene::setTouchEnable(bool enable){
	auto scene = getChildByName("scene");
	auto btn_start = dynamic_cast<ui::Button*>(scene->getChildByName("btn_start"));
	auto btn_goTitle = dynamic_cast<ui::Button*>(scene->getChildByName("btn_return"));
	auto btn_changeStone = dynamic_cast<ui::Button*>(scene->getChildByName("btn_changeStone"));
	auto pageview = dynamic_cast<ui::PageView*>(scene->getChildByName("pageView"));

	btn_start->setTouchEnabled(enable);
	btn_goTitle->setTouchEnabled(enable);
	btn_changeStone->setTouchEnabled(enable);
	pageview->setTouchEnabled(enable);
}

void StageSelectScene::saveStagePos() const{
	auto index = dynamic_cast<ui::PageView*>(getChildByName("scene")->getChildByName("pageView"))->getCurPageIndex();
	UserDefault::getInstance()->setIntegerForKey(DATA_INT_STAGE_SELECT_PAGEINDEX, index);
}
