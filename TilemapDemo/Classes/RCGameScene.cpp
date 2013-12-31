//
//  RCGameScene.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//
#include "RCGameScene.h"
#include "RCTileWorld.h"
#include "RCActorTemplateCache.h"
#include "RCActor.h"
#include "func.h"
#include "RCControllerLayer.h"

USING_NS_CC;

CCScene *RCGameScene::scene()
{
    CCScene *scene = CCScene::create();
    RCGameScene *layer = RCGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool RCGameScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_tileWorld = RCTileWorld::createWithTmxFile("game/tilemap/game_world.tmx");
    addChild(m_tileWorld);
    m_tileWorld->setAnchorPoint(CCPointZero);
    m_tileWorld->setPosition(CCPointZero);
    m_tileWorld->setScale(2.0f);
    
    RCActorTemplateCache::sharedActorTemplateCache()->addActorByFile("game/DSMaterials/Graphics/Characters/hero.plist");
    RCActorTemplate *actorTemplate = RCActorTemplateCache::sharedActorTemplateCache()->getActorTemplateByName("hero1");
    m_tileWorld->addPlayer(actorTemplate);
    RCActor *player = m_tileWorld->getPlayer();
    player->setSpeed(40);
    player->setPosition(ccp(400, 200));
    
    m_controllerLayer = RCControllerLayer::create();
    addChild(m_controllerLayer);
    m_tileWorld->bindControllerLayer(m_controllerLayer);
    
    return true;
}



