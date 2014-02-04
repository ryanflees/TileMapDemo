//
//  RCMessageCenter.cpp
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-25.
//
//

#include "RCMessageCenter.h"
#include "RCDataCenter.h"

void RCMessageObserver::registerMessageCode(int messageCode)
{
    messageCode >>= 8;
    messageCode <<= 8;
    m_messageCode = messageCode;
    RCMessageCenter::sharedMessageCenter()->addObserver(messageCode, this);
}

void RCMessageObserver::unregisterMessageCode()
{
    RCMessageCenter::sharedMessageCenter()->removeObserver(this);
}

RCMessageCenter* RCMessageCenter::sharedMessageCenter()
{
    if (!m_instanceOfMessageCenter) {
        m_instanceOfMessageCenter = RCMessageCenter::create();
        m_instanceOfMessageCenter->retain();
    }
    return m_instanceOfMessageCenter;
}

void RCMessageCenter::purge()
{
    CC_SAFE_RELEASE(m_instanceOfMessageCenter);
    m_instanceOfMessageCenter = NULL;
}

RCMessageCenter* RCMessageCenter::m_instanceOfMessageCenter = NULL;

RCMessageCenter::RCMessageCenter()
{

}

RCMessageCenter::~RCMessageCenter()
{
}

bool RCMessageCenter::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    return true;
}

void RCMessageCenter::addObserver(int messageCode, RCMessageObserver* observer)
{
    bool isDublicated = false;
    for (vector<RCMessageObserver*>::iterator iter = m_observers.begin();
         iter != m_observers.end(); ++iter) {
        if (*iter == observer) {
            isDublicated = true;
            break;
        }
    }
    if (isDublicated) {
        return;
    }
    m_observers.push_back(observer);
}

void RCMessageCenter::removeObserver(RCMessageObserver* observer)
{
    for (vector<RCMessageObserver*>::iterator iter = m_observers.begin();
         iter != m_observers.end(); ++iter) {
        if (*iter == observer) {
            m_observers.erase(iter);
            break;
        }
    }
}

void RCMessageCenter::sendMessage(int messageCode, ::google::protobuf::Message* message)
{
    RCMessageStruct messageStruct;
    messageStruct.messageCode = messageCode;
    message->SerializeToArray(messageStruct.data, RCSocketMessageSendBufferLength);
    int size = sizeof(messageStruct.data) +  message->ByteSize();
    RCDataCenter::sharedDataCenter()->handleMessage(&messageStruct, size);
}

void RCMessageCenter::sendData(void* data, int length)
{
    RCDataCenter::sharedDataCenter()->handleMessage(data, length);
}

void RCMessageCenter::onReceiveMessage(void *data, int len)
{
    RCMessageStruct* messageStruct = (RCMessageStruct*)data;
    int messageCode = messageStruct->messageCode;
    messageCode >>= 8;
    messageCode <<= 8;
    for (vector<RCMessageObserver*>::iterator iter = m_observers.begin();
         iter != m_observers.end(); ++iter) {
        if ((*iter)->getMessageCode() == messageCode)
        {
            (*iter)->onReceiveMessage(messageStruct->messageCode, messageStruct->data, len-sizeof(messageStruct->messageCode));
        }
    }
}
