#include "LevelManager.h"
#include "json/document.h"

LevelManager::LevelManager()
{
    loadLevel("LevelConfig.json");
}

bool LevelManager::loadLevel(const std::string& configFilePath)
{
    std::string jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(configFilePath);
    rapidjson::Document doc;
    doc.Parse(jsonStr.c_str());

    if (doc.HasParseError() || !doc.IsObject()) {
        CCLOG("json error");
        return false;
    }

    _levelData.push_back(*LevelModel::fromJson(1, doc));
    return true;
}

LevelModel LevelManager::getLevel(int levelId)
{
    return _levelData[levelId-1];
}
