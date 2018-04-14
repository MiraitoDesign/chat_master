#ifndef __TOP_SCENE_H__
#define __TOP_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Top : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Top);
};

#endif // __TOP_SCENE_H__
