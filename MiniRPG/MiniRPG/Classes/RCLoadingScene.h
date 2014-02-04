//
//  RCLoadingScene.h
//  HYDemo
//
//  Created by Bai Ryan on 14-1-20.
//
//

#ifndef __HYDemo__RCLoadingScene__
#define __HYDemo__RCLoadingScene__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

typedef enum
{
    kLoadingGameScene = 1
}LoadingSceneTag;

class RCLoadingScene : public CCNode
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
,public CCNodeLoaderListener
{
public:
    RCLoadingScene();
    ~RCLoadingScene();
    virtual bool init();
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RCLoadingScene, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual void onEnter();
    virtual void onExit();

    void loadResourceFinished();
    
private:
    void loadResources();
    void playNextScene();
    pthread_t threadLoadResource;

    CC_SYNTHESIZE(int, m_loadingSceneTag, LoadingSceneTag);
    CC_SYNTHESIZE(string, m_tileMapName, TileMapName);
};

class RCLoadingSceneLoader :public CCNodeLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RCLoadingSceneLoader, loader);
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RCLoadingScene);
};


#endif /* defined(__HYDemo__RCLoadingScene__) */
