//
//  RCActorTemplate.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCActorTemplate.h"

USING_NS_CC;

RCActorTemplate::RCActorTemplate():m_actionDictionary(NULL)
            ,m_actorTexture(NULL)
{

}

RCActorTemplate::~RCActorTemplate()
{
    CC_SAFE_RELEASE(m_actorTexture);
}

RCActorTemplate *RCActorTemplate::createWithDict(cocos2d::CCDictionary *dict)
{
    RCActorTemplate *pRet = new RCActorTemplate();
    if (pRet && pRet->initWithDict(dict))
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

bool RCActorTemplate::initWithDict(cocos2d::CCDictionary *dict)
{
    if (!CCNode::init()) {
        return false;
    }
    
    m_actionDictionary = CCDictionary::createWithDictionary(dict);
    m_actionDictionary->retain();
    
    CCString *actorName = (CCString*)dict->objectForKey("name");
    m_actorName = actorName->getCString();
    
    CCArray *actionArray = (CCArray*)dict->objectForKey("action_array");
    CCObject *object;
    CCARRAY_FOREACH(actionArray, object)
    {
        CCDictionary *actionDict = (CCDictionary*)object;
        CCString *actionName = (CCString*)actionDict->objectForKey("action_name");
        m_actionDictionary->setObject(actionDict, actionName->getCString());
    }
    
    return true;
}




