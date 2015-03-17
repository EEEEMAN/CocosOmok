#include "VS2PMenu.h"

bool VS2PMenu::init(){
	if (!Layer::init())
	{
		return false;
	}

	//창 표시
	auto window = CSLoader::getInstance()->createNode("SelectStone2P.csb");
	window->setName("window");
	window->setAnchorPoint(ANCHER_CENTER);
	window->setPosition(POSITION_CENTER);
	window->setScale(Director::getInstance()->getWinSize().width / window->getContentSize().width);
	addChild(window);

	this->setName("VS2PMenu");

	//설정 초기화
	waiting1pSel = false;
	waiting2pSel = false;
	set1PStone("black.png");
	set2PStone("white.png");

	//터치이벤트 설정
	auto changeStone1P = dynamic_cast<ui::Button*>(window->getChildByName("changeStone1P"));
	changeStone1P->addTouchEventListener(CC_CALLBACK_2(VS2PMenu::onTouch, this));
	auto changeStone2P = dynamic_cast<ui::Button*>(window->getChildByName("changeStone2P"));
	changeStone2P->addTouchEventListener(CC_CALLBACK_2(VS2PMenu::onTouch, this));
	auto btn_Cancel = dynamic_cast<ui::Button*>(window->getChildByName("btn_Cancel"));
	btn_Cancel->addTouchEventListener(CC_CALLBACK_2(VS2PMenu::onTouch, this));
	auto btn_GameStart = dynamic_cast<ui::Button*>(window->getChildByName("btn_GameStart"));
	btn_GameStart->addTouchEventListener(CC_CALLBACK_2(VS2PMenu::onTouch, this));

	return true;
}

void VS2PMenu::set1PStone(char* imgName){
	auto window = getChildByName("window");
	auto stonePanel = window->getChildByName("1pStonePanel");
	if (stonePanel->getChildByName("stone1P") != NULL){
		stonePanel->removeChildByName("stone1P");
	}
	auto stoneSprite = Sprite::create(imgName);
	stoneSprite->setName("stone1P");
	stoneSprite->setAnchorPoint(Vec2(0, 0));
	stoneSprite->setPosition(Vec2(0, 0));
	stonePanel->addChild(stoneSprite);

	stoneName1P = imgName;
}

void VS2PMenu::set2PStone(char* imgName){
	auto window = getChildByName("window");
	auto stonePanel = window->getChildByName("2pStonePanel");
	if (stonePanel->getChildByName("stone2P") != NULL){
		stonePanel->removeChildByName("stone2P");
	}
	auto stoneSprite = Sprite::create(imgName);
	stoneSprite->setName("stone2P");
	stoneSprite->setAnchorPoint(Vec2(0, 0));
	stoneSprite->setPosition(Vec2(0, 0));
	stonePanel->addChild(stoneSprite);

	stoneName2P = imgName;
}

void VS2PMenu::onTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
	auto node = dynamic_cast<Node*>(pSender);
	if (type == ui::Widget::TouchEventType::ENDED){
		if (node->getName().compare("changeStone1P") == 0){//1p돌선택
			//현제화면 터치를 막음
			setTouchEnable(false);
			waiting1pSel = true;
			waiting2pSel = false;
			//효과음
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			//돌선택 창 생성
			auto menuWindow = StoneSelect::create();
			addChild(menuWindow);
		}
		else if (node->getName().compare("changeStone2P") == 0){ //2p돌선택
			//현제화면 터치를 막음
			setTouchEnable(false);
			waiting2pSel = true;
			waiting1pSel = false;
			//효과음
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			//돌선택 창 생성
			auto menuWindow = StoneSelect::create();
			addChild(menuWindow);
		}
		else if (node->getName().compare("btn_GameStart") == 0){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			OmokScene::startGame(stoneName1P, stoneName2P);
		}
		else if (node->getName().compare("btn_Cancel") == 0){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			auto parent = (OmokTitleScene*)getParent();
			parent->setTouchEnable(true);
			this->removeFromParentAndCleanup(true);
		}
	}
}

void VS2PMenu::setTouchEnable(bool enable){
	auto window = getChildByName("window");
	auto changeStone1P = dynamic_cast<ui::Button*>(window->getChildByName("changeStone1P"));
	changeStone1P->setTouchEnabled(enable);
	auto changeStone2P = dynamic_cast<ui::Button*>(window->getChildByName("changeStone2P"));
	changeStone2P->setTouchEnabled(enable);
	auto btn_Cancel = dynamic_cast<ui::Button*>(window->getChildByName("btn_Cancel"));
	btn_Cancel->setTouchEnabled(enable);
	auto btn_GameStart = dynamic_cast<ui::Button*>(window->getChildByName("btn_GameStart"));
	btn_GameStart->setTouchEnabled(enable);
}

bool VS2PMenu::isWaiting1pSel() const{
	return waiting1pSel;
}

bool VS2PMenu::isWaiting2pSel() const{
	return waiting2pSel;
}