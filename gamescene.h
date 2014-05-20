#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "cocos2d.h"
using namespace cocos2d;


class gamescene : public Layer
{
public:
    gamescene();
    ~gamescene();
    
    static Scene *createScene();
    
};

#endif // GAMESCENE_H
