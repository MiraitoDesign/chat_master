#ifndef __CHATSCENE_SCENE_H__
#define __CHATSCENE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <WebSocket.h>

USING_NS_CC;
using namespace network;

class ChatScene : public cocos2d::Scene, cocos2d::ui::EditBoxDelegate, WebSocket::Delegate
{
protected:

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void pushsedButton(Ref *pSender);

    void sendMessage();

    // implement the "static create()" method manually
    CREATE_FUNC(ChatScene);

private:
    virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);

    virtual void onOpen(WebSocket* ws);
    virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
    virtual void onClose(WebSocket* ws);
    virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);

    Size visibleSize;
    Point origin;
    cocos2d::ui::EditBox* editBox;
    std::string           sendText;
    WebSocket*            webSocket;
};

#endif // __CHATSCENE_SCENE_H__