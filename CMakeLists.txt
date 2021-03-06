cmake_minimum_required(VERSION 3.6)

set(APP_NAME BaDog)

project(${APP_NAME})

set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

include(CocosBuildSet)
add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/Resources")
if (APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif ()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE Classes/AppDelegate.cpp)
list(APPEND GAME_HEADER Classes/AppDelegate.h)
file(GLOB_RECURSE Classes/MoriorGames "*.h" "*.cpp")

if (ANDROID)
    # change APP_NAME to the share library name for Android, it's value depend on AndroidManifest.xml
    set(APP_NAME MyGame)
    list(APPEND GAME_SOURCE
            proj.android/app/jni/hellocpp/main.cpp
            )
elseif (APPLE)
    if (IOS)
        list(APPEND GAME_HEADER
                proj.ios_mac/ios/AppController.h
                proj.ios_mac/ios/RootViewController.h
                )
        set(APP_UI_RES
                proj.ios_mac/ios/LaunchScreen.storyboard
                proj.ios_mac/ios/LaunchScreenBackground.png
                proj.ios_mac/ios/Images.xcassets
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/ios/main.m
                proj.ios_mac/ios/AppController.mm
                proj.ios_mac/ios/RootViewController.mm
                proj.ios_mac/ios/Prefix.pch
                ${APP_UI_RES}
                )
    elseif (MACOSX)
        set(APP_UI_RES
                proj.ios_mac/mac/Icon.icns
                proj.ios_mac/mac/Info.plist
                )
        list(APPEND GAME_SOURCE
                proj.ios_mac/mac/main.cpp
                proj.ios_mac/mac/Prefix.pch
                ${APP_UI_RES}
                )
    endif ()
    list(APPEND GAME_SOURCE ${common_res_files})
endif ()

# mark app complie info and libs info
set(all_code_files ${GAME_HEADER} ${GAME_SOURCE} ${Classes/MoriorGames})
if (NOT ANDROID)
    add_executable(${APP_NAME} ${all_code_files})
else ()
    add_library(${APP_NAME} SHARED ${all_code_files})
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos/platform/android ${ENGINE_BINARY_PATH}/cocos/platform)
    target_link_libraries(${APP_NAME} -Wl,--whole-archive cpp_android_spec -Wl,--no-whole-archive)
endif ()

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        )

# mark app resources
setup_cocos_app_config(${APP_NAME})
if (APPLE)
    set_target_properties(${APP_NAME} PROPERTIES RESOURCE "${APP_UI_RES}")
    if (MACOSX)
        set_target_properties(${APP_NAME} PROPERTIES
                MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/proj.ios_mac/mac/Info.plist"
                )
    elseif (IOS)
        cocos_pak_xcode(${APP_NAME} INFO_PLIST "iOSBundleInfo.plist.in")
        set_xcode_property(${APP_NAME} ASSETCATALOG_COMPILER_APPICON_NAME "AppIcon")
    endif ()
endif ()
