//
// Created by 稲村裕作 on 2018/04/10.
//

#ifndef __STARTMENU_SCENE_H__
#define __STARTMENU_SCENE_H__

#include "cocos2d.h"

class StartMenu : public cocos2d::Scene
{
public:
    // 画面表示のベースとなるSceneを作成する
    static cocos2d::Scene* createScene();

    // 初期化処理
    virtual bool init();

    // 終了メニュー選択時のコールバック
    // 今は使わないのでコメントアウト
//    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(StartMenu);
};

#endif //__STARTMENU_SCENE_H__
