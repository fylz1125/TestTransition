//
//  CCTransitonSlider.h
//  TestTransition
//
//  Created by lerry on 13-1-23.
//
//  Copyright (c) 2013年 w_lei@outlook.com. All rights reserved.

#ifndef __TestTransition__CCTransitonSlider__
#define __TestTransition__CCTransitonSlider__

#include "cocos2d.h"
USING_NS_CC;

class  CCTransitionSlider : public CCTransitionScene , public CCTransitionEaseScene {
    
public:
    CCTransitionSlider();
    virtual ~CCTransitionSlider();
    
    /**产生一个动作*/
    virtual CCActionInterval* action(void);
    
    /**实质上的过渡实现*/
    virtual void onEnter();
    
    /**给动作添加变化速率*/
    virtual CCActionInterval * easeActionWithAction(CCActionInterval * action);

public:
    static CCTransitionSlider* create(float t, CCScene *scene);
protected:
    // 设置当前Scene是否在前面
    // true则先绘制当前Scene再绘制载入Scene，false则相反
    // 即true时，第一次不会有过渡动画
    virtual void sceneOrder();
};

// 还是基于网格动画的实现。关于网格动画请看红孩儿大神的博客
class CC_DLL CCSlider : public CCTiledGrid3DAction
{
    public :
    bool init(float duration);
    virtual CCObject* copyWithZone(CCZone* pZone);
    
    /**实质上的网格动画实现*/
    virtual void update(float time);
    
    virtual void startWithTarget(CCNode *pTarget);
    
public:
    
    static CCSlider* create(float duration);
protected:
    int m_nRows;
    CCSize m_winSize;
};

#endif /* defined(__TestTransition__CCTransitonSlider__) */
