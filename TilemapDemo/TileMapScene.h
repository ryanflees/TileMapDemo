//
//  TileMapScene.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-24.
//
//

#ifndef __TilemapDemo__TileMapScene__
#define __TilemapDemo__TileMapScene__

#include <iostream>
#include "cocos2d.h"

class TileMapeScene : public cocos2d::CCLayer {
    
    
public:
    static cocos2d::CCScene *scene();
    virtual bool init();
    CREATE_FUNC(TileMapeScene);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    
    virtual void onEnter();
    virtual void onExit();
private:
    void addTileMap();
    void checkObjectInteract(cocos2d::CCPoint point);
    cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint location,
                                         cocos2d::CCTMXTiledMap* tileMap);
    cocos2d::CCRect getRectFromObjectProperties(cocos2d::CCDictionary* dict,
                                                cocos2d::CCTMXTiledMap*tileMap);
    
    cocos2d::CCTMXTiledMap *m_map;
};

#endif /* defined(__TilemapDemo__TileMapScene__) */
