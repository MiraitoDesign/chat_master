#include "TitleScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* Title::createScene()
{
    return Title::create();
}

bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto mItem1 = MenuItemImage::create("btn.png","HelloWorld.png", CC_CALLBACK_1(Title::btnCallback, this));

    mItem1->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - mItem1->getContentSize().height));

    auto menu = Menu::create(mItem1,NULL);
    menu ->setPosition(Point::ZERO);
    this->addChild(menu);

    this->addChild(menu, 1);

    return true;
}

void Title::btnCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(HelloWorld::createScene());
};
