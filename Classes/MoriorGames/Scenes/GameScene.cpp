#include "GameScene.h"

USING_NS_CC;

Scene *GameScene::createScene()
{
    return GameScene::create();
}

/**
 * on "init" you need to initialize your instance
 */
bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    return true;
}
