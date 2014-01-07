//
//  RCMainMenu.cpp
//  TilemapDemo
//
//  Created by Bai Ryan on 14-1-7.
//
//

#include "RCMainMenu.h"
#include "CCNodeLoaderLibrary.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool RCMainMenu::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    
    CCNodeLoaderLibrary *loaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    CCBReader *ccbReader = new CCBReader(loaderLibrary);
    CCNode *node = ccbReader->readNodeGraphFromFile("ccbi/main_menu.ccbi");
    addChild(node);

    
    return true;

}



