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

#define kScreenInsightScale ccp(0.8,0.8)
#define kScreenInsectSize CCSizeMake(200,200)
#define kPlayerOnMapEdgeSize CCSizeMake(10,10)

USING_NS_CC;

RCWorldManager::RCWorldManager():m_controllerLayerRef()
        ,m_playerRef()
        ,m_tileMapeRef()
        ,m_gameNodeRef()
        ,m_delegate()
        ,m_landscapeLayer()
        ,m_miscLayer()
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
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //m_screenInsight =CCRectMake(screenSize.width*(1-kScreenInsightScale.x)*0.5f
    //                            ,screenSize.height*(1-kScreenInsightScale.y)*0.5f
    //                            ,screenSize.width*kScreenInsightScale.x
    //                            ,screenSize.height*kScreenInsightScale.y);
    m_screenInsight = CCRectMake(kScreenInsectSize.width
                            , kScreenInsectSize.height
                            , screenSize.width - kScreenInsectSize.width*2
                                 , screenSize.height - kScreenInsectSize.height*2);
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
    if (delAngle <= 60 || delAngle >= 300) {
        if (m_playerAction != kActionMoveRight) {
            m_playerAction = kActionMoveRight;
            m_playerRef->setActorActionByKey(kMoveRightAction);
        }
    }
    else if (delAngle > 60 && delAngle < 120)
    {
        if (m_playerAction != kActionMoveUp) {
            m_playerAction = kActionMoveUp;
            m_playerRef->setActorActionByKey(kMoveUpAction);
        }
    }
    else if (delAngle >= 120 && delAngle <= 240)
    {
        if (m_playerAction != kActionMoveLeft) {
            m_playerAction = kActionMoveLeft;
            m_playerRef->setActorActionByKey(kMoveLeftAction);
        }
    }
    else if (delAngle > 240 && delAngle < 300)
    {
        if (m_playerAction != kActionMoveDown) {
            m_playerAction = kActionMoveDown;
            m_playerRef->setActorActionByKey(kMoveDownAction);
        }
    }
    
    CCPoint moveOffset = getPositionOnTheCircle(CCPointZero, m_playerRef->getSpeed(), delAngle);
    moveOffset = ccp(moveOffset.x*delta, moveOffset.y*delta);
    moveOffset = checkBarrierCollisionForOffset(moveOffset, m_playerRef);
    
    CCPoint newPos = m_playerRef->getPosition() + moveOffset;
    CCSize mapSize = getTilemapSizeInPixels();
    CCRect mapRect = CCRectMake(kPlayerOnMapEdgeSize.width
                                , kPlayerOnMapEdgeSize.height
                                , mapSize.width-kPlayerOnMapEdgeSize.width*2
                                , mapSize.height - kPlayerOnMapEdgeSize.height*2);
    if (moveOffset.x < 0) {
        if (newPos.x < mapRect.origin.x) {
            newPos.x = m_playerRef->getPositionX();
        }
    }
    if (moveOffset.y < 0) {
        if (newPos.y < mapRect.origin.y) {
            newPos.y = m_playerRef->getPositionY();
        }
    }
    if (moveOffset.x > 0) {
        if (newPos.x > mapRect.origin.x + mapRect.size.width) {
            newPos.x = m_playerRef->getPositionX();
        }
    }
    if (moveOffset.y > 0) {
        if (newPos.y > mapRect.origin.y + mapRect.size.height) {
            newPos.y = m_playerRef->getPositionY();
        }
    }
    
    m_playerRef->setPosition(newPos);
    adjustCamera(moveOffset);
    
//    if (pointIsInRect(newPos, mapRect)) {
//    }
}

void RCWorldManager::setTileMapeRef(cocos2d::CCTMXTiledMap* tileMap)
{
    m_tileMapeRef = tileMap;
    m_landscapeLayer = m_tileMapeRef->layerNamed("LanscapeLayer");
    m_miscLayer = m_tileMapeRef->layerNamed("MiscLayer");
}

