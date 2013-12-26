//
//  TileMapScene.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-24.
//
//

#include "TileMapScene.h"
#include "func.h"

USING_NS_CC;

CCScene* TileMapeScene::scene()
{
    CCScene* scene = CCScene::create();
    TileMapeScene* layer = TileMapeScene::create();
    scene->addChild(layer);
    return scene;
}

bool TileMapeScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    addTileMap();
    return true;
}


void TileMapeScene::onEnter()
{
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void TileMapeScene::onExit()
{
    CCLayer::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void TileMapeScene::addTileMap()
{
    m_map = CCTMXTiledMap::create("tilemap/hellotilemap.tmx");
    //CCTMXTiledMap *map = CCTMXTiledMap::create("tilemap/orthogonal.tmx");
    addChild(m_map);
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    //map->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    m_map->setPosition(CCPointZero);

    CCTMXLayer* eventLayer = m_map->layerNamed("GameEventLayer");
    eventLayer->setVisible(false);
}

bool TileMapeScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //CCLog("layer touched");
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    CCPoint tilePos = m_map->convertToNodeSpace(touchLocation);
    tilePos = tilePosFromLocation(tilePos, m_map);
    CCLog("touch tilemap %f %f", tilePos.x, tilePos.y);
    CCTMXLayer* backgroundLayer = m_map->layerNamed("Background");
    bool touchOnWater = false;
    int tileGID = backgroundLayer->tileGIDAt(tilePos);
    if (tileGID != 0) {
        CCDictionary *dict = m_map->propertiesForGID(tileGID);
        if (dict) {
            const CCString *isWater = dict->valueForKey("isWater");
            if (isWater) {
                touchOnWater = isWater->boolValue();
            }
        }
    }
    
    if (touchOnWater) {
        CCLog("touch on water");
    }
    
    checkObjectInteract(touchLocation);
    return true;
}


void TileMapeScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void TileMapeScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void TileMapeScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

CCPoint TileMapeScene::tilePosFromLocation(CCPoint location,CCTMXTiledMap* tileMap)
{
    // Tilemap position must be offset, in case the tilemap is scrolling CGPoint pos = ccpSub(location, tileMap.position);
    // Cast to int makes sure that result is in whole numbers
    CCPoint pos = ccpSub(location, tileMap->getPosition());

    pos.x = (int)(pos.x / tileMap->getTileSize().width);
    pos.y = (int)((tileMap->getMapSize().height * tileMap->getTileSize().height - pos.y) /
tileMap->getTileSize().height);
    CCLog("touch at (%.0f, %.0f) is at tileCoord (%i, %i)", location.x, location.y,(int)pos.x, (int)pos.y);
    return pos;
}


void TileMapeScene::checkObjectInteract(cocos2d::CCPoint point)
{
    CCTMXObjectGroup *objectLayer = m_map->objectGroupNamed("ObjectLayer");
    bool isTouchInRect = false;
    for (int i=0; i<objectLayer->getObjects()->count(); i++) {
        CCDictionary *dict = (CCDictionary*)objectLayer->getObjects()->objectAtIndex(i);
        CCRect rect = getRectFromObjectProperties(dict, m_map);
        if (pointIsInRect(point, rect)) {
            isTouchInRect = true;
            break;
        }
    }
    if (isTouchInRect) {
        CCLog("touch in rect");
    }
}

CCRect TileMapeScene::getRectFromObjectProperties(CCDictionary* dict,CCTMXTiledMap*tileMap)
{
    float x, y, width, height;
    x = dict->valueForKey("x")->floatValue() + tileMap->getPositionX();
    y = dict->valueForKey("y")->floatValue() + tileMap->getPositionY();
    width =  dict->valueForKey("width")->floatValue();
    height =  dict->valueForKey("height")->floatValue();
    return CCRectMake(x, y, width, height);
}






