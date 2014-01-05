//
//  RCTileWorld.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCTileWorld__
#define __TilemapDemo__RCTileWorld__

#include <iostream>
#include "cocos2d.h"
#include "RCWorldManager.h"

class RCActor;
class RCActorTemplate;
class RCControllerLayer;
class RCTileWorld : public cocos2d::CCLayer, RCWorldManagerDelegate
{
    
public:
    RCTileWorld();
    ~RCTileWorld();
    virtual bool initWithTmxFile(const char* tmxFile);
    static RCTileWorld *createWithTmxFile(const char* tmxFile);
    
    void addPlayer(RCActorTemplate* actorTemplate);
    void removePlayer();
    
    void bindControllerLayer(RCControllerLayer* controllerLayer);
    RCActor *getPlayer(){ return m_player;}
    
    virtual cocos2d::CCSize onGetWorldSize(RCWorldManager* worldManager);
    virtual cocos2d::CCSize onGetWorldSizeInPixels(RCWorldManager* worldManager);
    void setWorldScale(float scale);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);
private:
    void generateNPCActors();
    void addNPC(const char *actorName, cocos2d::CCPoint position);
    cocos2d::CCPoint getTilePositionByDict(cocos2d::CCDictionary *tileDict);
    
    RCWorldManager *m_worldManager;
    cocos2d::CCNode *m_gameNode;
    cocos2d::CCNode *m_actorNode;
    
    cocos2d::CCTMXTiledMap *m_tileMap;
    RCActor *m_player;
    cocos2d::CCArray *m_actorArray;
    //RCActorController* m_actorController;
};


#endif /* defined(__TilemapDemo__RCTileWorld__) */
