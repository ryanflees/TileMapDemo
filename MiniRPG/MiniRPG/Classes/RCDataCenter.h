//
//  RCDataCenter.h
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-28.
//
//

#ifndef __MiniRPG__RCDataCenter__
#define __MiniRPG__RCDataCenter__

#include "cocos2d.h"
#include "netmsg.pb.h"
#include <sqlite3.h>

using namespace MessageCode;

USING_NS_CC;
using namespace std;

class RCActorTemplateData : public CCObject
{
public:
    CREATE_FUNC(RCActorTemplateData);
    bool init()
    {
        return true;
    }
    int id;
    string name;
    string title;
    string faction;
    string plist;
};

class RCDataCenter :public CCNode
{
public:
    static RCDataCenter* sharedDataCenter();
    static RCDataCenter* m_instanceOfDataCenter;
    static void purge();
    RCDataCenter();
    virtual ~RCDataCenter();
    virtual bool init();
    CREATE_FUNC(RCDataCenter);
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    void handleMessage(void* data, int length);
    
    const char* getMapFileByID(int id);
    RCActorTemplateData* getActorTemplateDataByID(int id);
private:
    void dispatchMessage(void* data, int length);
    void processMessage(CCNode* node, void* data);
    void parseProtoLoginReq(ProtoLoginReq* req);

    void loadMapData();
    
    sqlite3 *m_mapDataBase;
};

#endif /* defined(__MiniRPG__RCDataCenter__) */
