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
		CCLayer::onEnter();
		
		m_pRefresh = CCMenuItemImage::itemFromNormalImage("refresh.png", "refreshchosen.png", this, menu_selector(GameLayer::SetSafeRestart));
		m_pRefresh->setPosition(ccp(158, 32));
		
		m_pMenu = CCMenu::menuWithItem(m_pRefresh);
		m_pMenu->setPosition(CCPointZero);
		this->addChild(m_pMenu, 1);
		
		// ask director the window size
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		m_Gameboard = new Gameboard();
		
		this->addChild(m_Gameboard);
		
		for(int i = 0; i < 6; i++)
			this->addChild(m_Gameboard->GetBoardSprite(i), i*2);
		
		m_gpSelectedPiece = NULL;
		m_gsNewSpot = NULL;
		m_nEmptyStartingSpot = -1;
		m_nRemovingPiece = -1;
		
		m_bRemovingPiece = false;
		m_fOpacityPer = 0.0f;
		m_fOpacityLerp = 0.0f;
		m_fYPer = 0.0f;
		m_fYLerp = 0.0f;
		
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
	
	if(m_nRemovingPiece > -1)
	{
		if(m_bRemovingPiece == true)
		{
			if(dt >= .016f)
			{
				m_fYPer += .1f;
				m_fYLerp = Lerp(m_vGamePieces[m_nRemovingPiece]->GetLowPosLerp().y, 
								m_vGamePieces[m_nRemovingPiece]->GetHighPosLerp().y, m_fYPer);
				m_vGamePieces[m_nRemovingPiece]->setPosition(ccp(m_vGamePieces[m_nRemovingPiece]->getPosition().x,
																 m_fYLerp));
				m_fOpacityPer += .1f;
				m_fOpacityLerp = Lerp(255, 0, m_fOpacityPer);
				m_vGamePieces[m_nRemovingPiece]->GetSprite()->setOpacity(m_fOpacityLerp);
				if(m_fYPer >= 1.0f)
				{
					m_fYPer = 0.0f;
					m_bRemovingPiece = false;
				}
			}
		}
		else
		{
			// Must make sure it's not visible, has no spot, and is in a new position
			m_vGamePieces[m_nRemovingPiece]->setIsVisible(false);
			m_vGamePieces[m_nRemovingPiece]->GetSprite()->setOpacity(255);
			m_vGamePieces[m_nRemovingPiece]->SetPreviousSpot(m_vGamePieces[m_nRemovingPiece]->GetCurrentSpot());
			m_vGamePieces[m_nRemovingPiece]->GetPreviousSpot()->SetGamePiece(NULL);
			m_vGamePieces[m_nRemovingPiece]->GetCurrentSpot()->SetGamePiece(NULL);
			m_vGamePieces[m_nRemovingPiece]->SetCurrentSpot(NULL);
			m_vGamePieces[m_nRemovingPiece]->SetAllPositions(ccp(-200, -200));
			// Add it to the UsedPieces
			m_vUsedPieces.push_back(m_vGamePieces[m_nRemovingPiece]);
			// Remove it from the GamePieces
			m_vGamePieces.erase(m_vGamePieces.begin()+m_nRemovingPiece);
			
			m_nRemovingPiece = -1;
		}
	}
	
	if(m_bSafeToRestart == true)
	{
		RestartGame();
		m_bSafeToRestart = false;
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
		if(PointInCircle(location, m_vGamePieces[i]->GetTopPoint(), m_vGamePieces[i]->GetRadius()) == true)
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

void GameLayer::RestartGame(void)
{
	for(int i = 0; i < m_Gameboard->GetSpots().size(); i++)
	{
		m_Gameboard->GetSpots()[i]->SetGamePiece(NULL);
	}
	
	for(int i = 0; i < m_vGamePieces.size(); i++)
	{
		m_vGamePieces[i]->SetCurrentSpot(NULL);
		m_vGamePieces[i]->SetPreviousSpot(NULL);
	}
	
	for(int i = 0; i < m_vUsedPieces.size(); i++)
	{
		m_vUsedPieces[i]->SetCurrentSpot(NULL);
		m_vUsedPieces[i]->SetPreviousSpot(NULL);
	}
	
	for(int i = m_vGamePieces.size()-1; i >= 0; i--)
	{
		this->removeChild(m_vGamePieces.back(), true);
		GamePiece* pTempPiece = m_vGamePieces.back();
		m_vGamePieces.pop_back();
		delete pTempPiece;
	}
	
	for(int i = m_vUsedPieces.size()-1; i >= 0; i--)
	{
		this->removeChild(m_vUsedPieces.back(), true);
		GamePiece* pTempPiece = m_vUsedPieces.back();
		m_vUsedPieces.pop_back();
		delete pTempPiece;
	}
	
	m_nEmptyStartingSpot = -1;
}