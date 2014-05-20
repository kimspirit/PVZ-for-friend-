#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <vector>
#include "cocos2d.h"
using namespace cocos2d;

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
    std::vector<Sprite *>	vecSelectedCard;
    std::vector<SPrite *>	vecNonSelectCard;
};

#endif // SELECTSCENE_H
