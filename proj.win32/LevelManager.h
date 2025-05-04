#pragma once
#include <string>
#include <vector>
#include <cocos2d.h>
#include "LevelModel.h"

class LevelManager :public cocos2d::Ref
{
public:
	LevelManager();
	bool loadLevel(const std::string& configFilePath);  // ��json�ļ�����عؿ�����
	LevelModel getLevel(int levelId);   // ���ݹؿ�IDȡ�ö�Ӧ�ؿ�����
private:
	std::vector<LevelModel> _levelData;
};
