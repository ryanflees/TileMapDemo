//
//  RCActor.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCActor.h"
#include "RCActorTemplate.h"

USING_NS_CC;

RCActor::RCActor()
{

}

RCActor::~RCActor()
{

}

RCActor *RCActor::createWithTemplate(RCActorTemplate *actorTemplate)
{
    RCActor *pRet = new RCActor();
    if (pRet && pRet->initWithTemplate(actorTemplate))
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

bool RCActor::initWithTemplate(RCActorTemplate *actorTemplate)
{
    if (!CCSprite::init()) {
        return false;
    }
    
    m_actionDictionary = CCDictionary::createWithDictionary(actorTemplate->getActionDictionary());
    m_actionDictionary->retain();
    
    m_texture = actorTemplate->getActorTexture();
    m_texture->retain();
    
    m_interval = 0.2f;
    m_intervalTimer = 0;
    m_frameIndex = 0;
    
    return true;
}

void RCActor::onEnter()
{
    CCSprite::onEnter();
    scheduleUpdate();
}

void RCActor::onExit()
{
    CCSprite::onExit();
    unscheduleUpdate();
}

void RCActor::update(float delta)
{
    CCSprite::update(delta);
    if (strcmp(m_curActionKey.c_str(), "") != 0) {
        CCDictionary *actionDict = (CCDictionary*)m_actionDictionary->objectForKey(m_curActionKey.c_str());
        CCArray *frameArray = (CCArray*)actionDict->objectForKey("frame_array");
        if (frameArray->count() > 1) {
            if (m_intervalTimer >= m_interval) {
                displayNextActionFrame(m_curActionKey.c_str());
                m_intervalTimer = 0;
            }
            else
            {
                m_intervalTimer += delta;
            }
        }
    }
}

void RCActor::setActorActionByKey(const char *actionKey)
{
    CCDictionary *actionDict = (CCDictionary*)m_actionDictionary->objectForKey(actionKey);
    if (!actionDict) {
        CCLOG("failed to set actor action, key not exist");
        return;
    }
    m_curActionKey = actionKey;
    m_intervalTimer = 0;
    m_frameIndex = 0;
    displayActionFirstFrame(m_curActionKey.c_str());
}

void RCActor::displayActionFirstFrame(const char *actionKey)
{
    CCDictionary *actionDict = (CCDictionary*)m_actionDictionary->objectForKey(actionKey);
    CCArray *frameArray = (CCArray*)actionDict->objectForKey("frame_array");
    CCDictionary *frameDict = (CCDictionary*)frameArray->objectAtIndex(0);
    displayFrameByDict(frameDict);
}

void RCActor::displayNextActionFrame(const char *actionKey)
{
    CCDictionary *actionDict = (CCDictionary*)m_actionDictionary->objectForKey(actionKey);
    CCArray *frameArray = (CCArray*)actionDict->objectForKey("frame_array");
    m_frameIndex ++;
    if (m_frameIndex == frameArray->count()) {
        m_frameIndex = 0;
    }
    CCDictionary *frameDict = (CCDictionary*)frameArray->objectAtIndex(m_frameIndex);
    displayFrameByDict(frameDict);
}

void RCActor::displayFrameByDict(cocos2d::CCDictionary *frameDict)
{
    int x = frameDict->valueForKey("x")->intValue();
    int y = frameDict->valueForKey("y")->intValue();
    int width = frameDict->valueForKey("width")->intValue();
    int height = frameDict->valueForKey("height")->intValue();
    CCRect rect = CCRectMake(x, y, width, height);
    CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(m_texture, rect);
    setDisplayFrame(frame);
}

CCRect RCActor::getRect()
{
    CCSize size = getContentSize();
    float x = getPositionX()-size.width*getAnchorPoint().x;
    float y = getPositionY()-size.height*getAnchorPoint().y;
    return CCRectMake(x, y, size.width, size.height);
}



