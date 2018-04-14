#include "ChatScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace ui;

Scene* Chat::createScene()
{
    return Chat::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChatScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Chat::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Chat::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("ChatMaster Chat", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

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

    float x = visibleSize.width / 2 ;
    float y = 20;
    button->setPosition(Vec2(x, y));

    button->addTouchEventListener([this](Ref * sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // TODO : メッセージ送信処理
        }
    });

    this->addChild(button);
    return true;
}


void Chat::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void Chat::editBoxEditingDidBegin(EditBox *editBox) {
}
void Chat::editBoxEditingDidEnd(EditBox *editBox) {
}
void Chat::editBoxTextChanged(EditBox *editBox, const std::string& text) {
}
void Chat::editBoxReturn(EditBox *editBox) {
}



