/*
 *  GamePiece.cpp
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#include "GamePiece.h"
#include "GameScene.h"
#include "FPGMath.h"

GamePiece::GamePiece(GameSpot* pSpot)
{
	SetCurrentSpot(pSpot);
	SetZOrder(pSpot->GetZOrder());
	
	m_gsPreviousSpot = NULL;
	m_bIsPlayable = true;
	m_bIsChosen = false;
	m_pSprite = CCSprite::spriteWithFile("PegBlue.png");
	m_pSprite->setAnchorPoint(ccp(.5, 0));
	
	//Sets all position data, the actual position of the object and the position of the top area
	SetAllPositions(m_gsCurrentSpot->GetPegTip());
	m_fRadius = 15.0f;
	
	this->addChild(m_pSprite);
	m_pGameLayer = GameScene::GetLayerInstance();
}

GamePiece::~GamePiece(void)
{
}

bool GamePiece::CanJump(void)
{
	
	return false;
}

void GamePiece::JumpToSpot(int nSpot)
{
	int nCurrentSpotIndex = m_gsCurrentSpot->GetSpotIndex();
//	vector<int> vJumpSpots = m_gsCurrentSpot->GetJumpSpots();
//	int i = 0;
//	for(; i < vJumpSpots.size(); i++)
//	{
//		//if(nSpot == vJumpSpots[i]->GetSpotIndex())
//		//{
//		//m_gsCurrentSpot = vGameSpots[nSpot];
//		//}
//	}
	
	if(nCurrentSpotIndex == m_gsCurrentSpot->GetSpotIndex())
		m_gsCurrentSpot = NULL;
}

void GamePiece::SetAllPositions(CCPoint ccpPosition)
{
	setPosition(ccpPosition);
	m_ccpTop = ccp(getPosition().x, getPosition().y + 88);
	m_ccpLowPosLerp = ccpPosition;
	m_ccpHighPosLerp = ccpPosition;
	m_ccpHighPosLerp.y += 50;
}

void GamePiece::update(ccTime dt)
{
	if(m_bIsChosen == true)
	{
		bool bAllSpotsDone = false;
		for(int i = 0; i < m_gsCurrentSpot->GetJumpSpots().size(); i++)
		{
			// Check to see if the Peg's in a new spot's circle
			if(PointInCircle(getPosition(), m_gsCurrentSpot->GetJumpSpots()[i]->GetCirclePoint(), 
							 m_gsCurrentSpot->GetJumpSpots()[i]->GetRadius()) == true)
			{
				// If it's true, check the specific connector to see if it has a peg in the Adjacent Spot, but not the Jump Spot
				if(m_gsCurrentSpot->CheckConnectors(i) == true)
				{
					// If that spot comes back as true, search through the Game Layer's pieces to get rid of
					// that specific Peg from the GamePieces and add it to the UsedPieces
					for(int j = 0; j < m_pGameLayer->GetGamePieces().size(); j++)
					{
						if(m_pGameLayer->GetGamePieces()[j] == m_gsCurrentSpot->GetAdjacentSpots()[i]->GetGamePiece())
						{
							m_pGameLayer->SetRemovingPiece(j);
							m_pGameLayer->SetBoolRemovingPiece(true);
							break;
						}
					}
					// PreviousSpot needs to not be the GamePiece's CurrentSpot
					SetPreviousSpot(m_gsCurrentSpot);
					m_gsPreviousSpot->SetGamePiece(NULL);
					SetCurrentSpot(m_gsCurrentSpot->GetJumpSpots()[i]);
					m_gsCurrentSpot->SetGamePiece(this);
					// Set all the positions and reorder the child
					SetAllPositions(m_gsCurrentSpot->GetPegTip());
					m_pGameLayer->reorderChild(this, m_gsCurrentSpot->GetZOrder());
					break;
				}
			}

			if(i == m_gsCurrentSpot->GetJumpSpots().size()-1)
				bAllSpotsDone = true;
		}
		
		if(bAllSpotsDone == true)
		{
			SetAllPositions(m_gsCurrentSpot->GetPegTip());
			m_pGameLayer->reorderChild(this, m_gsCurrentSpot->GetZOrder());
		}
			
		m_bIsChosen = false;
	}
}