#include "mainscene.h"
#include "cocostudio/CocoStudio.h"
#include "selectscene.h"

using namespace ui;
using namespace cocostudio;
Scene* MainScene::createScene()
{
    do {
        auto pScene = Scene::create();
        CC_BREAK_IF(!pScene);

        auto pLayer = new MainScene;
        if(pLayer->initScene() == false) {
            delete pLayer;
            pLayer = nullptr;
            break;
        }
        pLayer->autorelease();

        pScene->addChild(pLayer);
        return pScene;
    } while(false);
    log("Scene* MainScene::createScene() error !!!");
    return nullptr;
}

bool MainScene::initScene()
{
    do {

//用CocoStudio拼的UI
        auto pMainUI = GUIReader::shareReader()->widgetFromJsonFile("MainUI/NewUI_1.json");
        CC_BREAK_IF(!pMainUI);
        this->addChild(pMainUI);

//从UI里面获取按钮们
        auto pStart = dynamic_cast<Button *>(pMainUI->getChildByName("Start"));
        CC_BREAK_IF(!pStart);
        pStart->addTouchEventListener(this,toucheventselector(MainScene::clickButton));

        auto pShop = dynamic_cast<Button *>(pMainUI->getChildByName("Shop"));
        CC_BREAK_IF(!pShop);
        pShop->addTouchEventListener(this,toucheventselector(MainScene::clickButton));

        auto pArchive = dynamic_cast<Button *>(pMainUI->getChildByName("Archive"));
        CC_BREAK_IF(!pArchive);
        pArchive->addTouchEventListener(this,toucheventselector(MainScene::clickButton));

        auto pQuit = dynamic_cast<Button *>(pMainUI->getChildByName("Quit"));
        CC_BREAK_IF(!pQuit);
        pQuit->addTouchEventListener(this,toucheventselector(MainScene::clickButton));

        return true;

    } while(false);
    log("bool MainScene::initScene() error !!!");
    return false;
}

void MainScene::clickButton(Object* pSender, TouchEventType type)
{
    auto pButton = dynamic_cast<Button *>(pSender);
    if(type == TOUCH_EVENT_ENDED) {
        if(strcmp(pButton->getName(),"Start") == 0) {
	  Director::getInstance()->replaceScene(selectscene::createScene());
        }

        if(strcmp(pButton->getName(),"Shop") == 0) {

        }

        if(strcmp(pButton->getName(),"Archive") == 0) {

        }

        if(strcmp(pButton->getName(),"Quit") == 0) {
	  Director::getInstance()->end();
        }
    }

}
