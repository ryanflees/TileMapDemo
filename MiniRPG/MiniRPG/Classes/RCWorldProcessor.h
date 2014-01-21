//
//  RCWorldProcessor.h
//  TilemapDemo
//
//  Created by hy on 12/31/13.
//
//

#ifndef __TilemapDemo__RCWorldProcessor__
#define __TilemapDemo__RCWorldProcessor__

#include <iostream>
#include "cocos2d.h"
#include "RCControllerLayer.h"

#define kMoveUpAction "move_up"
#define kMoveDownAction "move_down"
#define kMoveLeftAction "move_left"
#define kMoveRightAction "move_right"
#define kStandDown "stand_down"
#define kStandUp "stand_up"
#define kStandLeft "stand_left"
#define kStandRight "stand_right"

typedef enum
{
    kActionMoveUp,
    kActionMoveDown,
    kActionMoveLeft,
    kActionMoveRight,
    kActionStandUp,
    kActionStandDown,
    kActionStandLeft,
    kActionStandRight
}ActorMoveDirectionEnum;

class RCWorldProcessor;
class RCWorldProcessorDelegate
{
public:
    virtual cocos2d::CCSize onGetWorldSize(RCWorldProcessor* worldProcessor) = 0;
    virtual cocos2d::CCSize onGetWorldSizeInPixels(RCWorldProcessor* worldProcessor) = 0;
};

class RCActor;
class RCWorldProcessor : public cocos2d::CCNode, public RCControllerLayerDelegate
{
public:
    RCWorldProcessor();
    ~RCWorldProcessor();
    virtual bool init();
    CREATE_FUNC(RCWorldProcessor);
    virtual void updateControllerVector(RCControllerLayer* controllerLayer, cocos2d::CCPoint pressedVector,float delta);
    void setControllerLayerRef(RCControllerLayer* controllerLayer);
    void setPlayerRef(RCActor* player);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
    
    void setTileMapGameNode(cocos2d::CCNode *gameNode, cocos2d::CCTMXTiledMap* tileMap);
    void setActorArray(cocos2d::CCArray *actorArray);
private:
    void checkObjectInteract(cocos2d::CCPoint point);
    
    cocos2d::CCPoint tilePosFromLocation(cocos2d::CCPoint location,
                                         cocos2d::CCTMXTiledMap* tileMap);
    
    cocos2d::CCRect getRectFromObjectProperties(cocos2d::CCDictionary* dict,
                                                cocos2d::CCTMXTiledMap*tileMap);
    
    bool checkBarrierCollision(cocos2d::CCPoint position);
    
    bool checkPositionInsideTileMap(cocos2d::CCPoint position);
    
    cocos2d::CCPoint checkBarrierCollisionForOffset(cocos2d::CCPoint offset, RCActor* player);

    void setActorPositionOnTile(RCActor *actor, cocos2d::CCDictionary *tileDict);
    
    cocos2d::CCSize getTilemapSize();
    
    cocos2d::CCSize getTilemapSizeInPixels();
    
    void adjustCamera(cocos2d::CCPoint moveOffset);
    
    CC_SYNTHESIZE(RCWorldProcessorDelegate*, m_delegate, Delegate);
    cocos2d::CCTMXTiledMap* m_tileMap;
    RCActor *m_player;
    cocos2d::CCNode *m_gameNode;
    RCControllerLayer* m_controllerLayer;
    cocos2d::CCArray *m_actorArray;
    cocos2d::CCPoint m_blockOffset;
    
    int m_playerAction;
    
    cocos2d::CCTMXLayer* m_miscLayer;
    cocos2d::CCTMXLayer* m_landscapeLayer;

    cocos2d::CCRect m_screenInsight;
};

#endif /* defined(__TilemapDemo__RCWorldProcessor__) */
