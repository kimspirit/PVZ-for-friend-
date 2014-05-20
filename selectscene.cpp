/*
 *
 */

#include "selectscene.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "./pvztools.h"
using namespace ui;
using namespace cocostudio;

selectscene::selectscene()
{

}

selectscene::~selectscene()
{

}

Scene* selectscene::createScene()
{
    auto pScene = Scene::create();
    auto pLayer = new selectscene;
    if(pLayer->initScene() == false) {
        delete pLayer;
        pLayer =nullptr;
        log("Scene* selectscene::createScene() error ~~~");
    }
    pScene->addChild(pLayer);
    return pScene;
}

bool selectscene::initScene()
{
    do {
        //Touch Event
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = CC_CALLBACK_2(selectscene::onTouchBegan, this);
        //listener->onTouchMoved = CC_CALLBACK_2(LCStartScene::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithFixedPriority(listener, -128);

        auto pBg = Sprite::create("Map_Level1.jpg");  //this is backgruond
        pBg->setAnchorPoint(Point::ZERO);
        addChild(pBg);

        auto pMainUI = GUIReader::getInstance()->widgetFromJsonFile("selectscene_1/selectscene_1.json"); //ui
        CC_BREAK_IF(!pMainUI);
        pMainUI->setTag(enTagUi);
        this->addChild(pMainUI);

        //card of character
        auto pArrowBg = Sprite::create("charactercard/Arrow_CD.png");
        pArrowBg->setPosition(Point(432,433));
        addChild(pArrowBg,enOrderFront);

        auto pArrow = Sprite::create("charactercard/Arrow_N.png");
        pArrow->setPosition(Point(432,433));
        addChild(pArrow,enOrderMid,ARROW_CARD);

        return true;
    } while(false);
    log("bool selectscene::initScene() error ~~~");
    return false;
}

bool selectscene::onTouchBegan(Touch *pTouch, Event *pEvent){
    auto pMainUi = dynamic_cast<Widget *>(getChildByTag(enTagUi));
    auto pCard = dynamic_cast<Sprite *>(getChildByTag(ARROW_CARD));
    if(pCard !=nullptr && pMainUi != nullptr && pCard->boundingBox().containsPoint(pTouch->getLocation())){
        auto pImageView = pMainUi->getChildByName("Card1");
        auto pMoveTo = MoveTo::create(1.f,pImageView->getPosition());
        pCard->runAction(pMoveTo);
    }
    return true;
}
