//
//  RCControllerLayer.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCControllerLayer.h"
#include "RCDPad.h"

USING_NS_CC;

RCControllerLayer::RCControllerLayer():m_delegate(NULL)
    ,m_dPad()
{

}

RCControllerLayer::~RCControllerLayer()
{

}

bool RCControllerLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    setTouchEnabled(true);
   
    m_dPad = RCDPad::create();
    addChild(m_dPad);
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    m_dPad->setPosition(ccp(screenSize.width*0.2f,screenSize.height*0.2f));
    
    m_buttonA = RCButton::createWithSpriteFrameFile("a_button_up.png", "a_button_down.png");
    addChild(m_buttonA);
    m_buttonA->setPosition(ccp(screenSize.width*0.8f,screenSize.height*0.2f));
    
    return true;
}

void RCControllerLayer::onEnter()
{
    CCLayer::onEnter();
    scheduleUpdate();
}

void RCControllerLayer::onExit()
{
    CCLayer::onExit();
    unscheduleUpdate();
}

void RCControllerLayer::update(float delta)
{
    if (m_delegate) {
        if (m_dPad) {
            m_delegate->updateControllerVector(this, m_dPad->getPressedVector(), delta);
        }
    }
}

void RCControllerLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCLog("touches count : %i", pTouches->count());
}

void RCControllerLayer::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCLog("touches count : %i", pTouches->count());

}

void RCControllerLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}

void RCControllerLayer::ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{

}


