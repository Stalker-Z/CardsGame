#pragma once
#include "LevelModel.h"
#include "CardView.h"
#include "GameScene.h"
#include "base/CCEventDispatcher.h"
#include "Event.h"

class GameController : public cocos2d::Node
{
public:
    GameController() {};

    void startGame(int levelId); // 输入关卡序号，开始游戏
    void handleCardClick(CardView* card);  // 处理点击卡牌事件
    void handleUndoClick(GameScene* scene);  // 处理点击回退事件
    void moveCardToTarget(CardView* card);  // 点击卡牌后移动卡牌

private:
    LevelManager _levelManager;
    LevelModel _model;
    GameScene* _scene;
    int _bottomTopNum;
    int _layer;
};

