#include "GameController.h"
#include "CardView.h"
#include "cocos2d.h"
#include "Judge.h"


void GameController::startGame(int levelId) {
    _model = _levelManager.getLevel(levelId);
    _bottomTopNum = _model.bottomCards.top()->getFace();
    _layer = 51;

    // 创建游戏视图
    auto director = cocos2d::Director::getInstance();
    auto glview = director->getOpenGLView();
    
    glview = cocos2d::GLViewImpl::createWithRect("CardsGame", cocos2d::Rect(0, 0, 1080, 2080), 0.5);
    glview->setDesignResolutionSize(1080, 2080, ResolutionPolicy::FIXED_WIDTH);
    director->setOpenGLView(glview);
    
    _scene = GameScene::createScene(&_model);
    director->runWithScene(_scene);

    auto dispatcherCard = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcherCard->addCustomEventListener(CARD_CLICK_EVENT, [this](cocos2d::EventCustom* event) {
        auto card = static_cast<CardView*>(event->getUserData());
        this->handleCardClick(card);
    });

    auto dispatcherUndo = cocos2d::Director::getInstance()->getEventDispatcher();
    dispatcherUndo->addCustomEventListener(UNDO_CLICK_EVENT, [this](cocos2d::EventCustom* event) {
        auto scene = static_cast<GameScene*>(event->getUserData());
        this->handleUndoClick(scene);
        });
}


void GameController::handleCardClick(CardView* card) {
    CCLOG("HANDLE");
    if (card) {
        if (card->getField() != CPT_BOTTOM) {
            this->moveCardToTarget(card);
        }
    }
}

void GameController::handleUndoClick(GameScene* scene)
{
    auto undo = this->_model.undoOp.top();
    auto card = (CardView*) scene->getBottomLayer()->getChildByTag(undo.getCardId());
    auto targetPos = undo.getLastPos();
    if (undo.getLastField() == CPT_MAIN) {
        card->retain();
        scene->getBottomLayer()->removeChild(card);
        scene->addChild(card, 200);
        card->setPosition(card->getPos());

        auto callback = cocos2d::CallFunc::create([=]() {
            scene->removeChild(card);
            card->setPos(targetPos);
            scene->getTopLayer()->addChild(card, undo.getLastZOrder(), card->getCardId());
            card->setPosition(targetPos);
            });
        auto moveAction = cocos2d::MoveTo::create(0.4f, cocos2d::Vec2(targetPos.x, targetPos.y + 580));
        auto sequence = cocos2d::Sequence::create(moveAction, callback, nullptr);
        card->runAction(sequence);
    }
    else {
        card->setLocalZOrder(undo.getLastZOrder());
        card->setPos(targetPos);
        auto callback = cocos2d::CallFunc::create([=]() {
            card->setPosition(targetPos);
            });
        auto moveAction = cocos2d::MoveTo::create(0.2f, targetPos);
        auto sequence = cocos2d::Sequence::create(moveAction, callback, nullptr);
        card->runAction(sequence);
    }

    card->setField(undo.getLastField());
    this->_model.bottomCards.pop();
    if (card->getField() == CPT_MAIN) {
        this->_model.mainCards.push_back(card->model);
    }
    else {
        if (!this->_model.spareCards.empty()) this->_model.spareCards.top()->isSelectable = false;
        this->_model.spareCards.push(card->model);
    }

    _bottomTopNum = undo.getLastBottomNum();
    this->_model.undoOp.pop();
    _layer--;
}

void GameController::moveCardToTarget(CardView* card) {
    // 计算目标位置（示例：从 topLayer 移动到底部）
    auto targetPos = cocos2d::Vec2(700, 300);
    auto moveTarget = cocos2d::Vec2(700, -280);

    // 控制卡牌移动
    if (card->getField() == CPT_MAIN) {
        if (!Judge::judgeNumber(card->getNum(), _bottomTopNum)) return;
        CCLOG("MAIN");
        const auto option = UndoModel::create(card->getCardId(), card->getPos(), card->getField(), card->getLocalZOrder(), _bottomTopNum);
        this->_model.undoOp.push(*option);
        card->retain();
        this->_scene->getTopLayer()->removeChild(card, false);
        this->_scene->addChild(card, _layer);
        card->setPosition(cocos2d::Vec2(card->getPos().x, card->getPos().y + 580));
        auto callback = cocos2d::CallFunc::create([=]() {
            this->_scene->removeChild(card);
            card->setPos(targetPos);
            this->_scene->getBottomLayer()->addChild(card, _layer, card->getCardId());
            card->setPosition(targetPos);
            });
        auto moveAction = cocos2d::MoveTo::create(0.4f, targetPos);
        auto sequence = cocos2d::Sequence::create(moveAction, callback, nullptr);
        card->runAction(sequence);
        this->_layer++;
        
    }
    else {
        CCLOG("SPARE");
        auto const option = UndoModel::create(card->getCardId(), card->getPos(), card->getField(), card->getLocalZOrder(), _bottomTopNum);
        this->_model.undoOp.push(*option);
        card->setZOrder(_layer);
        _layer++;
        card->setPos(targetPos);
        auto callback = cocos2d::CallFunc::create([=]() {
            card->setPosition(targetPos);
            });
        auto moveAction = cocos2d::MoveTo::create(0.2f, targetPos);
        auto sequence = cocos2d::Sequence::create(moveAction, callback, nullptr);
        card->runAction(sequence);
    }
    

    // 更新游戏逻辑状态
    this->_bottomTopNum = card->getNum();
    this->_model.bottomCards.push(card->model);
    if (card->getField() == CPT_MAIN) {
        this->_model.mainCards.remove(card->model);
    }
    else {
        this->_model.spareCards.pop();
        if (!this->_model.spareCards.empty())
        {
            this->_model.spareCards.top()->isSelectable = true;
        }
    }
    card->setField(CPT_BOTTOM);    
}