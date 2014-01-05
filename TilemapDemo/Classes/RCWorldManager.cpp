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

#define kScreenInsightScale ccp(0.8,0.8)
#define kScreenInsectSize CCSizeMake(200,200)
#define kPlayerOnMapEdgeSize CCSizeMake(10,10)

USING_NS_CC;

RCWorldManager::RCWorldManager():m_controllerLayer()
        ,m_player()
        ,m_tileMap()
        ,m_gameNode()
        ,m_delegate()
        ,m_landscapeLayer()
        ,m_miscLayer()
        ,m_actorArray()
{

}

RCWorldManager::~RCWorldManager()
{
    if (m_controllerLayer) {
        m_controllerLayer->setDelegate(NULL);
    }
}

bool RCWorldManager::init()
{
    if (!CCNode::init()) {
        return false;
    }
    m_blockOffset = CCPointZero;
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
    if (!m_player) {
        return;
    }
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
    if (delAngle <= 60 || delAngle >= 300) {
        if (m_playerAction != kActionMoveRight) {
            m_playerAction = kActionMoveRight;
            m_player->setActorActionByKey(kMoveRightAction);
        }
    }
    else if (delAngle > 60 && delAngle < 120)
    {
        if (m_playerAction != kActionMoveUp) {
            m_playerAction = kActionMoveUp;
            m_player->setActorActionByKey(kMoveUpAction);
        }
    }
    else if (delAngle >= 120 && delAngle <= 240)
    {
        if (m_playerAction != kActionMoveLeft) {
            m_playerAction = kActionMoveLeft;
            m_player->setActorActionByKey(kMoveLeftAction);
        }
    }
    else if (delAngle > 240 && delAngle < 300)
    {
        if (m_playerAction != kActionMoveDown) {
            m_playerAction = kActionMoveDown;
            m_player->setActorActionByKey(kMoveDownAction);
        }
    }
    
    CCPoint moveOffset = getPositionOnTheCircle(CCPointZero, m_player->getSpeed(), delAngle);
    moveOffset = ccp(moveOffset.x*delta, moveOffset.y*delta);
    
    moveOffset = checkBarrierCollisionForOffset(moveOffset, m_player);
    
    CCPoint newPos = m_player->getPosition() + moveOffset;
    CCSize mapSize = getTilemapSizeInPixels();
    CCRect mapRect = CCRectMake(kPlayerOnMapEdgeSize.width
                                , kPlayerOnMapEdgeSize.height
                                , mapSize.width-kPlayerOnMapEdgeSize.width*2
                                , mapSize.height - kPlayerOnMapEdgeSize.height*2);
    if (moveOffset.x < 0) {
        if (newPos.x < mapRect.origin.x) {
            newPos.x = m_player->getPositionX();
        }
    }
    if (moveOffset.y < 0) {
        if (newPos.y < mapRect.origin.y) {
            newPos.y = m_player->getPositionY();
        }
    }
    if (moveOffset.x > 0) {
        if (newPos.x > mapRect.origin.x + mapRect.size.width) {
            newPos.x = m_player->getPositionX();
        }
    }
    if (moveOffset.y > 0) {
        if (newPos.y > mapRect.origin.y + mapRect.size.height) {
            newPos.y = m_player->getPositionY();
        }
    }
    
    m_player->setPosition(newPos);
    adjustCamera(moveOffset);
}

void RCWorldManager::setTileMapGameNode(cocos2d::CCNode *gameNode,cocos2d::CCTMXTiledMap* tileMap)
{
    m_gameNode = gameNode;
    m_tileMap = tileMap;
    m_landscapeLayer = m_tileMap->layerNamed("LanscapeLayer");
    m_miscLayer = m_tileMap->layerNamed("MiscLayer");
    
    CCString *blockOffsetX = m_tileMap->propertyNamed("block_offset_x");
    CCString *blockOffsetY = m_tileMap->propertyNamed("block_offset_y");
    m_blockOffset = ccp(blockOffsetX->floatValue(), blockOffsetY->floatValue());
}

void RCWorldManager::setActorArray(cocos2d::CCArray *actorArray)
{
    m_actorArray = actorArray;
}

