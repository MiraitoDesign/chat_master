#include "ChatScene.h"

USING_NS_CC;
using namespace ui;

Scene* Chat::createScene()
{
    return Chat::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChatScene.cpp\n");
}

bool Chat::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // スクロール表示用のViewを作る
    float inputAreaHeight = 100;
    auto *scroll = ScrollView::create();
    scrollView = ScrollView::create();
    scroll->setContentSize(Size(visibleSize.width, visibleSize.height - inputAreaHeight));
    scroll->setDirection(ScrollView::Direction::VERTICAL);
    scroll->setPosition(Vec2(origin.x + 0, origin.y + inputAreaHeight));
    scroll->setTouchEnabled(true);
    scroll->setBounceEnabled(true);
    scroll->setTag(1);
    this->addChild(scroll);
    scrollView = scroll;

    /*
    for(int i=0; i < 30; i++) {
        // AndroidではNDKがstd::to_string/std::stoi/std::stofに対応していないのでstringstreamを使う
        std::stringstream chatMsgStream;
        chatMsgStream << "日本語テスト" << (i + 1);
        this->addChatMessage(scroll, chatMsgStream.str());
    }
    // 一番下までスクロール
    // scroll->scrollToBottom(0, false);
     */

    // テキストボックス追加
    ui::EditBox* messageText = ui::EditBox::create(Size(visibleSize.width - 10, 30), "textbox.png");
    messageText->setPosition(Vec2(origin.x+visibleSize.width/2, 80));
    messageText->setFont("American Typewriter", 12);
    messageText->setFontColor(Color3B::BLACK);
    messageText->setMaxLength(1000);
    messageText->setInputMode(ui::EditBox::InputMode::ANY);
    messageText->setDelegate(this);
    this->addChild(messageText);

    // ボタン追加
    ui::Button * button = ui::Button::create();
    button->setTouchEnabled(true);
    button->loadTextures("button.png", "button.png","");
    button->setTitleText("送信");
    button->setTitleFontName("fonts/mgenplus-1mn-medium.ttf");
    button->setTitleColor(Color3B::BLACK);

    float x = visibleSize.width / 2 ;
    float y = 40;
    button->setPosition(Vec2(x, y));

    UserDefault *userDef = UserDefault::getInstance();
    auto name = userDef->getStringForKey("name");

    button->addTouchEventListener([this, scroll, messageText, name](Ref * sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // メッセージ送信
            std::stringstream chatMsgStream;
            chatMsgStream << name << ":" << messageText->getText();
            webSocket->send(chatMsgStream.str());
        }
    });

    this->addChild(button);

    // WebSocket接続
    webSocket = new WebSocket();
//    webSocket->init(*this, "ws://10.0.1.34:8080");
    webSocket->init(*this, "ws://blurryplume.net:28080");

    return true;
}

void Chat::addChatMessage(ScrollView *view, std::string message) {

    auto label = Label::createWithTTF(message,"fonts/mgenplus-1mn-medium.ttf",12);
//    label->setPosition(label->getContentSize().width / 2, label->getContentSize().height / 2);
    label->setPosition(view->getContentSize().width, label->getContentSize().height / 2);
    label->runAction(MoveTo::create(0.2,Vec2(label->getContentSize().width / 2, label->getPosition().y)));

    // 全ての子Nodeを上に移動させる。
    auto children = view->getChildren();
    float maxY = 0;
    for (auto child : children) {
        auto position = child->getPosition();
        float posY = position.y + label->getContentSize().height;
        child->setPosition(Vec2(position.x, posY));
        maxY = (posY > maxY) ? posY : maxY;
    }

    if (maxY > view->getInnerContainerSize().height) {
        auto size = Size(view->getInnerContainerSize().width, view->getInnerContainerSize().height + label->getContentSize().height);
        view->setInnerContainerSize(size);
    }

    view->addChild(label);
    // scrollToBottom()だと一瞬画面が先頭に戻ってしまう模様。setInnerContainerPositionなら大丈夫だった。
    // view->scrollToBottom(0, false);
    view->setInnerContainerPosition(Vec2(0,0));
}

void Chat::editBoxEditingDidBegin(EditBox *editBox) {
}
void Chat::editBoxEditingDidEnd(EditBox *editBox) {
}
void Chat::editBoxTextChanged(EditBox *editBox, const std::string& text) {
}
void Chat::editBoxReturn(EditBox *editBox) {
}

void Chat::onOpen(WebSocket* ws) {
    this->addChatMessage(scrollView, "接続しました。");
}
void Chat::onMessage(WebSocket* ws, const WebSocket::Data& data) {
    this->addChatMessage(scrollView, data.bytes);
}
void Chat::onClose(WebSocket* ws){
    this->addChatMessage(scrollView, "切断されました。");
}
void Chat::onError(WebSocket* ws, const WebSocket::ErrorCode& error){
}

