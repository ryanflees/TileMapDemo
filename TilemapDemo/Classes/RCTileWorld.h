//
//  RCTileWorld.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCTileWorld__
#define __TilemapDemo__RCTileWorld__

#include <iostream>
#include "cocos2d.h"

class RCTileWorld : public cocos2d::CCLayer {
    
public:
    virtual bool initWithTmxFile(const char* tmxFile);
    static RCTileWorld *createWithTmxFile(const char* tmxFile);
    
private:
    cocos2d::CCTMXTiledMap *m_tileMap;
    cocos2d::CCNode *m_gameNode;
    //RCActorController* m_actorController;
};


#endif /* defined(__TilemapDemo__RCTileWorld__) */
