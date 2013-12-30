//
//  WorldScene.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-25.
//
//

#include "WorldScene.h"

USING_NS_CC;

CCScene *WorldScene::scene()
{
    CCScene *scene = CCScene::create();
    WorldScene *layer = WorldScene::create();
    scene->addChild(layer);
    return scene;
}

bool WorldScene::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    m_gameNode = CCNode::create();
    addChild(m_gameNode);
    
   // m_map = CCTMXTiledMap::create("tilemap/worldmap.tmx");
   // m_gameNode->addChild(m_map);
    
    
    return true;
}

void WorldScene::onEnter()
{
    CCLayer::onEnter();
}

void WorldScene::onExit()
{
    CCLayer::onExit();
}

bool WorldScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return true;
}


void WorldScene::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void WorldScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void WorldScene::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

}

void WorldScene::addTileMap()
{

}








