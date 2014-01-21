//
//  RCButton.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-3.
//
//

#include "RCButton.h"
#include "func.h"

USING_NS_CC;

RCButton::RCButton()
{

}

RCButton::~RCButton()
{

}

RCButton* RCButton::createWithSpriteFrameFile(const char *normalFrame, const char *selectedFrame)
{
    RCButton *pRet = new RCButton();
    if (pRet && pRet->initWithSpriteFrameFile(normalFrame, selectedFrame))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }

}

bool RCButton::initWithSpriteFrameFile(const char *normalFrame, const char *selectedFrame)
{
    if (!CCSprite::init()) {
        return false;
    }
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("dpad_buttons.plist");
    
    m_normalFrameName = normalFrame;
    m_selectedFrameName = selectedFrame;
    
    CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_normalFrameName.c_str());
    setDisplayFrame(spriteFrame);
    
    return true;
}

bool RCButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    if (pointIsInCircle(touchPoint, getPosition(), rect().size.width/2)) {
        processTouch(touchPoint);
        return true;
    }
    return false;
}

void RCButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
    if (pointIsInCircle(touchPoint, getPosition(), rect().size.width)) {
        processTouch(touchPoint);
    }
    else
    {
        processRelease();
    }
}

void RCButton::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    processRelease();
}

void RCButton::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    processRelease();
}

void RCButton::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void RCButton::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCRect RCButton::rect()
{
    float scaleMod = 1.5f;
	float w = getContentSize().width * getScale() * scaleMod;
	float h = getContentSize().height * getScale() * scaleMod;
	CCPoint point = CCPointMake(getPositionX() - (w/2), getPositionY() - (h/2));
	return CCRectMake(point.x, point.y, w, h);
}

void RCButton::processTouch(cocos2d::CCPoint point)
{
    m_pressed = true;
    CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_selectedFrameName.c_str());
    setDisplayFrame(spriteFrame);
    setColor(ccc3(255, 200, 200));
}

void RCButton::processRelease()
{
    m_pressed = false;
    CCSpriteFrame *spriteFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(m_normalFrameName.c_str());
    setDisplayFrame(spriteFrame);
    setColor(ccc3(255, 255, 255));
}








