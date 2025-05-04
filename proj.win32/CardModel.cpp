#include "CardModel.h"

CardModel* CardModel::create(CardSuitType suit, CardFaceType face, int x, int y, bool isFaceUp, bool isSelectable)
{
    cocos2d::Vec2 position;
    position.x = x;
    position.y = y;
    CardModel* model = new (std::nothrow) CardModel(suit, face, position, isFaceUp, isSelectable);
    if (model) {
        model->autorelease();
        return model;
    }
    CC_SAFE_DELETE(model);
    return nullptr;
}

rapidjson::Value CardModel::toJson(rapidjson::Document::AllocatorType& allocator) {
    rapidjson::Value obj(rapidjson::kObjectType);
    obj.AddMember("CardSuit", static_cast<int>(_suit), allocator);
    obj.AddMember("CardFace", static_cast<int>(_face), allocator);
    rapidjson::Value posObj(rapidjson::kObjectType);
    posObj.AddMember("x", static_cast<int>(position.x), allocator);
    posObj.AddMember("y", static_cast<int>(position.y), allocator);
    obj.AddMember("Position", posObj, allocator);
    return obj;
}

CardModel* CardModel::fromJson(const rapidjson::Value& json) {
    return create(
        static_cast<CardSuitType>(json["CardSuit"].GetInt()),
        static_cast<CardFaceType>(json["CardFace"].GetInt()),
        json["Position"]["x"].GetInt(),
        json["Position"]["y"].GetInt(),
        true,
        false
    );
}

void CardModel::_getImagePath()
{
    std::string color = "";
    switch (this->_suit) {
    case CST_CLUBS:
        suitPath = "suits/club.png";
        color = "black";
        break;
    case CST_DIAMONDS:
        suitPath = "suits/diamond.png";
        color = "red";
        break;
    case CST_HEARTS:
        suitPath = "suits/heart.png";
        color = "red";
        break;
    case CST_SPADES:
        suitPath = "suits/spade.png";
        color = "black";
        break;
    }

    switch (this->_face) {
    case CFT_ACE:
        bigNumPath = "number/big_" + color + "_" + "A.png";
        smallNumPath = "number/small_" + color + "_" + "A.png";
        break;
    case CFT_TWO:
        bigNumPath = "number/big_" + color + "_" + "2.png";
        smallNumPath = "number/small_" + color + "_" + "2.png";
        break;
    case CFT_THREE:
        bigNumPath = "number/big_" + color + "_" + "3.png";
        smallNumPath = "number/small_" + color + "_" + "3.png";
        break;
    case CFT_FOUR:
        bigNumPath = "number/big_" + color + "_" + "4.png";
        smallNumPath = "number/small_" + color + "_" + "4.png";
        break;
    case CFT_FIVE:
        bigNumPath = "number/big_" + color + "_" + "5.png";
        smallNumPath = "number/small_" + color + "_" + "5.png";
        break;
    case CFT_SIX:
        bigNumPath = "number/big_" + color + "_" + "6.png";
        smallNumPath = "number/small_" + color + "_" + "6.png";
        break;
    case CFT_SEVEN:
        bigNumPath = "number/big_" + color + "_" + "7.png";
        smallNumPath = "number/small_" + color + "_" + "7.png";
        break;
    case CFT_EIGHT:
        bigNumPath = "number/big_" + color + "_" + "8.png";
        smallNumPath = "number/small_" + color + "_" + "8.png";
        break;
    case CFT_NINE:
        bigNumPath = "number/big_" + color + "_" + "9.png";
        smallNumPath = "number/small_" + color + "_" + "9.png";
        break;
    case CFT_TEN:
        bigNumPath = "number/big_" + color + "_" + "10.png";
        smallNumPath = "number/small_" + color + "_" + "10.png";
        break;
    case CFT_JACK:
        bigNumPath = "number/big_" + color + "_" + "J.png";
        smallNumPath = "number/small_" + color + "_" + "J.png";
        break;
    case CFT_QUEEN:
        bigNumPath = "number/big_" + color + "_" + "Q.png";
        smallNumPath = "number/small_" + color + "_" + "Q.png";
        break;
    case CFT_KING:
        bigNumPath = "number/big_" + color + "_" + "K.png";
        smallNumPath = "number/small_" + color + "_" + "K.png";
        break;
    }
}
