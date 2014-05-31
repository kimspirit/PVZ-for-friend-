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
        /**
         * 通过读取数据库来获取可以选择的卡片.
         */
        std::vector<characterInfo> *pInfo = nullptr;
        pvzdatabase::getinstance()->writecharacterinfo(&pInfo);
        for(auto &info : *pInfo) {
            auto pCardBg = Sprite::create(info.strbgname);
            pCardBg->setPosition(432.f,433.f);
            addChild(pCardBg,enOrderFront);

            auto pCard = sesprite::createsprite(info.strname,Point(432,433),false,-1);
            pCard->setPosition(432.f,433.f);
            addChild(pCard,enOrderMid,info.nTag);

            selectCharacterInfo tempInfo;
            tempInfo.pCard = pCard;
            tempInfo.fCdTime = info.fCdTime;
            tempInfo.nTag = info.nTag;
            tempInfo.nCost = info.nCost;
            vecNonSelectedCard.push_back(tempInfo);
        }

        return true;
    } while(false);
    log("bool selectscene::initScene() error ~~~");
    return false;
}

bool selectscene::onTouchBegan(Touch *pTouch, Event *pEvent) {
    auto pMainUi = dynamic_cast<Widget *>(getChildByTag(enTagUi));


    for(auto &info : vecNonSelectedCard) {
        auto pCard = dynamic_cast<sesprite *>(getChildByTag(info.nTag));

        if(pCard->getIsSelect() == true){
            break;
        }
        if(pCard !=nullptr && pCard->getIsSelect() == false && pMainUi != nullptr && pCard->getBoundingBox().containsPoint(pTouch->getLocation())) {

            pCard->setIsSelect(true);
            pCard->setSeIndex(vecSelectedCard.size());

            auto pImageView = pMainUi->getChildByName("Card1");
            auto pMoveTo = MoveTo::create(1.f,pImageView->getPosition());
            pCard->runAction(pMoveTo);

            selectCharacterInfo tempInfo;
            tempInfo.pCard = pCard;
            tempInfo.fCdTime = info.fCdTime;
            tempInfo.nTag = info.nTag;
            tempInfo.nBgTag = info.nBgTag;
            tempInfo.nCost = info.nCost;
            vecSelectedCard.push_back(tempInfo);

            return true;
        }
    }

    for(auto &info : vecSelectedCard) {
        auto pCard = dynamic_cast<sesprite *>(getChildByTag(info.nTag));
        if(pCard !=nullptr && pCard->getIsSelect() == true && pMainUi != nullptr && pCard->getBoundingBox().containsPoint(pTouch->getLocation())) {

            pCard->setIsSelect(false);
            pCard->setPosition(pCard->getBgPosition());
            vecSelectedCard.erase(vecSelectedCard.begin()+pCard->getSeIndex());
            pCard->setSeIndex(-1);
            return true;
        }
    }

    return false;
}
