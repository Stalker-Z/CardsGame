#include "LevelModel.h"

LevelModel* LevelModel::create(int levelId, std::stack<CardModel*>& bottomCards, std::stack<CardModel*>& spareCards, std::list<CardModel*>& mainCards)
{
    LevelModel* model = new (std::nothrow) LevelModel(levelId, bottomCards, spareCards, mainCards);
    if (model) {
        model->autorelease();
        return model;
    }
    CC_SAFE_DELETE(model);
    return nullptr;
}

rapidjson::Value LevelModel::toJson(rapidjson::Document::AllocatorType& allocator)
{
    rapidjson::Value obj(rapidjson::kObjectType);

    rapidjson::Value aobj(rapidjson::kArrayType);
    for (auto i : this->mainCards) {
        aobj.PushBack(i->toJson(allocator), allocator);
    }
    obj.AddMember("Playfield", aobj, allocator);

    rapidjson::Value bobj(rapidjson::kArrayType);
    auto bottom = this->bottomCards;
    auto spare = this->spareCards;
    obj.AddMember("Stack", bobj, allocator);

    return obj;
}

LevelModel* LevelModel::fromJson(int levelId, const rapidjson::Value& json)
{
    std::stack<CardModel*> bottom;
    std::stack<CardModel*> spare;
    std::list<CardModel*> main;
    int count = 0;
    for (auto& i : json["Playfield"].GetArray()) {
        auto item = CardModel::fromJson(i);
        item->pos = CPT_MAIN;
        item->isSelectable = true;
        item->cardId = count;
        item->retain();
        count++;
        main.push_back(item);
    }
    for (auto& i : json["Stack"].GetArray()) {
        auto item = CardModel::fromJson(i);
        item->pos = CPT_SPARE;
        item->isSelectable = false;
        item->cardId = count;
        item->retain();
        count++;
        spare.push(item);
    }
    auto item = spare.top();
    item->isSelectable = true;
    item->pos = CPT_BOTTOM;
    bottom.push(item);
    spare.pop();
    spare.top()->isSelectable = true;
    return create(levelId, bottom, spare, main);
}
