//
//  RCMainMenu.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-7.
//
//

#include "RCMainMenu.h"
#include "CCNodeLoaderLibrary.h"
#include "RCGameScene.h"

RCMainMenu::RCMainMenu()
{

}

RCMainMenu::~RCMainMenu()
{

}

SEL_MenuHandler RCMainMenu::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "playButtonClicked", RCMainMenu::onButtonClicked);
    
    return NULL;
}

SEL_CCControlHandler RCMainMenu::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return false;
}

bool RCMainMenu::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    return false;
}

bool RCMainMenu::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    return false;
}

void RCMainMenu::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{

}

void RCMainMenu::onButtonClicked(CCNode* node)
{
    CCScene* scene = CCScene::create();
    RCGameScene* layer = RCGameScene::create();
    scene->addChild(layer);
    CCDirector::sharedDirector()->replaceScene(scene);
}


