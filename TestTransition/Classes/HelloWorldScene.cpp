#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "CCTransitonSlider.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCTransitionScene* createTransition(float t, CCScene *scene)
{
//    return CCTransitionSplitRows::create(t, scene);
    return CCTransitionSlider::create(t, scene);
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pCloseItem->setPosition( ccp(winSize.width - 20, 20) );

    
    CCSprite *sprite = CCSprite::create("background1.png");
    sprite->setPosition(ccp(winSize.width / 2, winSize.height /2 ));
    addChild(sprite, -1);


    CCMenuItemImage *item = CCMenuItemImage::create("f1.png", "f2.png", this, menu_selector(HelloWorld::nextCallback) );
    
    CCMenu *menu = CCMenu::create(pCloseItem, item, NULL);
    
    menu->setPosition( CCPointZero );
    item->setPosition(ccp(winSize.width - pCloseItem->getContentSize().width - item->getContentSize().width/2,20));
    
    addChild(menu, 1);
    return true;
}

void HelloWorld::nextCallback(cocos2d::CCObject *pSender)
{
    CCScene *scene = TestLayer1::scene();
    CCDirector::sharedDirector()->replaceScene(createTransition(1.2,scene));

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

CCScene* TestLayer1::scene()
{
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TestLayer1 *layer = TestLayer1::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TestLayer1::init()
{
    if (!CCLayer::init()) {
        return false;
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *sprite = CCSprite::create("background2.png");
    sprite->setPosition(ccp(winSize.width / 2, winSize.height /2 ));
    addChild(sprite, -1);
    
    
    CCMenuItemImage *item = CCMenuItemImage::create("f1.png", "f2.png", this, menu_selector(TestLayer1::nextCallback) );
    CCMenu *menu = CCMenu::create(item, NULL);
    menu->setPosition( CCPointZero );
    item->setPosition(ccp(winSize.width-item->getContentSize().width, 20));
    addChild(menu, 1);
    
    return true;
}

void TestLayer1::nextCallback(cocos2d::CCObject *pSender)
{
    CCScene *scene = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(createTransition(1.2,scene));
}

