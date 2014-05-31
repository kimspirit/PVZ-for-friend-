/*
 *
 */

#ifndef SESPRITE_H
#define SESPRITE_H

#include <string>
#include <cocos2d.h>

class sesprite : public cocos2d::Sprite
{
public:
  static sesprite *createsprite(std::string strname,cocos2d::Point ptBgPoint,bool isSelect, int nSeIndex);
  
  int getSeIndex();
  void setSeIndex(int nIndex);
  
  bool getIsSelect();
  void setIsSelect(bool bCheck);
  
  cocos2d::Point getBgPosition();
  
protected:
  bool initSprite(std::string strname,cocos2d::Point ptBgPoint,bool isSelect, int nSeIndex);
  
private:
  int 			m_nSelectIndex;
  bool 			m_bIsSelect;
  cocos2d::Point 	m_ptBgPoint;
};

#endif // SESPRITE_H
