//
// Created by Nobuhiro Kobayashi on 2018/04/22.
//

#include <cocos-ext.h>
#include "ChatScene.h"


USING_NS_CC;

Scene* ChatScene::createScene()
{
    return ChatScene::create();
}

bool ChatScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // GUI
    Label* displayText = Label::createWithSystemFont("", "fonts/arial.ttf", 24);
    displayText->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
    displayText->setPosition(Vec2(origin.x, origin.y + visibleSize.height -180));
    displayText->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
    displayText->setVerticalAlignment(cocos2d::TextVAlignment::TOP);

    this->addChild(displayText);

    // set polygon for editBox
    DrawNode* draw = DrawNode::create();
    draw->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    draw->setPosition(origin);
    this->addChild(draw);
    static Point Points1[] = {
            Point(origin.x,                     origin.y + visibleSize.height - 32),
            Point(origin.x + visibleSize.width, origin.y + visibleSize.height - 32),
            Point(origin.x + visibleSize.width, origin.y + visibleSize.height - 64),
            Point(origin.x,                     origin.y + visibleSize.height - 64)
    };
    draw->drawPolygon(Points1, 4, Color4F::WHITE, 1, Color4F::RED);

    // editBox
    editBox = ui::EditBox::create(Size(visibleSize.width / 2, 32), "chat_textbox.png");
    editBox->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    editBox->setPosition(Vec2(origin.x, origin.y + visibleSize.height - 32));
    editBox->setFont("fonts/arial.ttf", 36);
    editBox->setPlaceHolder("please input your message!");
    editBox->setFontColor(Color4B::BLACK);
    editBox->setMaxLength(500);
    editBox->setText("");
    editBox->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    editBox->setInputMode(ui::EditBox::InputMode::ANY);
    editBox->setDelegate(this);
    this->addChild(editBox);

    // send button: outline
    DrawNode* sendButtonDraw = DrawNode::create();
    sendButtonDraw->setPosition(0, 0);
    this->addChild(sendButtonDraw);
    static Point points[] = {
            Point(origin.x + visibleSize.width / 2 - 100, origin.y + visibleSize.height - 128),
            Point(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height - 128),
            Point(origin.x + visibleSize.width / 2 + 100, origin.y + visibleSize.height - 160),
            Point(origin.x + visibleSize.width / 2 - 100, origin.y + visibleSize.height - 160)
    };
    sendButtonDraw->drawPolygon(points, 4, Color4F::GRAY, 1, Color4F::GRAY);

    // send button: body
    Label* sendButtonLabel = Label::createWithSystemFont("send!", "fonts/arial.ttf", 24);
    sendButtonLabel->setColor(Color3B::BLACK);
    MenuItemLabel* sendMenu = MenuItemLabel::create(sendButtonLabel, CC_CALLBACK_1(ChatScene::pushsedButton, this));
    sendMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 144));
    Menu* menu = Menu::create(sendMenu, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    // WebSocket接続
    webSocket = new WebSocket();
    webSocket->init(*this, "ws://blurryplume.net:28080");

    return true;
}

void ChatScene::pushsedButton(Ref *pSender)
{
    sendText = editBox->getText();
    // 送信処理
    if (sendText.length() > 0) {
        webSocket->send(sendText);
        editBox->setText("");
    }
}

void ChatScene::sendMessage()
{

}

void ChatScene::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{

}
void ChatScene::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{

}
void ChatScene::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{

}
void ChatScene::editBoxReturn(cocos2d::ui::EditBox* editBox)
{

}

void ChatScene::onOpen(WebSocket* ws) {

}
void ChatScene::onMessage(WebSocket* ws, const WebSocket::Data& data) {
    Label* msgLabel = Label::createWithSystemFont(data.bytes, "fonts/arial.ttf", 36);
    msgLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    this->addChild(msgLabel);
}
void ChatScene::onClose(WebSocket* ws){

}
void ChatScene::onError(WebSocket* ws, const WebSocket::ErrorCode& error){
}
