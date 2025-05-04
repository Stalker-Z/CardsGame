#include "UndoModel.h"

UndoModel* UndoModel::create(int cardId, cocos2d::Vec2 lastPos, CardPosType lastField, int lastZOrder, int lastBottomNum)
{
    UndoModel* model = new (std::nothrow)  UndoModel(cardId, lastPos, lastField, lastZOrder, lastBottomNum);
    if (model) {
        model->autorelease();
        return model;
    }
    CC_SAFE_DELETE(model);
    return nullptr;
}
