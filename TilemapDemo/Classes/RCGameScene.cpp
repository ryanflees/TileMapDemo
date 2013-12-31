//
//  RCGameScene.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#define kMoveUpAction "move_up"
#define kMoveDownAction "move_down"
#define kMoveLeftAction "move_left"
#define kMoveRightAction "move_right"
#define kStandDown "stand_down"
#define kStandUp "stand_up"
#define kStandLeft "stand_left"
#define kStandRight "stand_right"

typedef enum
{
    kActionMoveUp,
    kActionMoveDown,
    kActionMoveLeft,
    kActionMoveRight,
    kActionStandUp,
    kActionStandDown,
    kActionStandLeft,
    kActionStandRight
}ActorMoveDirectionEnum;

#include "RCGameScene.h"
#include "RCTileWorld.h"
#include "RCActorTemplateCache.h"
#include "RCActor.h"
#include "func.h"

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
    m_player = RCActor::createWithTemplate(actorTemplate);
    addChild(m_player);
    m_player->setSpeed(30);
    m_player->setPosition(ccp(400, 100));
    m_player->setActorActionByKey("stand_down");
    
    m_controllerLayer = RCControllerLayer::create();
    addChild(m_controllerLayer);
    m_controllerLayer->setDelegate(this);
    
    return true;
}

void RCGameScene::updateControllerVector(RCControllerLayer *controllerLayer, CCPoint pressedVector, float delta)
{
    if (pressedVector.x == 0 && pressedVector.y == 0) {
        if (m_playerAction == kActionMoveRight) {
            m_playerAction = kActionStandRight;
            m_player->setActorActionByKey(kStandRight);
        }
        else if (m_playerAction == kActionMoveLeft)
        {
            m_playerAction = kActionStandLeft;
            m_player->setActorActionByKey(kStandLeft);
        }
        else if (m_playerAction == kActionMoveUp)
        {
            m_playerAction = kActionStandUp;
            m_player->setActorActionByKey(kStandUp);
        }
        else if (m_playerAction == kActionMoveDown)
        {
            m_playerAction = kActionStandDown;
            m_player->setActorActionByKey(kStandDown);
        }
        
        return;
    }
    float angle = ccpToAngle(pressedVector);
    float delAngle = radiansToDegrees(angle);
    if (delAngle <0 ) {
        delAngle += 360;
    }
    if (delAngle <= 45 || delAngle >= 315) {
        if (m_playerAction != kActionMoveRight) {
            m_playerAction = kActionMoveRight;
            m_player->setActorActionByKey(kMoveRightAction);
        }
    }
    else if (delAngle > 45 && delAngle < 135)
    {
        if (m_playerAction != kActionMoveUp) {
            m_playerAction = kActionMoveUp;
            m_player->setActorActionByKey(kMoveUpAction);
        }
    }
    else if (delAngle >= 135 && delAngle <= 225)
    {
        if (m_playerAction != kActionMoveLeft) {
            m_playerAction = kActionMoveLeft;
            m_player->setActorActionByKey(kMoveLeftAction);
        }
    }
    else if (delAngle > 225 && delAngle < 315)
    {
        if (m_playerAction != kActionMoveDown) {
            m_playerAction = kActionMoveDown;
            m_player->setActorActionByKey(kMoveDownAction);
        }
    }
    
    CCPoint moveOffset = getPositionOnTheCircle(CCPointZero, m_player->getSpeed(), delAngle);
    moveOffset = ccp(moveOffset.x*delta, moveOffset.y*delta);
    CCPoint newPos = m_player->getPosition() + moveOffset;
    m_player->setPosition(newPos);
}





