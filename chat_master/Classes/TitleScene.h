#ifndef PROJ_ANDROID_STUDIO_TITLE_H
#define PROJ_ANDROID_STUDIO_TITLE_H

#include "cocos2d.h"

class Title : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void btnCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Title);
};


#endif //PROJ_ANDROID_STUDIO_TITLE_H
