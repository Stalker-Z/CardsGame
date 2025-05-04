#pragma once
#include "D:\cocos2dx-game\CardsGame\CardsGame\cocos2d\cocos\2d\CCScene.h"

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "LevelManager.h"

class GameScene : public cocos2d::Scene
{
public:
    static GameScene* createScene(LevelModel* nowLevel);

    virtual bool init();

    // 创建回退按钮
    void setupBackButton();
    // 创建主牌堆区
    void setupPlayField();
    // 创建底牌和备用牌堆区
    void setupStack(std::stack<CardModel*> bottom, std::stack<CardModel*> spare);

    // 获取上/下Layer
    cocos2d::Layer* getTopLayer() { return _topLayer; }
    cocos2d::Layer* getBottomLayer() { return _bottomLayer; }

private:
    GameScene(LevelModel* nowLevel) :
        _nowLevel(nowLevel) {
        init();
    }

    void _onButtonClick();

    cocos2d::Layer* _topLayer;    // 上层主牌堆区
    cocos2d::Layer* _bottomLayer; // 下层底牌堆区+备用牌堆区
    LevelModel* _nowLevel;
};

#endif // __GAME_SCENE_H__
