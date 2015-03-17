#include "StoneSelect.h"

bool StoneSelect::init(){
	if (!Layer::init())
	{
		return false;
	}

	auto window = CSLoader::getInstance()->createNode("SelectStone.csb");
	window->setName("window");
	window->setAnchorPoint(ANCHER_CENTER);
	window->setPosition(POSITION_CENTER);
	window->setScale(Director::getInstance()->getWinSize().width / window->getContentSize().width);
	addChild(window);

	//현재 가지고있는 돌 표시
	auto gm = &GameManager::getInstance();
	for (int i = 0; i < GameManager::getInstance().stoneList.size(); i++){
		auto stone = gm->getStoneByID(gm->stoneList.at(i));
		addStone(stone);
	}

	//닫기버튼 설정
	dynamic_cast<ui::Button*>(window->getChildByName("btn_close"))->addTouchEventListener(CC_CALLBACK_2(StoneSelect::onTouch, this));

	return true;
}

void StoneSelect::addStone(Stone* stone){
	auto list = dynamic_cast<ui::ListView*>(getChildByName("window")->getChildByName("ListView"));
	if (list == NULL) return;
	//오목알이미지 생성
	char* imgName = stone->getImgName1P();
	auto stoneSpr = ui::Button::create(imgName, imgName, imgName, ui::Widget::TextureResType::LOCAL);
	stoneSpr->addTouchEventListener(CC_CALLBACK_2(StoneSelect::onTouch, this));
	stoneSpr->setTag(stone->getStoneID());
	stoneSpr->setName("stone");

	list->pushBackCustomItem(stoneSpr);
}

void StoneSelect::onTouch(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType type){
	auto node = dynamic_cast<Node*>(pSender);
	if (type == ui::Widget::TouchEventType::ENDED){
		if (getParent()->getName().compare("StageSelectScene") == 0){
			//닫기버튼
			if (node->getName().compare("btn_close") == 0){
				auto parent = (StageSelectScene*)getParent();
				parent->setTouchEnable(true);
				this->removeFromParentAndCleanup(true);
			}
			//돌 선택
			else if (node->getName().compare("stone") == 0){
				GameManager::getInstance().setCurrentStone(GameManager::getInstance().getStoneByID((StoneID)node->getTag()));
				auto parent = (StageSelectScene*)getParent();
				parent->setTouchEnable(true);
				parent->updateCurrentStone();
				this->removeFromParentAndCleanup(true);
			}
		}
		else if (getParent()->getName().compare("VS2PMenu") == 0){
			//닫기버튼
			if (node->getName().compare("btn_close") == 0){
				auto parent = (VS2PMenu*)getParent();
				parent->setTouchEnable(true);
				this->removeFromParentAndCleanup(true);
			}
			//돌 선택
			else if (node->getName().compare("stone") == 0){
				auto stone = GameManager::getInstance().getStoneByID((StoneID)node->getTag());
				auto parent = (VS2PMenu*)getParent();
				if (parent->isWaiting1pSel() && !parent->isWaiting2pSel()){
					parent->set1PStone(stone->getImgName1P());
				}
				else if (!parent->isWaiting1pSel() && parent->isWaiting2pSel()){
					parent->set2PStone(stone->getImgName2P());
				}
				parent->setTouchEnable(true);
				this->removeFromParentAndCleanup(true);
			}
		}
	}
}