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

static GameScene *pGameSceneSingleton = NULL;
static GameLayer *pGameLayerSingleton = NULL;

GameScene* GameScene::GetSceneInstance()
{
    if(pGameSceneSingleton == NULL)
	{
        pGameSceneSingleton = GameScene::node();
		
		// add layer as a child to scene
		pGameSceneSingleton->addChild(GameScene::GetLayerInstance(), 0, 1);
	}
	
    return pGameSceneSingleton;
}

GameLayer* GameScene::GetLayerInstance()
{
	if(pGameLayerSingleton == NULL)
		pGameLayerSingleton = GameLayer::node();
	
	return pGameLayerSingleton;
}

//CCScene* GameScene::scene()
//{
//	// 'scene' is an autorelease object
//	GameScene *scene = GameScene::node();
//	
//	// 'layer' is an autorelease object
//	m_pGameLayerSingleton = GameLayer::node();
//
//	// add layer as a child to scene
//	scene->addChild(layer, 0, 1);
//
//	// return the scene
//	return scene;
//}

// on "init" you need to initialize your instance
bool GameLayer::init()
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

void GameLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void GameLayer::onEnter()
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
//		for(int i = 0; i < 14; i++)
//			m_vGamePieces.push_back(new GamePiece(m_Gameboard->GetSpot(i)));
		//ccDrawCircle(ccp(50, 50), 1.0f, 0.0f, 6, false);
		
		this->addChild(m_Gameboard);
		
		for(int i = 0; i < 6; i++)
			this->addChild(m_Gameboard->GetBoardSprite(i), i*2);
		//this->addChild(m_vGamePieces[0], m_vGamePieces[0]->GetCurrentSpot()->GetZOrder());
		
		m_gpSelectedPiece = NULL;
		m_gsNewSpot = NULL;
		m_nEmptyStartingSpot = -1;
		
		this->schedule(schedule_selector(GameScene::update));
		
		bRet = true;
	} while(0);
}

void GameLayer::onExit()
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

void GameLayer::update(ccTime dt)
{
	for(int i = 0; i < m_vGamePieces.size(); i++)
	{
		m_vGamePieces[i]->update(dt);
	}
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	// Choose one of the touches to work with.
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	for(int i = 0; i < m_vGamePieces.size(); i++)
	{
		if(PointInCircle(location, m_vGamePieces[i]->GetTopPoint(), m_vGamePieces[0]->GetRadius()) == true)
		{
			m_gpSelectedPiece = m_vGamePieces[i];
			this->reorderChild(m_gpSelectedPiece, 11);
			break;
		}
	}
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if(m_gpSelectedPiece != NULL)
	{
//		m_pSelectedPiece->setPosition(ccp(location.x, location.y - 88));
//		
//		for(int i = 0; i < m_pSelectedPiece->GetCurrentSpot()->GetJumpSpots().size(); i++)
//		{
//			if(PointInCircle(m_pSelectedPiece->getPosition(), 
//							 m_pSelectedPiece->GetCurrentSpot()->GetJumpSpots()[i]->GetCirclePoint(), 
//							 m_pSelectedPiece->GetCurrentSpot()->GetJumpSpots()[i]->GetRadius()) == true)
//			{
//				// Need to change this to be from the selected piece's jump spots
//				// However, more of this will have to do with the ending gameplay for this
//				// Like this, the part of code that is commented below
//				// The uncommented code would be the one that should be moved into the TouchesEnded function
////				if(m_pSelectedPiece->GetCurrentSpot()->CheckConnectors(i) == true)
////					m_pNewSpot = m_pSelectedPiece->GetCurrentSpot()->GetJumpSpots()[i];
//				if(m_pSelectedPiece->GetCurrentSpot()->GetZOrder() != m_Gameboard->GetSpot(i)->GetZOrder())
//				{
//					m_pSelectedPiece->SetCurrentSpot(m_Gameboard->GetSpot(i));
//					this->reorderChild(m_pSelectedPiece, m_pSelectedPiece->GetCurrentSpot()->GetZOrder());
//					m_pSelectedPiece->SetZOrder(m_pSelectedPiece->GetCurrentSpot()->GetZOrder());
//				}
//			}
//			else
//				m_pNewSpot = NULL;
//		}
//		
		m_gpSelectedPiece->SetAllPositions(ccp(location.x, location.y - 88));
	}
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touch = (CCTouch*)(pTouches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	if(m_nEmptyStartingSpot == -1)
		StartUpGame(location);
	
	
	if(m_gpSelectedPiece != NULL)
	{
		m_gpSelectedPiece->SetIsChosen(true);
		m_gpSelectedPiece = NULL;
	}
}

void GameLayer::StartUpGame(CCPoint location)
{
	for(int i = 0; i < m_Gameboard->GetSpots().size(); i++)
	{
		if(PointInCircle(location, m_Gameboard->GetSpot(i)->GetCirclePoint(), m_Gameboard->GetSpot(i)->GetRadius()) == true)
		{
			m_nEmptyStartingSpot = i;
			break;
		}
	}
	
	if(m_nEmptyStartingSpot != -1)
	{
		for(int i = 0, j = 0; i < 14; i++, j++)
		{
			if(j == m_nEmptyStartingSpot)
				j++;
			
			m_vGamePieces.push_back(new GamePiece(m_Gameboard->GetSpot(j)));
			m_Gameboard->GetSpot(j)->SetGamePiece(m_vGamePieces[i]);
			
			this->addChild(m_vGamePieces[i], m_vGamePieces[i]->GetCurrentSpot()->GetZOrder());
		}
	}
}