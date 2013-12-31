//
//  RCControllerLayer.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCControllerLayer__
#define __TilemapDemo__RCControllerLayer__

#include <iostream>
#include "cocos2d.h"

class RCDPad;
class RCControllerLayer;
class RCControllerLayerDelegate
{
public:
    virtual void updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta) = 0;
};

class RCControllerLayer : public cocos2d::CCLayer {
public:
    RCControllerLayer();
    ~RCControllerLayer();
    virtual bool init();
    CREATE_FUNC(RCControllerLayer);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
private:
    RCDPad *m_dPad;
    CC_SYNTHESIZE(RCControllerLayerDelegate*, m_delegate, Delegate);
};

#endif /* defined(__TilemapDemo__RCControllerLayer__) */
