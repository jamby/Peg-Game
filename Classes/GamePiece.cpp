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

GamePiece::GamePiece(GameSpot* pSpot)
{
	SetCurrentSpot(pSpot);
	SetZOrder(pSpot->GetZOrder());
	
	m_gsPreviousSpot = NULL;
	m_bIsPlayable = true;
	m_bIsChosen = false;
	m_pSprite = CCSprite::spriteWithFile("PegBlue.png");
	m_pSprite->setAnchorPoint(ccp(.5, 0));
	
	setPosition(m_gsCurrentSpot->GetPegTip());
	
	// Set the top portion's collision with a point above the position and a radius
	m_ccpTop = ccp(getPosition().x, getPosition().y + 88);
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