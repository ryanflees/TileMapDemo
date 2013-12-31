//
//  RCUILayer.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCUILayer__
#define __TilemapDemo__RCUILayer__

#include <iostream>
#include "cocos2d.h"

class RCUILayer : public cocos2d::CCLayer{
public:
    virtual bool init();
    CREATE_FUNC(RCUILayer);
};

#endif /* defined(__TilemapDemo__RCUILayer__) */
