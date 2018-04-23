#include "ButtonLayer.h"

USING_NS_CC;
using namespace ui;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in ChatScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ButtonLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ボタン追加
    ui::Button * button = ui::Button::create();
    button->setTouchEnabled(true);
    button->loadTextures("button.png", "button.png","");

    float x = visibleSize.width / 2 ;
    float y = 40;
    button->setPosition(Vec2(x, y));

    button->addTouchEventListener([this](Ref * sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            // TODO : メッセージ送信処理
        }
    });

    this->addChild(button);
    return true;
}

