//
//  RCMainMenu.h
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-7.
//
//

#ifndef __TilemapDemo__RCMainMenu__
#define __TilemapDemo__RCMainMenu__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "RCMessageCenter.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RCMainMenu : public cocos2d::CCLayer
,public CCBSelectorResolver
,public CCBMemberVariableAssigner
,public CCNodeLoaderListener
,public RCMessageObserver
{
public:
    RCMainMenu();
    ~RCMainMenu();
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RCMainMenu, create);

    SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode);
    
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    
    virtual void onReceiveMessage(int messageCode, void *data, int length);
private:
    void onButtonClicked(CCNode* node);
};


class RCMainMenuLoader :public CCNodeLoader
{
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RCMainMenuLoader, loader);
    
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RCMainMenu);
};



#endif /* defined(__TilemapDemo__RCMainMenu__) */
