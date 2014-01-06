//
//  RCDPad.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCDPad.h"
#include "func.h"

USING_NS_CC;

bool RCDPad::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    m_pressedVector = CCPointZero;
    m_direction = kDPadNoDirection;
    m_pressed = false;
    
    CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
    cache->addSpriteFramesWithFile("dpad_buttons.plist");
    setDisplayFrame(cache->spriteFrameByName("d_pad_normal.png"));
    
    return true;
}

void RCDPad::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void RCDPad::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool RCDPad::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint touchPoint = pTouch->getLocation();
   if (pointIsInCircle(touchPoint, getPosition(), rect().size.width/2)) {
        processTouch(touchPoint);
        return true;
    }
    return false;
}

void RCDPad::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
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

void RCDPad::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    processRelease();
}

void RCDPad::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    processRelease();
}

CCRect RCDPad::rect()
{
    float scaleMod = 1.5f;
	float w = getContentSize().width * getScale() * scaleMod;
	float h = getContentSize().height * getScale() * scaleMod;
	CCPoint point = CCPointMake(getPositionX() - (w/2), getPositionY() - (h/2));
	return CCRectMake(point.x, point.y, w, h);
}

void RCDPad::processTouch(cocos2d::CCPoint point)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	setColor(ccc3(255,200,200));
	m_pressed = true;
	CCPoint center = ccp( rect().origin.x+rect().size.width/2, rect().origin.y+rect().size.height/2 );
	if(distanceBetweenPoints(point, center) < rect().size.width/10){
        setDisplayFrame(cache->spriteFrameByName("d_pad_normal.png"));
		setRotation(0);
		m_pressedVector = ccp(0,0);
		m_direction = kDPadNoDirection;
		return;
	}
	float radians = vectorToRadians( ccp(point.x-center.x, point.y-center.y) );
	float degrees = radiansToDegrees(radians) + 90;
    float sin45 = 0.7071067812f;
	if(degrees >= 337.5 || degrees < 22.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_horizontal.png"));
		setRotation(180);
        m_pressedVector = ccp(-1,0);
        m_direction = kDPadLeft;
	}else if(degrees >= 22.5 && degrees < 67.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_diagonal.png"));
		setRotation(-90);
        m_pressedVector = ccp(-sin45,sin45);
        m_direction = kDPadUpLeft;
	}else if(degrees >= 67.5 && degrees < 112.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_horizontal.png"));
		setRotation(-90);
        m_pressedVector = ccp(0,1);
        m_direction = kDPadUp;
	}else if(degrees >= 112.5 && degrees < 157.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_diagonal.png"));
		setRotation(0);
        m_pressedVector = ccp(sin45,sin45);
        m_direction = kkDPadUpRight;
	}else if(degrees >= 157.5 && degrees < 202.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_horizontal.png"));
		setRotation(0);
        m_pressedVector = ccp(1,0);
        m_direction = kkDPadRight;
	}else if(degrees >= 202.5 && degrees < 247.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_diagonal.png"));
		setRotation(90);
        m_pressedVector = ccp(sin45,-sin45);
        m_direction = kDPadDownRight;
	}else if(degrees >= 247.5 && degrees < 292.5){
		setDisplayFrame(cache->spriteFrameByName("d_pad_horizontal.png"));
		setRotation(90);
        m_pressedVector = ccp(0,-1);
        m_direction = kDPadDown;
	}else{
		setDisplayFrame(cache->spriteFrameByName("d_pad_diagonal.png"));
		setRotation(180);
        m_pressedVector = ccp(-sin45,-sin45);
        m_direction = kDPadDownLeft;
	}

}

void RCDPad::processRelease()
{
    setColor(ccc3(255,255,255));
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	setDisplayFrame(cache->spriteFrameByName("d_pad_normal.png"));
	setRotation(0);
	m_pressed = false;
	m_pressedVector = ccp(0,0);
	m_direction = kDPadNoDirection;
}



