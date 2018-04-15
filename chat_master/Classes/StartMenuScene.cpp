//
// Created by Nobuhiro Kobayashi on 2018/04/14.
//

#include "StartMenuScene.h"
#include "HelloWorldScene.h"

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
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto startButton = MenuItemImage::create(
            "aqua_button.png",
            "CloseSelected.png",
            CC_CALLBACK_1(StartMenu::pushStartButton, this));

    float x = visibleSize.width / 2;
    float y = visibleSize.height;
    startButton->setPosition(Vec2(x, y));

    auto menu = Menu::create(startButton, NULL);
    menu ->setPosition(Point::ZERO);
    this->addChild(menu);

    this->addChild(menu, 1);
}

void StartMenu::pushStartButton(Ref *pSender)
{
    auto helloWorld = HelloWorld::create();
    Director::getInstance()->replaceScene(helloWorld);
}

