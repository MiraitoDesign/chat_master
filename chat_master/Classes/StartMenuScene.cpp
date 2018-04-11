//
// Created by 稲村裕作 on 2018/04/10.
//

#include "StartMenuScene.h"

// 以下のように定義されているので、これを読み込んでおくとcocos2dのネームスペース宣言が楽
// #define USING_NS_CC using namespace cocos2d
USING_NS_CC;

/**
 * 画面表示のベースとなるSceneを返す
 * @return Scene
 */
Scene* StartMenu::createScene() {
    return StartMenu::create();
}

/**
 * 読み込みに失敗した場合のエラー表示を行う。
 * とりあえずこれもHelloWorldと同じ感じで実装しておく
 * @param filename
 */
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartMenuScene.cpp\n");
}

/**
 * 画面表示時の初期化処理を行う
 * @return bool
 */
bool StartMenu::init() {
    //////////////////////////////
    // 親クラスの初期化処理呼び出し
    if ( !Scene::init() )
    {
        return false;
    }


    // Directorと呼ばれるcocos2dxが持つゲーム全体の処理のながれを司っているクラスを使用して画面情報を取得する
    // 画面解像度の取得
    auto visibleSize = Director::getInstance()->getVisibleSize();
    // 0座標の取得
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 画面表示処理
    // 画面遷移用のボタン置いておく
    auto startChatButton = MenuItemImage::create(
            "StartChat.png",
            "StartChat.png");

    // ボタンが読み込みできなければエラー
    if (startChatButton == nullptr ||
        startChatButton->getContentSize().width <= 0 ||
        startChatButton->getContentSize().height <= 0)
    {
        problemLoading("'StartChat.png' and 'StartChat.png'");
    } else {
        // 中央に配置しておく
        float x = origin.x + visibleSize.width - startChatButton->getContentSize().width/2;
        float y = origin.y + startChatButton->getContentSize().height/2;
        startChatButton->setPosition(Vec2(origin.x + visibleSize.width/2,
                                          origin.y + visibleSize.height/2));
    }

    this->addChild(startChatButton, 1);
}