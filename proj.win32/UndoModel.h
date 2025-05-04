#pragma once

#include "CardConfig.h"
#include <cocos2d.h>

class UndoModel : public cocos2d::Ref
{
public:
	static UndoModel* create(int cardId, cocos2d::Vec2 lastPos, CardPosType lastField, int lastZOrder, int lastBottomNum);

	// 获取卡牌ID
	int getCardId() const { return _cardId; }
	// 获取卡牌操作前位置
	cocos2d::Vec2 getLastPos() const { return _lastPos; }
	// 获取卡牌操作前区域
	CardPosType getLastField() const { return _lastField; }
	// 获取卡牌操作前层数
	int getLastZOrder() const { return _lastZOrder; }
	// 获取卡牌操作前底牌堆面数值
	int getLastBottomNum() const { return _lastBottomNum; }

private:
	UndoModel(int cardId, cocos2d::Vec2 lastPos, CardPosType lastField, int lastZOrder, int lastBottomNum) :
		_cardId(cardId), _lastPos(lastPos), _lastField(lastField), _lastZOrder(lastZOrder), _lastBottomNum(lastBottomNum) {	}
	// 卡牌ID
	int _cardId;
	// 操作前位置
	cocos2d::Vec2 _lastPos;
	// 操作前区域
	CardPosType _lastField;
	// 操作前层数
	int _lastZOrder;
	// 操作前底牌堆面数值
	int _lastBottomNum;
};

