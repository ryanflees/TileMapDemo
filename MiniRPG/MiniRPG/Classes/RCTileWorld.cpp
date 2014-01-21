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
#include "RCActorTemplateCache.h"

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
    
    m_actorNode = CCNode::create();
    m_gameNode->addChild(m_actorNode);
    
    generateNPCActors();
    
    m_worldProcessor = RCWorldProcessor::create();
    addChild(m_worldProcessor);
    m_worldProcessor->setTileMapGameNode(m_gameNode, m_tileMap);
    m_worldProcessor->setDelegate(this);
    
    return true;
}

void RCTileWorld::addPlayer(RCActorTemplate* actorTemplate)
{
    if (m_player) {
        m_player->removeFromParent();
        m_player = NULL;
    }
    m_player = RCActor::createWithTemplate(actorTemplate);
    m_actorNode->addChild(m_player);
    m_player->setVisible(false);
    m_worldProcessor->setPlayerRef(m_player);
}

void RCTileWorld::removePlayer()
{
    if (m_player) {
        m_player->removeFromParent();
        m_player = NULL;
    }
    m_worldProcessor->setPlayerRef(m_player);
}

void RCTileWorld::bindControllerLayer(RCControllerLayer* controllerLayer)
{
    m_worldProcessor->setControllerLayerRef(controllerLayer);
}

CCSize RCTileWorld::onGetWorldSize(RCWorldProcessor *worldProcessor)
{
    float scalex = m_gameNode->getScaleX() * m_tileMap->getScaleX();
    float scaley = m_gameNode->getScaleY() * m_tileMap->getScaleY();
    
    CCSize size = CCSizeMake(m_tileMap->getContentSize().width*scalex, m_tileMap->getContentSize().height*scaley);
    return size;
}

CCSize RCTileWorld::onGetWorldSizeInPixels(RCWorldProcessor* worldProcessor)
{
    CCSize size = CCSizeMake(m_tileMap->getContentSize().width, m_tileMap->getContentSize().height);
    return size;
}

void RCTileWorld::setWorldScale(float scale)
{
    m_gameNode->setScale(scale);
}

void RCTileWorld::onEnter()
{
    CCLayer::onEnter();
    scheduleUpdate();
}

void RCTileWorld::onExit()
{
    CCLayer::onExit();
    unscheduleUpdate();
}

void RCTileWorld::update(float delta)
{
    CCSize mapSize = onGetWorldSizeInPixels(NULL);
    CCObject *object;
    CCARRAY_FOREACH(m_actorNode->getChildren(), object)
    {
        CCNode *node = (CCNode*)object;
        int zorder = mapSize.height - node->getPositionY();
        node->setZOrder(zorder);
    }
}

void RCTileWorld::generateNPCActors()
{
    CCTMXObjectGroup *objectLayer = m_tileMap->objectGroupNamed("ObjectLayer");
    
    for (int i=0; i<objectLayer->getObjects()->count(); i++) {
        CCDictionary *dict = (CCDictionary*)objectLayer->getObjects()->objectAtIndex(i);
        const CCString *type = dict->valueForKey("type");
        if (strcmp(type->getCString(), "spawn") == 0) {
            const CCString *isNPCStr = dict->valueForKey("npc");
            if (isNPCStr->intValue()) {
                const CCString *npcActorName = dict->valueForKey("actor");
                CCPoint tilePos = getTilePositionByDict(dict);
                addNPC(npcActorName->getCString(), tilePos);
            }
        }
    }
}

void RCTileWorld::addNPC(const char *actorName, cocos2d::CCPoint position)
{
    RCActorTemplate *actorTemplate = RCActorTemplateCache::sharedActorTemplateCache()->getActorTemplateByName(actorName);
    RCActor *npcActor = RCActor::createWithTemplate(actorTemplate);
    m_actorNode->addChild(npcActor);
    npcActor->setPosition(position);
    npcActor->setActorActionByKey(kStandDown);
    m_actorArray->addObject(npcActor);
}

cocos2d::CCPoint RCTileWorld::getTilePositionByDict(cocos2d::CCDictionary *tileDict)
{
    if (!tileDict) {
        return CCPointZero;
    }
    float x, y, width, height;
    x = tileDict->valueForKey("x")->floatValue();
    y = tileDict->valueForKey("y")->floatValue();
    width =  tileDict->valueForKey("width")->floatValue();
    height =  tileDict->valueForKey("height")->floatValue();
    return ccp(x+width/2,y+height/2);
}




