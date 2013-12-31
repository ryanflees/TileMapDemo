//
//  RCWorldManager.cpp
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#include "RCWorldManager.h"
#include "RCActor.h"
#include "func.h"

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


USING_NS_CC;

RCWorldManager::RCWorldManager():m_controllerLayerRef()
        ,m_playerRef()
        ,m_tileMapeRef()
{

}

RCWorldManager::~RCWorldManager()
{
    if (m_controllerLayerRef) {
        m_controllerLayerRef->setDelegate(NULL);
    }
}

bool RCWorldManager::init()
{
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

void RCWorldManager::updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta)
{
    if (!m_playerRef) {
        return;
    }
    if (pressedVector.x == 0 && pressedVector.y == 0) {
        if (m_playerAction == kActionMoveRight) {
            m_playerAction = kActionStandRight;
            m_playerRef->setActorActionByKey(kStandRight);
        }
        else if (m_playerAction == kActionMoveLeft)
        {
            m_playerAction = kActionStandLeft;
            m_playerRef->setActorActionByKey(kStandLeft);
        }
        else if (m_playerAction == kActionMoveUp)
        {
            m_playerAction = kActionStandUp;
            m_playerRef->setActorActionByKey(kStandUp);
        }
        else if (m_playerAction == kActionMoveDown)
        {
            m_playerAction = kActionStandDown;
            m_playerRef->setActorActionByKey(kStandDown);
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
            m_playerRef->setActorActionByKey(kMoveRightAction);
        }
    }
    else if (delAngle > 45 && delAngle < 135)
    {
        if (m_playerAction != kActionMoveUp) {
            m_playerAction = kActionMoveUp;
            m_playerRef->setActorActionByKey(kMoveUpAction);
        }
    }
    else if (delAngle >= 135 && delAngle <= 225)
    {
        if (m_playerAction != kActionMoveLeft) {
            m_playerAction = kActionMoveLeft;
            m_playerRef->setActorActionByKey(kMoveLeftAction);
        }
    }
    else if (delAngle > 225 && delAngle < 315)
    {
        if (m_playerAction != kActionMoveDown) {
            m_playerAction = kActionMoveDown;
            m_playerRef->setActorActionByKey(kMoveDownAction);
        }
    }
    
    CCPoint moveOffset = getPositionOnTheCircle(CCPointZero, m_playerRef->getSpeed(), delAngle);
    moveOffset = ccp(moveOffset.x*delta, moveOffset.y*delta);
    CCPoint newPos = m_playerRef->getPosition() + moveOffset;
    m_playerRef->setPosition(newPos);
}

void RCWorldManager::setControllerLayerRef(RCControllerLayer* controllerLayer)
{
    if (m_controllerLayerRef) {
        m_controllerLayerRef->setDelegate(NULL);
    }
    m_controllerLayerRef = controllerLayer;
    if (m_controllerLayerRef) {
        m_controllerLayerRef->setDelegate(this);
    }
}

void RCWorldManager::setPlayerRef(RCActor *player)
{
    m_playerRef = player;
    if (m_playerRef) {
        m_playerAction = kActionStandDown;
        m_playerRef->setActorActionByKey(kStandDown);
    }
}





