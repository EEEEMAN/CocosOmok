#include "OmokTitleScene.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

Scene* OmokTitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = OmokTitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool OmokTitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getVisibleSize();

	//admob
	if (!AdmobHelper::isAdShowing){
		AdmobHelper::showAd();
	}
	//GameManager설정
	GameManager::getInstance().setSceneState(SCENE_TITLE);

	GameManager::getInstance().sound->stopBackgroundMusic();
	GameManager::getInstance().sound->playBackgroundMusic(BGM_TITLE, true);

	auto title = CSLoader::createNode("Title.csb");
	title->setScaleX(winSize.width / title->getContentSize().width);
	title->setScaleY(winSize.height / title->getContentSize().height);
	title->setAnchorPoint(Vec2(0.5, 0.5));
	title->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	title->setName("title");
	this->addChild(title, ORDER_TITLE_BACKGROUND);

	auto anim = CSLoader::createTimeline("Title.csb");
	anim->gotoFrameAndPlay(0, false);
	title->runAction(anim);

	auto listview = dynamic_cast<ui::ListView*>(title->getChildByName("ListView"));
	//버튼이벤트
	auto btn_1p = dynamic_cast<ui::Button*>(listview->getChildByName("btn_1p"));
	btn_1p->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			TransitionScene* transition = TransitionFade::create(1.0f, StageSelectScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	auto btn_2p = dynamic_cast<ui::Button*>(listview->getChildByName("btn_2p"));
	btn_2p->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			setTouchEnable(false);
			auto layer = VS2PMenu::create();
			addChild(layer, ORDER_TITLE_OPTION);
		}
	});
	auto btn_exit = dynamic_cast<ui::Button*>(listview->getChildByName("btn_exit"));
	btn_exit->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			Director::getInstance()->end();
		}
	});
	auto btn_option = dynamic_cast<ui::Button*>(listview->getChildByName("btn_option"));
	btn_option->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
		if (type == ui::Widget::TouchEventType::ENDED){
			GameManager::getInstance().sound->playEffect(EFFECT_SELECT);
			setTouchEnable(false);
			auto layer = OmokOption::create();
			addChild(layer, ORDER_TITLE_OPTION);
		}
	});

	return true;
}


void OmokTitleScene::setTouchEnable(bool enable){
	//터치를 막음
	ui::ListView* list = dynamic_cast<ui::ListView*>(getChildByName("title")->getChildByName("ListView"));
	auto menulist = list->getChildren();
	for (int i = 0; i < menulist.size(); i++){
		dynamic_cast<ui::Button*>(menulist.at(i))->setTouchEnabled(enable);
	}
	list->setTouchEnabled(enable);
}