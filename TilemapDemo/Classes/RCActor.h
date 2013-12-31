//
//  RCActor.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCActor__
#define __TilemapDemo__RCActor__

#include <iostream>
#include "cocos2d.h"

using namespace std;

class RCActorTemplate;
class RCActor : public cocos2d::CCSprite {

public:
    RCActor();
    ~RCActor();
    
    virtual bool initWithTemplate(RCActorTemplate *actorTemplate);
    static RCActor *createWithTemplate(RCActorTemplate *actorTemplate);
    
    void setActorActionByKey(const char* actionKey);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
private:
    CC_SYNTHESIZE(float, m_speed, Speed);
    CC_SYNTHESIZE_READONLY(string, m_curActionKey, CurActionKey);
    cocos2d::CCDictionary *m_actionDictionary;
    cocos2d::CCTexture2D *m_texture;
    float m_interval;
    float m_intervalTimer;
    int m_frameIndex;
    
    void displayNextActionFrame(const char *actionKey);
    void displayActionFirstFrame(const char *actionKey);
    void displayFrameByDict(cocos2d::CCDictionary *frameDict);
};

#endif /* defined(__TilemapDemo__RCActor__) */
