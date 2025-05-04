#pragma once
#include <string>
#include <vector>
#include <cocos2d.h>
#include "LevelModel.h"

class LevelManager :public cocos2d::Ref
{
public:
	LevelManager();
	bool loadLevel(const std::string& configFilePath);  // 从json文件里加载关卡数据
	LevelModel getLevel(int levelId);   // 根据关卡ID取得对应关卡数据
private:
	std::vector<LevelModel> _levelData;
};
