//
//  RCControllerLayer.h
//  TilemapDemo
//
//  Created by Bai Ryan on 13-12-30.
//
//

#ifndef __TilemapDemo__RCControllerLayer__
#define __TilemapDemo__RCControllerLayer__

#include <iostream>
#include "cocos2d.h"

class RCDPad;

class RCControllerLayer : public cocos2d::CCLayer {
public:
    virtual bool init();
    CREATE_FUNC(RCControllerLayer);
    
private:
    RCDPad *m_dPad;
};

#endif /* defined(__TilemapDemo__RCControllerLayer__) */
