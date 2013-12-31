//
//  RCActorTemplateCache.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCActorTemplateCache__
#define __TilemapDemo__RCActorTemplateCache__

#include <iostream>
#include "cocos2d.h"

class RCActorTemplate;

class RCActorTemplateCache : cocos2d::CCNode {
public:
    static RCActorTemplateCache* sharedActorTemplateCache();
    static void purge();
    static RCActorTemplateCache* m_instanceOfActorTemplate;
    
    RCActorTemplateCache();
    ~RCActorTemplateCache();
    virtual bool init();
    CREATE_FUNC(RCActorTemplateCache);
    void dumpAllActorTemplates();
    void addActorByFile(const char* plistFile);
    RCActorTemplate* getActorTemplateByName(const char* actorName);
private:
    cocos2d::CCArray *m_actorTemplateArray;
};

#endif /* defined(__TilemapDemo__RCActorTemplateCache__) */
