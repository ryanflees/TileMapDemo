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
#include "RCControllerLayer.h"

class RCTileWorld;

class RCGameScene : public cocos2d::CCLayer {
    
public:
    static cocos2d::CCScene *scene();
    
    virtual bool init();
    CREATE_FUNC(RCGameScene);
    
private:
    RCControllerLayer *m_controllerLayer;
    RCTileWorld *m_tileWorld;
};

#endif /* defined(__TilemapDemo__RCGameScene__) */
