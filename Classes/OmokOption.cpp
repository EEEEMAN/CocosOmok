#include "OmokOption.h"

USING_NS_CC;

bool OmokOption::init(){
	if (!Layer::init())
	{
		return false;
	}

	auto layer = CSLoader::createNode("Option.csb");
	layer->setName("layerpan");
	layer->setAnchorPoint(ANCHER_CENTER);
	layer->setPosition(POSITION_CENTER);
	layer->setScale(Director::getInstance()->getWinSize().width / layer->getContentSize().width);
	addChild(layer);

	//현재상태를 설정창에 시각화
	auto slider_BGM = dynamic_cast<ui::Slider*>(layer->getChildByName("Slider_BGM"));
	auto slider_Effect = dynamic_cast<ui::Slider*>(layer->getChildByName("Slider_Effect"));
	auto cb_renju = dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_Renju"));
	auto cb_33 = dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_33"));
	auto cb_44 = dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_44"));
	auto cb_6mok = dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_6mok"));
	float bgmvol = (int)(GameManager::getInstance().sound->getBackgroundMusicVolume() * 100); //BGM
	slider_BGM->setPercent(bgmvol);
	float effvol = (int)(GameManager::getInstance().sound->getEffectsVolume() * 100); //효과음
	slider_Effect->setPercent(effvol);
	cb_renju->setSelectedState(GameManager::getInstance().isRuleRenju()); //렌주룰 적용여부 시각화
	cb_renju->addTouchEventListener(CC_CALLBACK_2(OmokOption::onTouch, this));
	if (GameManager::getInstance().isRuleRenju()){ //렌주룰이 체크되어있으면 세부규칙 수정불가
		cb_33->setBright(false);
		cb_44->setBright(false);
		cb_6mok->setBright(false);
		cb_33->setTouchEnabled(false);
		cb_44->setTouchEnabled(false);
		cb_6mok->setTouchEnabled(false);
	}
	else{ //렌주룰이 체크되어있지 않으면 세부규칙 적용여부 시각화
		cb_33->setSelectedState(GameManager::getInstance().isRule33());
		cb_44->setSelectedState(GameManager::getInstance().isRule44());
		cb_6mok->setSelectedState(GameManager::getInstance().isRule6mok());
	}

	//닫기버튼 설정
	auto btn_close = dynamic_cast<ui::Button*>(layer->getChildByName("btn_close"));
	btn_close->addTouchEventListener(CC_CALLBACK_2(OmokOption::onTouch, this));

	//도움말버튼 설정
	auto btn_help = dynamic_cast<ui::Button*>(layer->getChildByName("btn_help"));
	btn_help->addTouchEventListener(CC_CALLBACK_2(OmokOption::onTouch, this));

	//볼륨조절 설정
	slider_BGM->addTouchEventListener(CC_CALLBACK_2(OmokOption::onTouch, this));
	slider_Effect->addTouchEventListener(CC_CALLBACK_2(OmokOption::onTouch, this));

	return true;
}

