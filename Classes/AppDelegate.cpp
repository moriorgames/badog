#include "AppDelegate.h"
#include "MoriorGames/Scenes/GameScene.h"
#include "MoriorGames/Screen/Resolution.h"
#include "MoriorGames/Definitions.h"

#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;

Resolution *globalResolution = new Resolution;

USING_NS_CC;

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};
    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
    Resolution resolution;

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::createWithRect("BaDog", resolution.getDesktopRect());
        director->setOpenGLView(glview);
    }

    //Prevent entering sleep mode
    cocos2d::Device::setKeepScreenOn(true);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    auto screenSize = glview->getFrameSize();
    Resolution::DesignProperties designProperties = resolution.designPropertiesByScreen(screenSize)
        ->getDesignProperties();
    glview->setDesignResolutionSize(designProperties.width, designProperties.height, ResolutionPolicy::FIXED_WIDTH);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}
