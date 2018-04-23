#include "TopScene.h"
#include "ChatScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Top::createScene()
{
    return Top::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in TopScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Top::init()
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
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("ChatMaster Top", "fonts/Marker Felt.ttf", 24);
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
    ui::EditBox* nameText = ui::EditBox::create(Size(visibleSize.width - 10, 30), "textbox.png");
    nameText->setPosition(Vec2(origin.x+visibleSize.width/2, visibleSize.height/2 + 50));
    nameText->setFont("fonts/mgenplus-1mn-medium.ttf", 12);
    nameText->setFontColor(Color3B::BLACK);
    nameText->setMaxLength(20);
    nameText->setInputMode(ui::EditBox::InputMode::ANY);
    nameText->setDelegate(this);
    this->addChild(nameText);

    UserDefault *userDef = UserDefault::getInstance();
    auto name = userDef->getStringForKey("name");
    nameText->setText(name.c_str());

    // ボタン追加
    ui::Button * button = ui::Button::create();
    button->setTouchEnabled(true);
    button->loadTextures("button.png", "button.png","");
    button->setTitleText("決定");
    button->setTitleFontName("fonts/mgenplus-1mn-medium.ttf");
    button->setTitleColor(Color3B::BLACK);
    button->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

    float x = visibleSize.width /2;
    float y = visibleSize.height /2;

    button->setPosition(Vec2(x, y));

    button->addTouchEventListener([this, nameText](Ref * sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            UserDefault *userDef = UserDefault::getInstance();
            userDef->setStringForKey("name", nameText->getText());

            auto chatScene = Chat::create();
            TransitionFade* fade = TransitionFade::create(0.5f, chatScene, Color3B::WHITE);
            Director::getInstance()->replaceScene(chatScene);
        }
    });

    this->addChild(button);

//    auto buttonLayer = ButtonLayer::create();
//    this->addChild(buttonLayer);

    return true;
}

void Top::editBoxEditingDidBegin(EditBox *editBox) {
}
void Top::editBoxEditingDidEnd(EditBox *editBox) {
}
void Top::editBoxTextChanged(EditBox *editBox, const std::string& text) {
}
void Top::editBoxReturn(EditBox *editBox) {
}