void OmokOption::onTouch(Ref* pSender, ui::Widget::TouchEventType type){
	auto gm = &GameManager::getInstance();
	cocos2d::log("%d,%d,%d,%d", gm->isRule33(), gm->isRule44(), gm->isRule6mok(), gm->isRuleRenju());
	auto node = dynamic_cast<Node*>(pSender);
	if (type == ui::Widget::TouchEventType::ENDED){
		//BGM슬라이더
		if (node->getName().compare("Slider_BGM") == 0){
			int percent = dynamic_cast<ui::Slider*>(node)->getPercent();
			float volume = (float)percent / 100;
			UserDefault::getInstance()->setFloatForKey(OPTION_FLOAT_BGM, volume);
			UserDefault::getInstance()->flush();
			GameManager::getInstance().sound->setBackgroundMusicVolume(volume);
		}
		//효과음슬라이더
		else if (node->getName().compare("Slider_Effect") == 0){
			int percent = dynamic_cast<ui::Slider*>(node)->getPercent();
			float volume = (float)percent / 100;
			UserDefault::getInstance()->setFloatForKey(OPTION_FLOAT_EFFECT, volume);
			UserDefault::getInstance()->flush();
			GameManager::getInstance().sound->setEffectsVolume(volume);
		}
		//도움말버튼
		else if (node->getName().compare("btn_help") == 0){
			auto help = CSLoader::createNode("HelpRenjuRule.csb");
			auto anim = CSLoader::createTimeline("HelpRenjuRule.csb");
			anim->gotoFrameAndPlay(0, false);
			help->setName("help");
			auto btn = dynamic_cast<ui::Button*>(help->getChildByName("btn_close"));
			btn->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type){
				if (type == ui::Widget::TouchEventType::ENDED){
					if (this->getChildByName("help") != NULL){
						this->setTouchEnable(true);
						this->removeChildByName("help");
					}
				}
			});
			auto winSize = Director::getInstance()->getWinSize();
			help->setAnchorPoint(Vec2(0.5, 0.5));
			help->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
			this->addChild(help);
			this->setTouchEnable(false);
			help->runAction(anim);
		}
		//Renju룰 체크박스
		else if (node->getName().compare("CheckBox_Renju") == 0){
			auto cb_renju = dynamic_cast<ui::CheckBox*>(node);
			auto cb_33 = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_33"));
			auto cb_44 = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_44"));
			auto cb_6mok = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_6mok"));
			if (cb_renju->getSelectedState()){
				cb_33->setBright(true);
				cb_44->setBright(true);
				cb_6mok->setBright(true);
				cb_33->setTouchEnabled(true);
				cb_44->setTouchEnabled(true);
				cb_6mok->setTouchEnabled(true);
			}
			else{
				cb_33->setBright(false);
				cb_44->setBright(false);
				cb_6mok->setBright(false);
				cb_33->setTouchEnabled(false);
				cb_44->setTouchEnabled(false);
				cb_6mok->setTouchEnabled(false);
			}
		}
		//닫기버튼
		else if (node->getName().compare("btn_close") == 0){
			//체크박스 설정 적용
			auto cb_renju = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_Renju"));
			if (cb_renju->getSelectedState()){
				GameManager::getInstance().setRuleRenju(true);
			}
			else{
				auto cb_33 = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_33"));
				auto cb_44 = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_44"));
				auto cb_6mok = dynamic_cast<ui::CheckBox*>(getChildByName("layerpan")->getChildByName("CheckBox_6mok"));
				GameManager::getInstance().setRuleRenju(false);
				GameManager::getInstance().setRule33(cb_33->getSelectedState());
				GameManager::getInstance().setRule44(cb_44->getSelectedState());
				GameManager::getInstance().setRule6mok(cb_6mok->getSelectedState());
			}

			//닫기
			OmokTitleScene* parent = dynamic_cast<OmokTitleScene*>(getParent());
			parent->setTouchEnable(true);
			this->removeFromParentAndCleanup(true);
		}
	}
}

void OmokOption::setTouchEnable(bool enable){
	auto layer = getChildByName("layerpan");

	//현재상태를 설정창에 시각화
	dynamic_cast<ui::Slider*>(layer->getChildByName("Slider_BGM"))->setTouchEnabled(enable);
	dynamic_cast<ui::Slider*>(layer->getChildByName("Slider_Effect"))->setTouchEnabled(enable);
	dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_Renju"))->setTouchEnabled(enable);
	dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_33"))->setTouchEnabled(enable);
	dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_44"))->setTouchEnabled(enable);
	dynamic_cast<ui::CheckBox*>(layer->getChildByName("CheckBox_6mok"))->setTouchEnabled(enable);
	dynamic_cast<ui::Button*>(layer->getChildByName("btn_close"))->setTouchEnabled(enable);
	dynamic_cast<ui::Button*>(layer->getChildByName("btn_help"))->setTouchEnabled(enable);
}