//
// Created by Nobuhiro Kobayashi on 2018/04/14.
//

#include "StartMenuScene.h"
#include "HelloWorldScene.h"
#include "ChatScene.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
    return StartMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    setContents();

    return true;
}

void StartMenu::setContents()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // タイトル
    Label* title = Label::createWithSystemFont("ChatMaster!", "fonts/arial.ttf", 36);
    float tX = origin.x + visibleSize.width / 2;
    float tY = origin.y + visibleSize.height - 10;
    title->setPosition(Vec2(tX, tY));
    this->addChild(title);

    // ボタン
    auto startButton = MenuItemImage::create(
            "aqua_button.png",
            "CloseSelected.png",
            CC_CALLBACK_1(StartMenu::pushStartButton, this));

    startButton->setPosition(Vec2(tX, tY - 60));

    auto menu = Menu::create(startButton, NULL);
    menu->setPosition(origin);
    this->addChild(menu);
}

void StartMenu::pushStartButton(Ref *pSender)
{
    auto chatScene = ChatScene::create();
    Director::getInstance()->replaceScene(chatScene);
}

