//
//  RCLoadingScene.cpp
//  HYDemo
//
//  Created by Bai Ryan on 14-1-20.
//
//

#include "RCLoadingScene.h"
#include "SimpleAudioEngine.h"
#include "RCGameScene.h"

using namespace CocosDenshion;

#define kLoadingDelayTime 1.0f

RCLoadingScene::RCLoadingScene()
:m_loadingSceneTag()
{
}

RCLoadingScene::~RCLoadingScene()
{
    
}

bool RCLoadingScene::init()
{
    if (!CCNode::init()) {
        return false;
    }
    return true;
}

SEL_MenuHandler RCLoadingScene::onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler RCLoadingScene::onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName)
{
    return NULL;
}

bool RCLoadingScene::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
    return false;
}

bool RCLoadingScene::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, CCBValue* pCCBValue)
{
    
    return false;
}

void RCLoadingScene::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    
}

void RCLoadingScene::onEnter()
{
    CCNode::onEnter();
    
    CCCallFunc *loadRes = CCCallFunc::create(this, callfunc_selector(RCLoadingScene::loadResources));
    CCFiniteTimeAction *seq = CCSequence::create(CCDelayTime::create(kLoadingDelayTime),loadRes,NULL);
    runAction(seq);
}

void RCLoadingScene::onExit()
{
    CCNode::onExit();
}

static void* loadThreadFunction(void* data)
{
//    CCTextureCache::sharedTextureCache()->addImageAsync("Imagesetfile/mainScene1.png", NULL, NULL);
//    CCTextureCache::sharedTextureCache()->addImageAsync("Imagesetfile/mainScene2.png", NULL, NULL);
//    CCTextureCache::sharedTextureCache()->addImageAsync("Imagesetfile/mainScene3.png", NULL, NULL);
//    CCTextureCache::sharedTextureCache()->addImageAsync("Imagesetfile/mainScene4.png", NULL, NULL);
//    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("general.mp3");
//    SimpleAudioEngine::sharedEngine()->preloadEffect("click.mp3");
//
    //SimpleAudioEngine::sharedEngine()->preloadEffect("Y_BOSS.wav");
    RCLoadingScene *loadingScene = (RCLoadingScene*)data;
    loadingScene->loadResourceFinished();
    return NULL;
}

void RCLoadingScene::loadResourceFinished()
{
    CCCallFunc *callNext = CCCallFunc::create(this, callfunc_selector(RCLoadingScene::playNextScene));
    CCFiniteTimeAction *seq = CCSequence::create(CCDelayTime::create(kLoadingDelayTime),callNext,NULL);
    runAction(seq);
}

void RCLoadingScene::loadResources()
{
    int errCode = 0;
    do {
        pthread_attr_t addr;
        errCode = pthread_attr_init(&addr);
        
        CC_BREAK_IF(errCode != 0);
        
        errCode = pthread_attr_setdetachstate(&addr, PTHREAD_CREATE_DETACHED);
        
        if (errCode != 0) {
            pthread_attr_destroy(&addr);
            break;
        }
        
        errCode = pthread_create(&threadLoadResource, &addr, loadThreadFunction, this);
    } while (0);
}

void RCLoadingScene::playNextScene()
{
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Imagesetfile/mainScene1.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Imagesetfile/mainScene2.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Imagesetfile/mainScene3.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Imagesetfile/mainScene4.plist");
//    RCSceneManager::sharedSceneManager()->switchToOnePieceGameScene();
    switch (m_loadingSceneTag) {
        case kLoadingGameScene:
            {
                CCScene* scene = CCScene::create();
                RCGameScene* node = RCGameScene::create();
                scene->addChild(node);
                CCDirector::sharedDirector()->replaceScene(scene);
                node->addTileMap(m_tileMapName.c_str());
            }
            break;
            
        default:
            break;
    }
}
