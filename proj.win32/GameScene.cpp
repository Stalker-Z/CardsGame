#include "GameScene.h"
#include <ui/UIButton.h>
#include "CardView.h"
#include "base/CCEventDispatcher.h"

USING_NS_CC;

GameScene* GameScene::createScene(LevelModel* nowLevel)
{
    GameScene* scene = new (std::nothrow) GameScene(nowLevel);
    if (scene) {
        scene->autorelease();
        return scene;
    }
    CC_SAFE_DELETE(scene);
    return nullptr;
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 创建上层主牌堆区（高度1500）
    _topLayer = LayerColor::create(Color4B(139, 69, 19, 255), 1080, 1500);
    _topLayer->setPosition(0, 580); // 定位到顶部
    this->addChild(_topLayer, 0);


    // 创建下层备用牌堆+底牌堆区（占580）
    _bottomLayer = LayerColor::create(Color4B(128, 0, 128, 255), 1080, 580);
    _bottomLayer->setPosition(0, 0); // 定位到底部
    this->addChild(_bottomLayer, 0);

    // 创建回退按钮
    setupBackButton();

    setupPlayField();
    setupStack(_nowLevel->bottomCards, _nowLevel->spareCards);

    return true;
}

void GameScene::setupBackButton() {
    auto btn = ui::Button::create();
    btn->setTitleFontName("fonts/simhei.ttf");
    btn->setTitleText(u8"回退");
    btn->setTitleColor(Color3B(255, 255, 255));
    btn->setTitleFontSize(50);
    btn->setPosition(Vec2(950, 300));

    this->addChild(btn, 10);

    btn->addClickEventListener([=](Ref* sender) {
        CCLOG("Button clicked!");
        if (!_nowLevel->undoOp.empty()) this->_onButtonClick();
        });
}

void GameScene::setupPlayField()
{
    for (auto item : _nowLevel->mainCards) {
        auto card = CardView::create(item);
        card->setPosition(card->getPos());
        _topLayer->addChild(card, 10, card->getCardId());
    }
}

void GameScene::setupStack(std::stack<CardModel*> bottom, std::stack<CardModel*> spare)
{
    // 显示备用牌堆
    int layers = 100;
    float posX = 410;
    float posY = 300;
    while (!spare.empty()) {
        auto item = spare.top();
        spare.pop();
        auto card = CardView::create(item);
        card->retain();
        card->model->position = cocos2d::Vec2(posX, posY);
        card->setPosition(cocos2d::Vec2(posX, posY));
        _bottomLayer->addChild(card, layers, card->getCardId());
        layers--;
        posX -= 150;
    }

    // 显示底牌堆
    layers = 50;
    posX = 700;
    while (!bottom.empty()) {
        auto item = bottom.top();
        bottom.pop();
        auto card = CardView::create(item);
        card->model->position = cocos2d::Vec2(posX, posY);
        card->setPosition(cocos2d::Vec2(posX, posY));
        _bottomLayer->addChild(card, layers, card->getCardId());
        layers--;
    }
}

void GameScene::_onButtonClick()
{
    // 创建事件并附加回退数据
    cocos2d::EventCustom event(UNDO_CLICK_EVENT);
    event.setUserData(this); // 传递当前回退操作指针

    // 获取全局事件分发器并发送
    cocos2d::Director::getInstance()
        ->getEventDispatcher()
        ->dispatchEvent(&event);
}
