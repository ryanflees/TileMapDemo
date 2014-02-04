//
//  RCMessageCenter.h
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-25.
//
//

#ifndef __MiniRPG__RCMessageCenter__
#define __MiniRPG__RCMessageCenter__

#include "cocos2d.h"
#include "netmsg.pb.h"

#define RCSocketMessageSendBufferLength 1024

#define SEND_MESSAGE(code, message) RCMessageCenter::sharedMessageCenter()->sendMessage(code, message)

using namespace std;
USING_NS_CC;

struct RCMessageStruct
{
    int messageCode;
    char data[RCSocketMessageSendBufferLength];
};

class RCMessageObserver
{
public:
    virtual void onReceiveMessage(int messageCode, void *data, int length) = 0;
    void registerMessageCode(int messageCode);
    void unregisterMessageCode();
private:
    CC_SYNTHESIZE_READONLY(int, m_messageCode, MessageCode);
};

class RCMessageCenter :public CCNode
{
public:
    static RCMessageCenter* sharedMessageCenter();
    static RCMessageCenter* m_instanceOfMessageCenter;
    static void purge();
    RCMessageCenter();
    virtual ~RCMessageCenter();
    virtual bool init();
    CREATE_FUNC(RCMessageCenter);
    
    void addObserver(int messageCode, RCMessageObserver* observer);
    void removeObserver(RCMessageObserver* observer);
    
    void sendMessage(int messageCode, ::google::protobuf::Message* message);
    void onReceiveMessage(void* data, int len);
    
    vector<RCMessageObserver*> m_observers;
private:
    void sendData(void* data, int length);
};

#endif /* defined(__MiniRPG__RCMessageCenter__) */
