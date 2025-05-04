#pragma once

#include <stack>
#include <vector>
#include "CardModel.h"
#include "UndoModel.h"

class LevelModel : public cocos2d::Ref
{
public:
	// �����ؿ�
	LevelModel() {}

	static LevelModel* create(int levelId, std::stack<CardModel*>& bottomCards, std::stack<CardModel*>& spareCards, std::list<CardModel*>& mainCards);

	// �����ƶ�
	std::stack<CardModel*> bottomCards;
	// �����ƶ�
	std::stack<CardModel*> spareCards;
	// ���ƶ�
	std::list<CardModel*> mainCards;

	// ���˲���ջ
	std::stack<UndoModel> undoOp;
	
	// ��ȡ�ؿ�id
	int getLevelId() const { return _levelId; }

	// ���л��뷴���л�
	rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator);
	static LevelModel* fromJson(int levelId, const rapidjson::Value& json);
private:
	LevelModel(int levelId, std::stack<CardModel*>& bottomCards, std::stack<CardModel*>& spareCards, std::list<CardModel*>& mainCards)
		: _levelId(levelId), bottomCards(bottomCards), spareCards(spareCards), mainCards(mainCards) {
	}

	int _levelId;
};

