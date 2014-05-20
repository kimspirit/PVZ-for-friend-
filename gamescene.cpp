/*
 *
 */

#include "gamescene.h"

gamescene::gamescene()
{

}

gamescene::~gamescene()
{

}

Scene* gamescene::createScene()
{
  auto pScene = Scene::create();
  auto pLyaer = new gamescene();
  pScene->addChild(pLyaer);
}

