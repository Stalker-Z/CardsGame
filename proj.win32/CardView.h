#pragma once
#include <cocos2d.h>
#include "CardModel.h"
#include "base/CCEventDispatcher.h"
#include "Event.h"

class CardView :
    public cocos2d::Sprite
{
public:
    // ����������ͼ
    static CardView* create(CardModel* model);   
    
    // ��ȡ��������
    int getNum();

    // ��ȡ����λ����Ϣ
    cocos2d::Vec2 getPos();
    // ���ÿ���λ����Ϣ
    void setPos(cocos2d::Vec2 position);

    // ��ȡ����������Ϣ
    CardPosType getField();
    // ���ÿ���������Ϣ
    void setField(CardPosType field);

    // ������Ϣ
    CardModel* model;

    // ��ȡ����ID
    int getCardId();

    // ���������¼�
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
