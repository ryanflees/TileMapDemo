
-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    -- run
    
    local cclog = function(...)
        print(string.format(...))
    end

     
    require "CCBReaderLoad"

    MainMenu = MainMenu or {}
    ccb["MainMenu"] = MainMenu

    local function CreateMainMenuLayer()
       local proxy = CCBProxy:create()
       local node = CCBReaderLoad("ccbi/main_menu.ccbi", proxy, true, "MainMenu"); 
        local  layer = tolua.cast(node,"CCLayer")  
        return layer  
    end

    function runCocosBuilder()  
        cclog("HelloCCBSceneTestMain")  
        local scene = CCScene:create()  
        scene:addChild(CreateMainMenuLayer())  
        return scene  
    end  

    local scene  = runCocosBuilder()  
    CCDirector:sharedDirector():runWithScene(scene)
end

xpcall(main, __G__TRACKBACK__)
