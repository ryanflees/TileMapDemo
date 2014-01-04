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
#include "RCButton.h"

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
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    RCDPad *m_dPad;
    RCButton *m_buttonA;
    CC_SYNTHESIZE(RCControllerLayerDelegate*, m_delegate, Delegate);
};

#endif /* defined(__TilemapDemo__RCControllerLayer__) */
