//
// Created by Nobuhiro Kobayashi on 2018/04/14.
//

#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void setContents();

    void pushStartButton(Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartMenu);
};

#endif // __STARTMENU_SCENE_H__


