#pragma once
#include <cocos2d.h>
#include "CardModel.h"
#include "base/CCEventDispatcher.h"
#include "Event.h"

class CardView :
    public cocos2d::Sprite
{
public:
    // 创建卡牌视图
    static CardView* create(CardModel* model);   
    
    // 获取卡牌数字
    int getNum();

    // 获取卡牌位置信息
    cocos2d::Vec2 getPos();
    // 设置卡牌位置信息
    void setPos(cocos2d::Vec2 position);

    // 获取卡牌区域信息
    CardPosType getField();
    // 设置卡牌区域信息
    void setField(CardPosType field);

    // 卡牌信息
    CardModel* model;

    // 获取卡牌ID
    int getCardId();

    // 监听触摸事件
    void setupTouch();

private:
    CardView(CardModel* model, cocos2d::Sprite* front, cocos2d::Sprite* back)
        : model(model), _front(front), _back(back) {
        this->setContentSize(front->getContentSize());
        this->addChild(front, 0);
        this->addChild(back, -1);
        _cardId = model->cardId;
        setupTouch();
    }

    void _onClick();

    int _cardId;
    
    cocos2d::Sprite* _front;
    cocos2d::Sprite* _back;
};
