#pragma once
#include "D:\cocos2dx-game\CardsGame\CardsGame\cocos2d\cocos\2d\CCSprite.h"

#include "cocos2d.h"
#include "CardConfig.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include <string>

class CardModel : public cocos2d::Ref
{
public:
	// ��������
	static CardModel* create(CardSuitType suit, CardFaceType face, int x, int y, bool isFaceUp = true, bool isSelectable = false);

	// ��ȡ��ɫ
	CardSuitType getSuit() const { return _suit; }
	// ��ȡ����
	CardFaceType getFace() const { return _face; }

	// ״̬�����Ƿ�ɱ�ѡ��
	bool isFaceUp;
	bool isSelectable;

	// λ��
	cocos2d::Vec2 position;
	// ����
	CardPosType pos;

	// ͼ���ļ���ַ
	std::string suitPath;
	std::string bigNumPath;
	std::string smallNumPath;

	int cardId;

	// ���л��뷴���л�
	rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator);
	static CardModel* fromJson(const rapidjson::Value& json);

	bool operator==(const CardModel& rhs) const {
		if (this->cardId == rhs.cardId) {
			return true;
		}
		return false;
	}

private:
	CardModel(CardSuitType suit, CardFaceType face, cocos2d::Vec2 position, bool isFaceUp = true, bool isSelectable = false)
		: _suit(suit), _face(face), position(position), isFaceUp(isFaceUp), isSelectable(isSelectable), pos(CPT_NONE) {
		_getImagePath();
	}

	
	CardSuitType _suit;
	CardFaceType _face;

	void _getImagePath();
};

