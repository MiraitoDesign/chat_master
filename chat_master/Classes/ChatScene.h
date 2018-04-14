#ifndef __CHAT_SCENE_H__
#define __CHAT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Chat : public cocos2d::Scene, cocos2d::ui::EditBoxDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(Chat);
private:
   virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
   virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
   virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
   virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};

#endif // __CHAT_SCENE_H__
