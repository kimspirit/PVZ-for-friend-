/*
 *
 */

#include "sesprite.h"


sesprite* sesprite::createsprite(std::string strname,cocos2d::Point ptBgPoint,bool isSelect, int nSeIndex)
{
  do{
    auto sprires = new sesprite;
    if(sprires->initSprite(strname,ptBgPoint,isSelect,nSeIndex) == false){
      delete sprires;
      sprires = nullptr;
      break;
    }
    
    sprires->autorelease();
    return sprires;
  }while(false);
  cocos2d::log("sesprite* sesprite::createsprite() error ~~~");
  return nullptr;
}

bool sesprite::initSprite(std::string strname,cocos2d::Point ptBgPoint,bool isSelect, int nSeIndex)
{
  do{
    initWithFile(strname);
    m_bIsSelect = isSelect;
    m_nSelectIndex = nSeIndex;
    m_ptBgPoint = ptBgPoint;
    return true;
  }while(false);
  cocos2d::log("sesprite::initSprite() error ~~~");
  return false;
}

bool sesprite::getIsSelect()
{
  return m_bIsSelect;
}

void sesprite::setIsSelect(bool bCheck)
{
  m_bIsSelect = bCheck;
}


int sesprite::getSeIndex()
{
  return m_nSelectIndex;
}

void sesprite::setSeIndex(int nIndex)
{
  m_nSelectIndex = nIndex;
}


cocos2d::Point sesprite::getBgPosition()
{
  return m_ptBgPoint;
}
