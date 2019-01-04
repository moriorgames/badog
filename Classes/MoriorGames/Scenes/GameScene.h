#ifndef MORIOR_GAMES_SCENES_GAME_SCENE_H
#define MORIOR_GAMES_SCENES_GAME_SCENE_H

#include "cocos2d.h"

class GameScene: public cocos2d::Scene
{
public:
    static cocos2d::Scene *createScene();

    virtual bool init();

    CREATE_FUNC(GameScene);
};

#endif