void RCWorldManager::adjustCamera(CCPoint moveOffset)
{
    CCPoint playerOnScreenPos = m_gameNode->convertToWorldSpace(m_player->getPosition());
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCSize mapSize = getTilemapSize();
    if (moveOffset.x > 0) {
        if (playerOnScreenPos.x > m_screenInsight.origin.x + m_screenInsight.size.width) {
            CCPoint nodeNewPos = m_gameNode->getPosition() + ccp(-moveOffset.x*m_gameNode->getScaleX(),0);
            if ( screenSize.width - nodeNewPos.x <= mapSize.width) {
                m_gameNode->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.x < 0) {
        if (playerOnScreenPos.x < m_screenInsight.origin.x) {
            CCPoint nodeNewPos = m_gameNode->getPosition() +                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ccp(-moveOffset.x*m_gameNode->getScaleX(),0);
            if (nodeNewPos.x <= 0) {
                m_gameNode->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.y > 0) {
        if (playerOnScreenPos.y > m_screenInsight.origin.y + m_screenInsight.size.height) {
            CCPoint nodeNewPos = m_gameNode->getPosition() +
            ccp(0, -moveOffset.y*m_gameNode->getScaleY());
            if (screenSize.height - nodeNewPos.y <= mapSize.height) {
                m_gameNode->setPosition(nodeNewPos);
            }
        }
    }
    if (moveOffset.y < 0) {
        if (playerOnScreenPos.y < m_screenInsight.origin.y) {
            CCPoint nodeNewPos = m_gameNode->getPosition() +
            ccp(0, -moveOffset.y*m_gameNode->getScaleY());
            if (nodeNewPos.y <= 0) {
                m_gameNode->setPosition(nodeNewPos);
            }
        }
    }
}

void RCWorldManager::setControllerLayerRef(RCControllerLayer* controllerLayer)
{
    if (m_controllerLayer) {
        m_controllerLayer->setDelegate(NULL);
    }
    m_controllerLayer = controllerLayer;
    if (m_controllerLayer) {
        m_controllerLayer->setDelegate(this);
    }
}

void RCWorldManager::setPlayerRef(RCActor *player)
{
    m_player = player;
    if (m_player) {
        m_playerAction = kActionStandDown;
        m_player->setActorActionByKey(kStandDown);
        
        CCTMXObjectGroup *objectLayer = m_tileMap->objectGroupNamed("ObjectLayer");

//        CCDictionary *dict = (CCDictionary*) objectLayer->objectNamed("Spawn");
//        float x, y, width, height;
//        x = dict->valueForKey("x")->floatValue();
//        y = dict->valueForKey("y")->floatValue();
//        width =  dict->valueForKey("width")->floatValue();
//        height =  dict->valueForKey("height")->floatValue();
//        m_player->setVisible(true);
//        m_player->setPosition(ccp(x, y));
//
        m_player->setVisible(true);
        for (int i=0; i<objectLayer->getObjects()->count(); i++) {
            CCDictionary *dict = (CCDictionary*)objectLayer->getObjects()->objectAtIndex(i);
            const CCString *type = dict->valueForKey("type");
            if (strcmp(type->getCString(), "spawn") == 0) {
                const CCString *isPlayerStr = dict->valueForKey("player");
                if (isPlayerStr) {
                    int isPlayerSpawn = isPlayerStr->intValue();
                    if (isPlayerSpawn) {
                        setActorPositionOnTile(m_player, dict);
                    }
                }
            }
        }
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
    if (!m_player) {
        return;
    }
    
    CCPoint playerPosition = m_player->getPosition();
    //CCPoint newPoint = m_player->convertToWorldSpace(m_player->getPosition());
    //CCPoint newPoint = m_player->convertToWorldSpaceAR(m_player->getPosition());
    CCPoint newPoint = m_gameNode->convertToWorldSpace(m_player->getPosition());
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
    if (!checkPositionInsideTileMap(position)) {
        return false;
    }
    CCPoint tileCoord = tilePosFromLocation(position, m_tileMap);
    int tileID = m_miscLayer->tileGIDAt(tileCoord);
    if (tileID) {
        CCDictionary *dict = m_tileMap->propertiesForGID(tileID);
        if (dict) {
            const CCString *isBlock = dict->valueForKey("block");
            if (isBlock) {
             //   CCLog("block tile at %i",tileID);
                hasCollision = true;
            }
        }
    }

    tileID = m_landscapeLayer->tileGIDAt(tileCoord);
    if (tileID) {
        CCDictionary *dict = m_tileMap->propertiesForGID(tileID);
        if (dict) {
            const CCString *isBlock = dict->valueForKey("block");
            if (isBlock) {
            //    CCLog("block tile at %i",tileID);
                hasCollision = true;
            }
        }
    }
    return hasCollision;
}

bool RCWorldManager::checkPositionInsideTileMap(cocos2d::CCPoint position)
{
    CCSize mapSize = getTilemapSizeInPixels();
    CCRect mapRect = CCRectMake(kPlayerOnMapEdgeSize.width
                                , kPlayerOnMapEdgeSize.height
                                , mapSize.width-kPlayerOnMapEdgeSize.width*2
                                , mapSize.height - kPlayerOnMapEdgeSize.height*2);
    if (pointIsInRect(position, mapRect)) {
        return true;
    }
    return false;
}

CCPoint RCWorldManager::checkBarrierCollisionForOffset(cocos2d::CCPoint offset, RCActor* player)
{
    CCPoint newOffset = offset;
    
    if (offset.x >=0 && offset.y >=0) {
        
    }
    else if(offset.x <0 && offset.y >= 0)
    {
    
    }
    
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

void RCWorldManager::setActorPositionOnTile(RCActor *actor, cocos2d::CCDictionary *tileDict)
{
    float x, y, width, height;
    x = tileDict->valueForKey("x")->floatValue();
    y = tileDict->valueForKey("y")->floatValue();
    width =  tileDict->valueForKey("width")->floatValue();
    height =  tileDict->valueForKey("height")->floatValue();
    actor->setPosition(ccp(x+width/2, y+height/2));
}


