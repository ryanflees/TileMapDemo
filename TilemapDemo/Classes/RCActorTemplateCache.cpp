//
//  RCActorTemplateCache.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#include "RCActorTemplateCache.h"
#include "RCActorTemplate.h"
#include "RCStringHelper.h"

USING_NS_CC;
using namespace std;

RCActorTemplateCache* RCActorTemplateCache::sharedActorTemplateCache()
{
    if (!m_instanceOfActorTemplate) {
        m_instanceOfActorTemplate = RCActorTemplateCache::create();
        m_instanceOfActorTemplate->retain();
    }
    return m_instanceOfActorTemplate;
}

void RCActorTemplateCache::purge()
{
    CC_SAFE_RELEASE(m_instanceOfActorTemplate);
}

RCActorTemplateCache* RCActorTemplateCache::m_instanceOfActorTemplate = NULL;

RCActorTemplateCache::RCActorTemplateCache()
{

}

RCActorTemplateCache::~RCActorTemplateCache()
{
    m_actorTemplateArray->release();
}

bool RCActorTemplateCache::init()
{
    if (!CCNode::init()) {
        return false;
    }
    
    m_actorTemplateArray = CCArray::create();
    m_actorTemplateArray->retain();
    
    return true;
}

void RCActorTemplateCache::dumpAllActorTemplates()
{
    m_actorTemplateArray->removeAllObjects();
}

RCActorTemplate* RCActorTemplateCache::getActorTemplateByName(const char* actorName)
{
    RCActorTemplate *result = NULL;
    CCObject *object;
    CCARRAY_FOREACH(m_actorTemplateArray, object)
    {
        RCActorTemplate *actorTemplate = dynamic_cast<RCActorTemplate*>(object);
        if (actorTemplate && strcmp(actorTemplate->getActorName().c_str(), actorName) == 0) {
            result = actorTemplate;
            break;
        }
    }
    return result;
}

void RCActorTemplateCache::addActorByFile(const char *plistFile)
{
   // string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistFile);
    CCDictionary *dict = CCDictionary::createWithContentsOfFile(plistFile);
    
    CCArray *actorArray = (CCArray*)dict->objectForKey("actor_array");
    CCObject *object;
    CCARRAY_FOREACH(actorArray, object)
    {
        CCDictionary *actorDict = (CCDictionary*)object;
        CCString *textureFile = (CCString*)actorDict->objectForKey("texture");
        CCString *textureFolder = RCStringHelper::sharedStringHelper()->stringByDeletingLastPathComponent(plistFile);
        CCString *texturePath = RCStringHelper::sharedStringHelper()->stringByAppendingPathComponent(textureFolder->getCString(), textureFile->getCString());
        CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(texturePath->getCString());
        if (!texture) {
            CCLOG("failed to load texture %s", texturePath->getCString());
            continue;
        }
        RCActorTemplate *actorTemplate = RCActorTemplate::createWithDict(actorDict);
        actorTemplate->setActorTexture(texture);
        m_actorTemplateArray->addObject(actorTemplate);
    }
}










