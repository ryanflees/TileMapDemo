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

bool RCControllerLayer::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_dPad = RCDPad::create();
    addChild(m_dPad);
    
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    m_dPad->setPosition(ccp(screenSize.width*0.2f,screenSize.height*0.2f));
    
    return true;
}




