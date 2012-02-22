//
//  GameScene.cpp
//  Peg Game
//
//  Created by Jared Hamby on 8/28/11.
//  Copyright Fruit-Punched Games, LLC 2011. All rights reserved.
//

#include "GameScene.h"
#include "FPGMath.h"

USING_NS_CC;

CCScene* m_pGameSceneSingleton = NULL;

CCScene* GameScene::GetInstance()
{
    if(m_pGameSceneSingleton == NULL)
        m_pGameSceneSingleton = GameScene::scene();
	
    return m_pGameSceneSingleton;
}

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	GameScene *layer = GameScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 255, 255)))
		return false;
	
	
	bool bRet = false;
	do
	{
		//////////////////////////////
		// 1. super init first
		CC_BREAK_IF(!CCLayer::init());
		
		this->setIsTouchEnabled(true);

		bRet = true;
	} while(0);
	
	return bRet;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void GameScene::onEnter()
{
	bool bRet = false;
	do
	{
		//////////////////////////////
		// 1. super init first
		//CC_BREAK_IF(!CCLayer::init());
		
		CCLayer::onEnter();
		
		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.
		
		// add a "close" icon to exit the progress. it's an autorelease object
		//CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
		//										"CloseNormal.png",
		//										"CloseSelected.png",
		//										this,
		//										menu_selector(HelloWorld::menuCloseCallback) );
		//	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
		
		// create menu, it's an autorelease object
		//CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
		//pMenu->setPosition( CCPointZero );
		//this->addChild(pMenu, 1);
		
		// ask director the window size
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		m_Gameboard = new Gameboard();
		for(int i = 0; i < 14; i++)
			m_vGamePieces.push_back(new GamePiece(m_Gameboard->GetSpot(i)));
		//ccDrawCircle(ccp(50, 50), 1.0f, 0.0f, 6, false);
		
		this->addChild(m_Gameboard);
		
		for(int i = 0; i < 6; i++)
			this->addChild(m_Gameboard->GetBoardSprite(i), i*2);
		this->addChild(m_vGamePieces[0], m_vGamePieces[0]->GetCurrentSpot()->GetZOrder());
		
		m_pSelectedPiece = NULL;
		
		this->schedule(schedule_selector(GameScene::update));
		
		bRet = true;
	} while(0);
}

void GameScene::onExit()
{
	this->removeAllChildrenWithCleanup(true);
	
	for(int i = 0; i < 10; i++)
	{
		GamePiece* tempPiece = m_vGamePieces.back();
		m_vGamePieces.pop_back();
		delete tempPiece;
	}
	
	m_vGamePieces.clear();
	
	delete m_Gameboard;
	
	CCLayer::onExit();
}

void GameScene::update(ccTime dt)
{
	
}

void GameScene::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	// Choose one of the touches to work with.
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
//	for(int i = 0; i < m_vGamePieces.size(); i++)
//	{
//		
//	}
	if(PointInCircle(location, m_vGamePieces[0]->GetTopPoint(), m_vGamePieces[0]->GetRadius()) == true)
		m_pSelectedPiece = m_vGamePieces[0];
}

void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if(m_pSelectedPiece != NULL)
	{
		m_pSelectedPiece->setPosition(ccp(location.x, location.y - 88));
	
		this->reorderChild(m_pSelectedPiece, 11);
	}
}

void GameScene::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if(m_pSelectedPiece != NULL)
	{
		m_pSelectedPiece->setPosition(ccp(location.x, location.y - 88));
		
		for(int i = 0; i < 15; i++)
		{
			if(PointInCircle(m_pSelectedPiece->getPosition(), m_Gameboard->GetSpot(i)->GetCirclePoint(), m_Gameboard->GetSpot(i)->GetRadius()) == true)
			{
				if(m_pSelectedPiece->GetCurrentSpot()->GetZOrder() != m_Gameboard->GetSpot(i)->GetZOrder())
				{
					m_pSelectedPiece->SetCurrentSpot(m_Gameboard->GetSpot(i));
					this->reorderChild(m_pSelectedPiece, m_pSelectedPiece->GetCurrentSpot()->GetZOrder());
					m_pSelectedPiece->SetZOrder(m_pSelectedPiece->GetCurrentSpot()->GetZOrder());
				}
			}		
		}
		
		m_pSelectedPiece->SetTopPoint(ccp(m_pSelectedPiece->getPosition().x, m_pSelectedPiece->getPosition().y + 88));
	}
	
	m_pSelectedPiece = NULL;
}