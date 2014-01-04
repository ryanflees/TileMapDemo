//
//  RCButton.h
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-3.
//
//

#ifndef __TilemapDemo__RCButton__
#define __TilemapDemo__RCButton__

#include <iostream>
#include "cocos2d.h"

using namespace std;

class RCButton : public cocos2d::CCSprite, public cocos2d::CCTargetedTouchDelegate
{

public:
    RCButton();
    ~RCButton();
    static RCButton *createWithSpriteFrameFile(const char *normalFrame, const char *selectedFrame);
    virtual bool initWithSpriteFrameFile(const char *normalFrame, const char *selectedFrame);
    
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
    
    CC_SYNTHESIZE(string, m_normalFrameName, NormalFrameName);
    CC_SYNTHESIZE(string, m_selectedFrameName, SelectedFrameName);

    bool m_pressed;
    unsigned int m_touchHash;
};

#endif /* defined(__TilemapDemo__RCButton__) */
