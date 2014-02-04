//
//  RCDataNode.h
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-30.
//
//

#ifndef __MiniRPG__RCDataNode__
#define __MiniRPG__RCDataNode__

#include "cocos2d.h"
struct RCMessageStruct;

USING_NS_CC;

class RCDataNode :public CCObject
{
public:
    RCDataNode();
    virtual ~RCDataNode();
    virtual bool init();
    CREATE_FUNC(RCDataNode);
private:
    CC_SYNTHESIZE_READONLY(RCMessageStruct*, m_messageStruct, MessageStruct);
    CC_SYNTHESIZE(int, m_dataLength, DataLength);
};

#endif /* defined(__MiniRPG__RCDataNode__) */
