//
//  RCGameEntry.cpp
//  TilemapDemo
//
//  Created by hy on 1/6/14.
//
//

#include "RCGameEntry.h"
#include "RCMainMenu.h"

using namespace std;
USING_NS_CC;

RCGameEntry* RCGameEntry::m_instanceOfGameEntry = NULL;

RCGameEntry* RCGameEntry::sharedGameEntry()
{
    if (!m_instanceOfGameEntry) {
        m_instanceOfGameEntry = new RCGameEntry();
    }
    return m_instanceOfGameEntry;
}

void RCGameEntry::purge()
{
    CC_SAFE_DELETE(m_instanceOfGameEntry);
}

RCGameEntry::RCGameEntry()
{

}

RCGameEntry::~RCGameEntry()
{

}

void RCGameEntry::showMainMenu()
{
    CCScene *scene = CCScene::create();
    CCNodeLoaderLibrary *pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader *ccbReader = new CCBReader(pLoaderLibrary);
    pLoaderLibrary->registerCCNodeLoader("RCMainMenu", RCMainMenuLoader::loader());
    CCNode *node = ccbReader->readNodeGraphFromFile("ccbi/main_menu.ccbi");
    ccbReader->release();
    scene->addChild(node);
    CCDirector::sharedDirector()->runWithScene(scene);
}

void RCGameEntry::readAllLevelData()
{

}

void RCGameEntry::loadLevel(const char* levelFile)
{

}





