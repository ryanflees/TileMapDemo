//
//  RCTileWorld.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCTileWorld.h"

USING_NS_CC;

RCTileWorld *RCTileWorld::createWithTmxFile(const char *tmxFile)
{
    RCTileWorld *pRet = new RCTileWorld();
    if (pRet && pRet->initWithTmxFile(tmxFile))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool RCTileWorld::initWithTmxFile(const char *tmxFile)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_gameNode = CCNode::create();
    addChild(m_gameNode);
    
    if (tmxFile && strlen(tmxFile) > 1) {
        m_tileMap = CCTMXTiledMap::create(tmxFile);
        addChild(m_tileMap);
    }
    
    //m_actorController = [RCActorController node];
    //[self addChild:m_actorController];
    return true;
}





