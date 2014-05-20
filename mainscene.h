
#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
class MainScene : public Layer
{
public:
    static Scene *createScene();

    void clickButton(Object *pSender, ui::TouchEventType type);
protected:
    bool initScene();
};

#endif // MAINSCENE_H
