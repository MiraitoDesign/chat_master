#ifndef __BUTTON_LAYER_H__
#define __BUTTON_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ButtonLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    CREATE_FUNC(ButtonLayer);
};

#endif // __BUTTON_LAYER_H__
