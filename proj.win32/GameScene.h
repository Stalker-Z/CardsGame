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

    // �������˰�ť
    void setupBackButton();
    // �������ƶ���
    void setupPlayField();
    // �������ƺͱ����ƶ���
    void setupStack(std::stack<CardModel*> bottom, std::stack<CardModel*> spare);

    // ��ȡ��/��Layer
    cocos2d::Layer* getTopLayer() { return _topLayer; }
    cocos2d::Layer* getBottomLayer() { return _bottomLayer; }

private:
    GameScene(LevelModel* nowLevel) :
        _nowLevel(nowLevel) {
        init();
    }

    void _onButtonClick();

    cocos2d::Layer* _topLayer;    // �ϲ����ƶ���
    cocos2d::Layer* _bottomLayer; // �²���ƶ���+�����ƶ���
    LevelModel* _nowLevel;
};

#endif // __GAME_SCENE_H__
