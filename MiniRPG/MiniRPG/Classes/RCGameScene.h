//
//  RCGameScene.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCGameScene__
#define __TilemapDemo__RCGameScene__


#include <iostream>
#include "cocos2d.h"

class RCTileWorld;
class RCActor;
class RCControllerLayer;
class RCGameScene : public cocos2d::CCLayer
{
    
public:
    static cocos2d::CCScene *scene();
    
    virtual bool init();
    CREATE_FUNC(RCGameScene);
    
    virtual void onEnter();
    virtual void onExit();
    
    void addTileMap(const char* tileMap);
private:
    RCControllerLayer *m_controllerLayer;
    RCTileWorld *m_tileWorld;
    
    RCActor *m_player;
};

#endif /* defined(__TilemapDemo__RCGameScene__) */
