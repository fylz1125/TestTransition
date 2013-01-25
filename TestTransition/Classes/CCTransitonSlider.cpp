//
//  CCTransitonSlider.cpp
//  TestTransition
//
//  Created by lerry on 13-1-23.
//
//  Copyright (c) 2013年 w_lei@outlook.com. All rights reserved.

#include "CCTransitonSlider.h"

CCTransitionSlider::CCTransitionSlider()
{
}

CCTransitionSlider::~CCTransitionSlider()
{
}



CCTransitionSlider* CCTransitionSlider::create(float t, CCScene* scene)
{
    CCTransitionSlider* pScene = new CCTransitionSlider();
    if(pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}


void CCTransitionSlider::onEnter()
{
    CCTransitionScene::onEnter();    
    CCActionInterval* slider = action();
    m_pOutScene->runAction
    (
     CCSequence::create
     (
      easeActionWithAction(slider),
      CCCallFunc::create(this, callfunc_selector(CCTransitionScene::finish)),
      CCStopGrid::create(),
      NULL
      )
     );
    
}

CCActionInterval* CCTransitionSlider:: action()
{
    return CCSlider::create(m_fDuration/2.0f);
}


CCActionInterval* CCTransitionSlider::easeActionWithAction(CCActionInterval * action)
{

    // 动画由慢到快
    return CCEaseIn::create(action, 3.5f);
}

// CCSlider
CCSlider* CCSlider::create(float duration)
{
    CCSlider *pAction = new CCSlider();
    
    if (pAction)
    {
        if (pAction->init(duration))
        {
            pAction->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pAction);
        }
    }
    
    return pAction;
}

void CCTransitionSlider::sceneOrder()
{
    m_bIsInSceneOnTop = false;

}

bool CCSlider::init(float duration)
{
    m_nRows = 1;
    
    return CCTiledGrid3DAction::initWithSize(ccg(2, 1), duration);
}

CCObject* CCSlider::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCSlider* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        pCopy = (CCSlider*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCSlider();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCTiledGrid3DAction::copyWithZone(pZone);
    
    pCopy->init(m_fDuration);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCSlider::startWithTarget(CCNode *pTarget)
{
    CCTiledGrid3DAction::startWithTarget(pTarget);
    m_winSize = CCDirector::sharedDirector()->getWinSizeInPixels();
}

void CCSlider::update(float time)
{
    int j;
    // 水平方向有两格
    for (j = 0; j < m_sGridSize.x; ++j)
    {
        ccQuad3 coords = originalTile(ccg(0, j));
        // 控制方向反转
        float    direction = 1;
        
        if ( (j % 2 ) == 0 )
        {
            direction = -1;
        }
        // 格子四个顶点数据赋值
        coords.bl.x += direction * m_winSize.width * time;
        coords.br.x += direction * m_winSize.width * time;
        coords.tl.x += direction * m_winSize.width * time;
        coords.tr.x += direction * m_winSize.width * time;
        
        // 重新设置格子数据
        setTile(ccg(0, j), coords);
    }
}


