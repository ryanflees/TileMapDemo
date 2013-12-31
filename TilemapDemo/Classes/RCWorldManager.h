//
//  RCWorldManager.h
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#ifndef __TilemapDemo__RCWorldManager__
#define __TilemapDemo__RCWorldManager__

#include <iostream>
#include "cocos2d.h"
#include "RCControllerLayer.h"

class RCActor;
class RCWorldManager : public cocos2d::CCNode, public RCControllerLayerDelegate
{
public:
    RCWorldManager();
    ~RCWorldManager();
    virtual bool init();
    CREATE_FUNC(RCWorldManager);
    virtual void updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta);
    void setControllerLayerRef(RCControllerLayer* controllerLayer);
    void setPlayerRef(RCActor* player);
private:
    CC_SYNTHESIZE(cocos2d::CCTMXTiledMap*, m_tileMapeRef, TileMapeRef);
    RCActor* m_playerRef;;
    RCControllerLayer* m_controllerLayerRef;
    
    int m_playerAction;

};

#endif /* defined(__TilemapDemo__RCWorldManager__) */
