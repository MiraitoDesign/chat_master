#ifndef __CHAT_SCENE_H__
#define __CHAT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <WebSocket.h>

USING_NS_CC;
using namespace ui;
using namespace network;

class Chat : public cocos2d::Scene, cocos2d::ui::EditBoxDelegate, WebSocket::Delegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(Chat);
private:
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    void addChatMessage(cocos2d::ui::ScrollView *view, std::string message);

    WebSocket* webSocket;
    ScrollView* scrollView;
};

#endif // __CHAT_SCENE_H__
