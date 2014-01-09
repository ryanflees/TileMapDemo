//
//  RCMainMenu.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-7.
//
//

#include "RCMainMenu.h"
#include "CCNodeLoaderLibrary.h"

SEL_MenuHandler RCMainMenu::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
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

//bool RCMainMenu::init()
//{
//    if (!CCLayer::init()) {
//        return false;
//    }
//    CCNodeLoaderLibrary *loaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
//    CCBReader *ccbReader = new CCBReader(loaderLibrary);
//    CCNode *node = ccbReader->readNodeGraphFromFile("ccbi/main_menu.ccbi");
//    addChild(node);
//    return true;
//}
//


