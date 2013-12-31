//
//  RCTileWorld.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCTileWorld.h"
#include "RCActor.h"
#include "RCActorTemplate.h"

USING_NS_CC;

RCTileWorld::RCTileWorld():m_player(NULL)
{

}

RCTileWorld::~RCTileWorld()
{
    m_actorArray->release();
}

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
    
    if (!tmxFile || strlen(tmxFile) == 1)
    {
        return false;
    }
    
    m_actorArray = CCArray::create();
    m_actorArray->retain();
    
    m_gameNode = CCNode::create();
    addChild(m_gameNode);
    
    m_tileMap = CCTMXTiledMap::create(tmxFile);
    m_gameNode->addChild(m_tileMap);
    
    m_worldManager = RCWorldManager::create();
    addChild(m_worldManager);
    
    return true;
}

void RCTileWorld::addPlayer(RCActorTemplate* actorTemplate)
{
    if (m_player) {
        m_player->removeFromParent();
        m_player = NULL;
    }
    m_player = RCActor::createWithTemplate(actorTemplate);
    m_gameNode->addChild(m_player);
    m_worldManager->setPlayerRef(m_player);
}

void RCTileWorld::removePlayer()
{
    if (m_player) {
        m_player->removeFromParent();
        m_player = NULL;
    }
    m_worldManager->setPlayerRef(m_player);
}

void RCTileWorld::bindControllerLayer(RCControllerLayer* controllerLayer)
{
    m_worldManager->setControllerLayerRef(controllerLayer);
}





