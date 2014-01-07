//
//  RCGameEntry.cpp
//  TilemapDemo
//
//  Created by hy on 1/6/14.
//
//

#include "RCGameEntry.h"
#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"
#include "Lua_extensions_CCB.h"

using namespace std;
USING_NS_CC;

RCGameEntry* RCGameEntry::m_instanceOfGameEntry = NULL;

RCGameEntry* RCGameEntry::sharedGameEntry()
{
    if (!m_instanceOfGameEntry) {
        m_instanceOfGameEntry = new RCGameEntry();
    }
    return m_instanceOfGameEntry;
}

void RCGameEntry::purge()
{
    CC_SAFE_DELETE(m_instanceOfGameEntry);
}

RCGameEntry::RCGameEntry()
{

}

RCGameEntry::~RCGameEntry()
{

}

void RCGameEntry::loadScript(const char* luaScriptPath)
{
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    tolua_extensions_ccb_open(pEngine->getLuaStack()->getLuaState());
    string path = CCFileUtils::sharedFileUtils()->fullPathForFilename(luaScriptPath);
    pEngine->executeScriptFile(path.c_str());
}






