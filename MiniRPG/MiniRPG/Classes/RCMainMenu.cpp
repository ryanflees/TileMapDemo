//
//  RCMainMenu.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-7.
//
//

#include "RCMessage.h"
#include "RCMainMenu.h"
#include "CCNodeLoaderLibrary.h"
#include "RCGameScene.h"
#include "netmsg.pb.h"
#include "RCDataCenter.h"
#include "RCGameEntry.h"

using namespace MessageCode;

RCMainMenu::RCMainMenu()
{

}

RCMainMenu::~RCMainMenu()
{
    unregisterMessageCode();
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
    registerMessageCode(MC_PROTOLOGINRES);
}

void RCMainMenu::onReceiveMessage(int messageCode, void *data, int length)
{
    switch (messageCode) {
        case MC_PROTOLOGINRES:
        {
            ProtoLoginRes* res = new ProtoLoginRes();
            res->ParseFromArray(data, length);
            int mapID = res->mapid();
            const char* mapFile = RCDataCenter::sharedDataCenter()->getMapFileByID(mapID);
            RCGameEntry::sharedGameEntry()->showGameScene(mapFile);
            delete (res);
        }
            break;
        default:
            break;
    }
}

void RCMainMenu::onButtonClicked(CCNode* node)
{
    ProtoLoginReq* req = new ProtoLoginReq();
    req->set_authid(1);
    SEND_MESSAGE(MC_PROTOLOGINREQ, req);
    delete (req);
//    CCScene* scene = CCScene::create();
//    RCGameScene* layer = RCGameScene::create();
//    scene->addChild(layer);
//    CCDirector::sharedDirector()->replaceScene(scene);
}

void RCMainMenu::onEnter()
{
    CCLayer::onEnter();
}

void RCMainMenu::onExit()
{
    CCLayer::onExit();
}

void RCMainMenu::update(float dt)
{
    CCLog("mainmenu update");
}
