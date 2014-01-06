//
//  RCGameEntry.h
//  TilemapDemo
//
//  Created by hy on 1/6/14.
//
//

#ifndef __TilemapDemo__RCGameEntry__
#define __TilemapDemo__RCGameEntry__

#include <iostream>
#include "cocos2d.h"

class RCGameEntry
{
public:
    static RCGameEntry *sharedGameEntry();
    static void purge();
    static RCGameEntry *m_instanceOfGameEntry;
    RCGameEntry();
    ~RCGameEntry();
    
    void loadScript(const char* luaScriptPath);
};


#endif /* defined(__TilemapDemo__RCGameEntry__) */
