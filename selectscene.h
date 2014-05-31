#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <string>
#include <vector>
#include "sesprite.h"
#include "./pvzdatabase.h"
using namespace cocos2d;

class selectCharacterInfo {
public:
    sesprite 		*pCard;
    float 		fCdTime;
    int 		nCost;
    int         	nTag;
    int			nBgTag;
};

class selectscene : public Layer
{
public:
    selectscene();
    ~selectscene();
    
    static Scene *createScene();
    bool initScene();
    
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
private:
    enum{
        enTagUi,
    };
    std::vector<selectCharacterInfo>	vecSelectedCard;		//存放一个选择的卡片
    std::vector<selectCharacterInfo>	vecNonSelectedCard;		//存放一个未选择的卡片
};

#endif // SELECTSCENE_H
