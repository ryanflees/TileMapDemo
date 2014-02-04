//
//  RCDataNode.cpp
//  MiniRPG
//
//  Created by Bai Ryan on 14-1-30.
//
//

#include "RCDataNode.h"
#include "RCMessageCenter.h"

RCDataNode::RCDataNode()
{
}

RCDataNode::~RCDataNode()
{
    delete (m_messageStruct);
}

bool RCDataNode::init()
{
    m_messageStruct = new RCMessageStruct();
    return true;
}
