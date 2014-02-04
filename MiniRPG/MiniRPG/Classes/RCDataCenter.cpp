//
//  RCDataCenter.cpp
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-28.
//
//

#include "RCDataCenter.h"
#include "RCMessage.h"
#include "RCMessageCenter.h"
#include "RCDataNode.h"

#define PROCESS_MESSAGE_DELAY 0.3f

#define MAP_DATABASE "map_data.sqlite"
#define ACTOR_TEMPLATE_DATABASE "actor_template.sqlite"

RCDataCenter* RCDataCenter::sharedDataCenter()
{
    if (!m_instanceOfDataCenter) {
        m_instanceOfDataCenter = RCDataCenter::create();
        m_instanceOfDataCenter->retain();
    }
    return m_instanceOfDataCenter;
}

RCDataCenter* RCDataCenter::m_instanceOfDataCenter = NULL;

void RCDataCenter::purge()
{
    CC_SAFE_RELEASE(m_instanceOfDataCenter);
    m_instanceOfDataCenter = NULL;
}

RCDataCenter::RCDataCenter()
:m_mapDataBase()
{

}

RCDataCenter::~RCDataCenter()
{
}

bool RCDataCenter::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    loadMapData();
    return true;
}

void RCDataCenter::handleMessage(void* data, int length)
{
    RCDataNode* dataNode = RCDataNode::create();
    dataNode->retain();
    
    memcpy(dataNode->getMessageStruct(), data, length);
    dataNode->setDataLength(length);
    
    CCCallFuncND* callback = CCCallFuncND::create(this, callfuncND_selector(RCDataCenter::processMessage), dataNode);
    CCFiniteTimeAction* seq = CCSequence::create(CCDelayTime::create(PROCESS_MESSAGE_DELAY), callback, NULL);
    CCDirector::sharedDirector()->getRunningScene()->runAction(seq);
}

const char* RCDataCenter::getMapFileByID(int id)
{
    sqlite3_stmt* statement;
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(MAP_DATABASE);
    int res = sqlite3_open(path.c_str(), &m_mapDataBase);
    if (res == SQLITE_OK) {
        CCString *selectValue = CCString::createWithFormat("select * from map where id=%i",id);
        int ret = sqlite3_prepare_v2(m_mapDataBase, selectValue->getCString(), (int)strlen(selectValue->getCString()), &statement, NULL);
        ret = sqlite3_step(statement);
        if (ret == SQLITE_ROW) {
            string mapName = (const char*)sqlite3_column_text(statement, 1);
            string mapFile = (const char*)sqlite3_column_text(statement, 2);
            CCLog("mapeName: %s mpaeFile %s", mapName.c_str(), mapFile.c_str());
            return mapFile.c_str();
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(m_mapDataBase);
    return NULL;
}

RCActorTemplateData* RCDataCenter::getActorTemplateDataByID(int id)
{
    RCActorTemplateData* actorTemplateData = RCActorTemplateData::create();
    sqlite3 *dataBase;
    sqlite3_stmt* statement;
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(ACTOR_TEMPLATE_DATABASE);
    int res = sqlite3_open(path.c_str(), &dataBase);
    if (res == SQLITE_OK) {
        CCString *selectValue = CCString::createWithFormat("select * from actor where id=%i",id);
        int ret = sqlite3_prepare_v2(dataBase, selectValue->getCString(), (int)strlen(selectValue->getCString()), &statement, NULL);
        ret = sqlite3_step(statement);
        if (ret == SQLITE_ROW) {
            actorTemplateData->name = (const char*)sqlite3_column_text(statement, 1);
            actorTemplateData->title = (const char*)sqlite3_column_text(statement, 2);
            actorTemplateData->plist = (const char*)sqlite3_column_text(statement, 4);
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(dataBase);
    return actorTemplateData;
}

void RCDataCenter::dispatchMessage(void* data, int length)
{
    RCMessageCenter::sharedMessageCenter()->onReceiveMessage(data, length);
}

void RCDataCenter::parseProtoLoginReq(ProtoLoginReq* req)
{
    CCLog("req : %i", req->authid());
    ProtoLoginRes* res = new ProtoLoginRes();
    res->set_mapid(1);
    RCMessageStruct* messageStruct = new RCMessageStruct();
    
    messageStruct->messageCode = MC_PROTOLOGINRES;
    res->SerializeToArray(messageStruct->data, res->ByteSize());
    int size = res->ByteSize() + sizeof(messageStruct->messageCode);
    dispatchMessage(messageStruct, size);
    
    delete (messageStruct);
    delete (res);
}

void RCDataCenter::processMessage(cocos2d::CCNode *node, void *data)
{
    CCLog("processMessage");
    RCDataNode* dataNode = (RCDataNode*)data;
    switch (dataNode->getMessageStruct()->messageCode) {
        case MC_PROTOLOGINREQ:
        {
            ProtoLoginReq* req = new ProtoLoginReq();
            int messageSize = dataNode->getDataLength() - sizeof(dataNode->getMessageStruct()->messageCode);
            req->ParseFromArray(dataNode->getMessageStruct()->data, messageSize);
            parseProtoLoginReq(req);
            delete (req);
        }
            break;
            
        default:
            break;
    }
    
    dataNode->release();
}

void RCDataCenter::update(float dt)
{
 //   CCLog("update");
}

void RCDataCenter::onEnter()
{
    CCNode::onEnter();
}

void RCDataCenter::onExit()
{
    CCNode::onExit();
}

void RCDataCenter::loadMapData()
{
    const char* mapSqlite = MAP_DATABASE;
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(mapSqlite);
    int res = sqlite3_open(path.c_str(), &m_mapDataBase);
    if (res != SQLITE_OK) {
        sqlite3_close(m_mapDataBase);
        CCLog("failed to open database");
    }
    else
    {
        CCLog("%s loaded", mapSqlite);
    }
    sqlite3_close(m_mapDataBase);
}
