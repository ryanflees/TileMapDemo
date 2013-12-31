//
//  RCDPad.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCDPad__
#define __TilemapDemo__RCDPad__

#include <iostream>
#include "cocos2d.h"

enum
{
	kDPadNoDirection,
	kDPadUp,
	kkDPadUpRight,
	kkDPadRight,
	kDPadDownRight,
	kDPadDown,
	kDPadDownLeft,
	kDPadLeft,
	kDPadUpLeft
};

class RCDPad : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{
public:
    virtual bool init();
    CREATE_FUNC(RCDPad);

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    virtual void onEnter();
    virtual void onExit();
    
private:
    cocos2d::CCRect rect();
    void processTouch(cocos2d::CCPoint point);
    void processRelease();
    
    CC_SYNTHESIZE_READONLY(cocos2d::CCPoint, m_pressedVector, PressedVector);
    CC_SYNTHESIZE_READONLY(int, m_direction, Direction);
    
    bool m_pressed;
    unsigned int m_touchHash;

};

#endif /* defined(__TilemapDemo__RCDPad__) */
