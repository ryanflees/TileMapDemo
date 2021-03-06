//
//  RCActorTemplate.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCActorTemplate__
#define __TilemapDemo__RCActorTemplate__

#include <iostream>
#include "cocos2d.h"

using namespace std;

class RCActorTemplate : public cocos2d::CCNode {
public:
    RCActorTemplate();
    ~RCActorTemplate();
    static RCActorTemplate *createWithDict(cocos2d::CCDictionary *dict);
    virtual bool initWithDict(cocos2d::CCDictionary *dict);
    
private:
    CC_SYNTHESIZE(string, m_actorName, ActorName);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCTexture2D*, m_actorTexture, ActorTexture);
    CC_SYNTHESIZE_READONLY(cocos2d::CCDictionary*, m_actionDictionary, ActionDictionary);
};

#endif /* defined(__TilemapDemo__RCActorTemplate__) */
