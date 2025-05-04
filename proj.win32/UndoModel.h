#pragma once

#include "CardConfig.h"
#include <cocos2d.h>

class UndoModel : public cocos2d::Ref
{
public:
	static UndoModel* create(int cardId, cocos2d::Vec2 lastPos, CardPosType lastField, int lastZOrder, int lastBottomNum);

	// ��ȡ����ID
	int getCardId() const { return _cardId; }
	// ��ȡ���Ʋ���ǰλ��
	cocos2d::Vec2 getLastPos() const { return _lastPos; }
	// ��ȡ���Ʋ���ǰ����
	CardPosType getLastField() const { return _lastField; }
	// ��ȡ���Ʋ���ǰ����
	int getLastZOrder() const { return _lastZOrder; }
	// ��ȡ���Ʋ���ǰ���ƶ�����ֵ
	int getLastBottomNum() const { return _lastBottomNum; }

private:
	UndoModel(int cardId, cocos2d::Vec2 lastPos, CardPosType lastField, int lastZOrder, int lastBottomNum) :
		_cardId(cardId), _lastPos(lastPos), _lastField(lastField), _lastZOrder(lastZOrder), _lastBottomNum(lastBottomNum) {	}
	// ����ID
	int _cardId;
	// ����ǰλ��
	cocos2d::Vec2 _lastPos;
	// ����ǰ����
	CardPosType _lastField;
	// ����ǰ����
	int _lastZOrder;
	// ����ǰ���ƶ�����ֵ
	int _lastBottomNum;
};

