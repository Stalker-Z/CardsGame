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

    void startGame(int levelId); // ����ؿ���ţ���ʼ��Ϸ
    void handleCardClick(CardView* card);  // �����������¼�
    void handleUndoClick(GameScene* scene);  // �����������¼�
    void moveCardToTarget(CardView* card);  // ������ƺ��ƶ�����

private:
    LevelManager _levelManager;
    LevelModel _model;
    GameScene* _scene;
    int _bottomTopNum;
    int _layer;
};

