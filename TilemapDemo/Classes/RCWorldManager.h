//
//  RCWorldManager.h
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#ifndef __TilemapDemo__RCWorldManager__
#define __TilemapDemo__RCWorldManager__

#include <iostream>
#include "cocos2d.h"
#include "RCControllerLayer.h"

class RCWorldManager;
class RCWorldManagerDelegate
{
public:
    virtual cocos2d::CCSize onGetWorldSize(RCWorldManager* worldManager) = 0;
    virtual cocos2d::CCSize onGetWorldSizeInPixels(RCWorldManager* worldManager) = 0;
};

class RCActor;
class RCWorldManager : public cocos2d::CCNode, public RCControllerLayerDelegate
{
public:
    RCWorldManager();
    ~RCWorldManager();
    virtual bool init();
    CREATE_FUNC(RCWorldManager);
    virtual void updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta);
    void setControllerLayerRef(RCControllerLayer* controllerLayer);
    void setPlayerRef(RCActor* player);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    void setTileMapeRef(cocos2d::CCTMXTiledMap* tileMap);
private:
    void checkObjectInteract(cocos2d::CCPoint point);
    cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint location,
                                         cocos2d::CCTMXTiledMap* tileMap);
    cocos2d::CCRect getRectFromObjectProperties(cocos2d::CCDictionary* dict,
                                                cocos2d::CCTMXTiledMap*tileMap);
    bool checkBarrierCollision(cocos2d::CCPoint position);
    cocos2d::CCPoint checkBarrierCollisionForOffset(cocos2d::CCPoint offset, RCActor* player);
    
    cocos2d::CCSize getTilemapSize();
    cocos2d::CCSize getTilemapSizeInPixels();
    void adjustCamera(cocos2d::CCPoint moveOffset);
    
    CC_SYNTHESIZE(RCWorldManagerDelegate*, m_delegate, Delegate);
    cocos2d::CCTMXTiledMap* m_tileMapeRef;
    RCActor *m_playerRef;
    CC_SYNTHESIZE(cocos2d::CCNode*, m_gameNodeRef, GameNodeRef);
    RCControllerLayer* m_controllerLayerRef;
    
    int m_playerAction;
    
    cocos2d::CCTMXLayer* m_miscLayer;
    cocos2d::CCTMXLayer* m_landscapeLayer;

    cocos2d::CCRect m_screenInsight;
};

#endif /* defined(__TilemapDemo__RCWorldManager__) */