void RCWorldManager::adjustCamera(CCPoint moveOffset)
{
    CCPoint playerOnScreenPos = m_gameNodeRef->convertToWorldSpace(m_playerRef->getPosition());
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize mapSize = getTilemapSize();
    if (moveOffset.x > 0) {
        if (playerOnScreenPos.x > m_screenInsight.origin.x + m_screenInsight.size.width) {
            CCPoint nodeNewPos = m_gameNodeRef->getPosition() + ccp(-moveOffset.x*m_gameNodeRef->getScaleX(),0);
            if ( screenSize.width - nodeNewPos.x <= mapSize.width) {
                m_gameNodeRef->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.x < 0) {
        if (playerOnScreenPos.x < m_screenInsight.origin.x) {
            CCPoint nodeNewPos = m_gameNodeRef->getPosition() +                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ccp(-moveOffset.x*m_gameNodeRef->getScaleX(),0);
            if (nodeNewPos.x <= 0) {
                m_gameNodeRef->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.y > 0) {
        if (playerOnScreenPos.y > m_screenInsight.origin.y + m_screenInsight.size.height) {
            CCPoint nodeNewPos = m_gameNodeRef->getPosition() +
            ccp(0, -moveOffset.y*m_gameNodeRef->getScaleY());
            if (screenSize.height - nodeNewPos.y <= mapSize.height) {
                m_gameNodeRef->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.y < 0) {
        if (playerOnScreenPos.y < m_screenInsight.origin.y) {
            CCPoint nodeNewPos = m_gameNodeRef->getPosition() +
            ccp(0, -moveOffset.y*m_gameNodeRef->getScaleY());
            if (nodeNewPos.y <= 0) {
                m_gameNodeRef->setPosition(nodeNewPos);
            }
        }
    }
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

void RCWorldManager::onEnter()
{
    CCNode::onEnter();
    scheduleUpdate();
}

void RCWorldManager::onExit()
{
    CCNode::onExit();
    unscheduleUpdate();
}

void RCWorldManager::update(float delta)
{
    if (!m_playerRef) {
        return;
    }
    
    CCPoint playerPosition = m_playerRef->getPosition();
    //CCPoint newPoint = m_playerRef->convertToWorldSpace(m_playerRef->getPosition());
    //CCPoint newPoint = m_playerRef->convertToWorldSpaceAR(m_playerRef->getPosition());
    CCPoint newPoint = m_gameNodeRef->convertToWorldSpace(m_playerRef->getPosition());
    //CCPoint newPoint = CCDirector::sharedDirector()->convertToUI(playerPosition);
    //CCLog("new point %f %f",newPoint.x, newPoint.y);
    //CCSize size = getTilemapSize();
    //CCLog("size %f %f",size.width, size.height);
    
}

CCSize RCWorldManager::getTilemapSize()
{
    if (!m_delegate) {
        return CCSizeMake(0, 0);
    }
    return m_delegate->onGetWorldSize(this);
}

CCSize RCWorldManager::getTilemapSizeInPixels()
{
    if (!m_delegate) {
        return CCSizeMake(0, 0);
    }
    return m_delegate->onGetWorldSizeInPixels(this);
}


CCPoint RCWorldManager::tilePosFromLocation(CCPoint location,CCTMXTiledMap* tileMap)
{
    // Tilemap position must be offset, in case the tilemap is scrolling CGPoint pos = ccpSub(location, tileMap.position);
    // Cast to int makes sure that result is in whole numbers
    CCPoint pos = ccpSub(location, tileMap->getPosition());
    
    pos.x = (int)(pos.x / tileMap->getTileSize().width);
    pos.y = (int)((tileMap->getMapSize().height * tileMap->getTileSize().height - pos.y) /
                  tileMap->getTileSize().height);
    //CCLog("touch at (%.0f, %.0f) is at tileCoord (%i, %i)", location.x, location.y,(int)pos.x, (int)pos.y);
    return pos;
}

void RCWorldManager::checkObjectInteract(cocos2d::CCPoint point)
{
//    CCTMXObjectGroup *objectLayer = m_map->objectGroupNamed("ObjectLayer");
//    bool isTouchInRect = false;
//    for (int i=0; i<objectLayer->getObjects()->count(); i++) {
//        CCDictionary *dict = (CCDictionary*)objectLayer->getObjects()->objectAtIndex(i);
//        CCRect rect = getRectFromObjectProperties(dict, m_map);
//        if (pointIsInRect(point, rect)) {
//            isTouchInRect = true;
//            break;
//        }
//    }
//    if (isTouchInRect) {
//        CCLog("touch in rect");
//    }
}

CCRect RCWorldManager::getRectFromObjectProperties(CCDictionary* dict,CCTMXTiledMap*tileMap)
{
    float x, y, width, height;
    x = dict->valueForKey("x")->floatValue() + tileMap->getPositionX();
    y = dict->valueForKey("y")->floatValue() + tileMap->getPositionY();
    width =  dict->valueForKey("width")->floatValue();
    height =  dict->valueForKey("height")->floatValue();
    return CCRectMake(x, y, width, height);
}

bool RCWorldManager::checkBarrierCollision(cocos2d::CCPoint position)
{
    bool hasCollision = false;
    CCPoint tileCoord = tilePosFromLocation(position, m_tileMapeRef);
    int tileID = m_miscLayer->tileGIDAt(tileCoord);
    if (tileID) {
        CCDictionary *dict = m_tileMapeRef->propertiesForGID(tileID);
        if (dict) {
            const CCString *isBlock = dict->valueForKey("block");
            if (isBlock) {
                CCLog("block tile at %i",tileID);
                hasCollision = true;
            }
        }
    }

    tileID = m_landscapeLayer->tileGIDAt(tileCoord);
    if (tileID) {
        CCDictionary *dict = m_tileMapeRef->propertiesForGID(tileID);
        if (dict) {
            const CCString *isBlock = dict->valueForKey("block");
            if (isBlock) {
                CCLog("block tile at %i",tileID);
                hasCollision = true;
            }
        }
    }
    return hasCollision;
}

CCPoint RCWorldManager::checkBarrierCollisionForOffset(cocos2d::CCPoint offset, RCActor* player)
{
    CCPoint newOffset = offset;
    
    if (newOffset.x > 0) {
        bool hasCollision = false;
        CCRect newRect = player->getRect();
        newRect.origin = ccp(offset.x, 0) +newRect.origin;
        CCPoint topRightPoint = ccp(newRect.origin.x + newRect.size.width, newRect.origin.y + newRect.size.height);
        CCPoint midRightPoint = ccp(newRect.origin.x + newRect.size.width, newRect.origin.y + newRect.size.height*0.5f);
        CCPoint bottomRightPoint = ccp(newRect.origin.x + newRect.size.width, newRect.origin.y);
        if (checkBarrierCollision(topRightPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(midRightPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(bottomRightPoint)) {
            hasCollision = true;
        }
        if (hasCollision) {
            newOffset.x = 0;
        }
    }
    if (newOffset.x < 0) {
        bool hasCollision = false;
        CCRect newRect = player->getRect();
        newRect.origin = ccp(offset.x, 0) + newRect.origin;
        CCPoint topLeftPoint = ccp(newRect.origin.x, newRect.origin.y + newRect.size.height);
        CCPoint midLeftPoint = ccp(newRect.origin.x, newRect.origin.y + newRect.size.height*0.5f);
        CCPoint bottomLeftPoint = ccp(newRect.origin.x, newRect.origin.y);
        if (checkBarrierCollision(topLeftPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(midLeftPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(bottomLeftPoint)) {
            hasCollision = true;
        }
        if (hasCollision) {
            newOffset.x = 0;
            newRect.origin = newOffset + player->getPosition();
        }
    }
    if (newOffset.y > 0) {
        bool hasCollision = false;
        CCRect newRect = player->getRect();
        newRect.origin = ccp(0, offset.y) + newRect.origin;
        CCPoint topLeftPoint = ccp(newRect.origin.x, newRect.origin.y + newRect.size.height);
        CCPoint topMidPoint = ccp(newRect.origin.x + newRect.size.width*0.5f, newRect.origin.y + newRect.size.height);
        CCPoint topRightPoint = ccp(newRect.origin.x + newRect.size.width, newRect.origin.y + newRect.size.height);
        if (checkBarrierCollision(topLeftPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(topMidPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(topRightPoint)) {
            hasCollision = true;
        }
        if (hasCollision) {
            newOffset.y = 0;
            newRect.origin = newOffset + player->getPosition();
        }
    }
    
    if (newOffset.y < 0) {
        bool hasCollision = false;
        CCRect newRect = player->getRect();
        newRect.origin = ccp(0, offset.y) + newRect.origin;
        CCPoint bottomLeftPoint = ccp(newRect.origin.x, newRect.origin.y);
        CCPoint bottomMidPoint = ccp(newRect.origin.x + newRect.size.width*0.5f, newRect.origin.y);
        CCPoint bottomRightPoint = ccp(newRect.origin.x + newRect.size.width, newRect.origin.y);
        if (checkBarrierCollision(bottomLeftPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(bottomMidPoint)) {
            hasCollision = true;
        }
        if (checkBarrierCollision(bottomRightPoint)) {
            hasCollision = true;
        }
        if (hasCollision) {
            newOffset.y = 0;
            newRect.origin = newOffset + player->getPosition();
        }
    }
    
    return newOffset;
}


