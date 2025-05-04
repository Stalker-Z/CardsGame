#pragma once

#include <stack>
#include <vector>
#include "CardModel.h"
#include "UndoModel.h"

class LevelModel : public cocos2d::Ref
{
public:
	// 创建关卡
	LevelModel() {}

	static LevelModel* create(int levelId, std::stack<CardModel*>& bottomCards, std::stack<CardModel*>& spareCards, std::list<CardModel*>& mainCards);

	// 底牌牌堆
	std::stack<CardModel*> bottomCards;
	// 备用牌堆
	std::stack<CardModel*> spareCards;
	// 主牌堆
	std::list<CardModel*> mainCards;

	// 回退操作栈
	std::stack<UndoModel> undoOp;
	
	// 获取关卡id
	int getLevelId() const { return _levelId; }

	// 序列化与反序列化
	rapidjson::Value toJson(rapidjson::Document::AllocatorType& allocator);
	static LevelModel* fromJson(int levelId, const rapidjson::Value& json);
private:
	LevelModel(int levelId, std::stack<CardModel*>& bottomCards, std::stack<CardModel*>& spareCards, std::list<CardModel*>& mainCards)
		: _levelId(levelId), bottomCards(bottomCards), spareCards(spareCards), mainCards(mainCards) {
	}

	int _levelId;
};

