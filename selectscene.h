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
    std::vector<Sprite *>	vecSelectedCard;		//存放一选择的卡片
    std::vector<Sprite *>	vecNonSelectCard;		//存放为选择的卡片
};

#endif // SELECTSCENE_H
