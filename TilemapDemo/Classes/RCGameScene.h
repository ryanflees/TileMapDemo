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
class RCActor;
class RCGameScene : public cocos2d::CCLayer
                , public RCControllerLayerDelegate
{
    
public:
    static cocos2d::CCScene *scene();
    
    virtual bool init();
    CREATE_FUNC(RCGameScene);
    
    void updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta);
private:
    RCControllerLayer *m_controllerLayer;
    RCTileWorld *m_tileWorld;
    
    RCActor *m_player;
    int m_playerAction;
};

#endif /* defined(__TilemapDemo__RCGameScene__) */
