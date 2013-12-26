//
//  WorldScene.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-25.
//
//

#ifndef __TilemapDemo__WorldScene__
#define __TilemapDemo__WorldScene__

#include <iostream>
#include "cocos2d.h"

class WorldScene : public cocos2d::CCLayer {
    
public:
    static cocos2d::CCScene *scene();
    virtual bool init();
    CREATE_FUNC(WorldScene);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
    void addTileMap();
    
    cocos2d::CCNode *m_gameNode;
    cocos2d::CCTMXTiledMap *m_map;

};

#endif /* defined(__TilemapDemo__WorldScene__) */
