/*
 *  GamePiece.cpp
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#include "GamePiece.h"

GamePiece::GamePiece(GameSpot* pSpot)
{
	SetCurrentSpot(pSpot);
	m_gsPreviousSpot = NULL;
	m_bIsPlayable = true;
	m_bIsChosen = false;
	m_pSprite = CCSprite::spriteWithFile("PegBlue.png");
	m_pSprite->setAnchorPoint(ccp(.5, 0));
	
	m_pSprite->setPosition(m_gsCurrentSpot->GetPegTip());
	this->addChild(m_pSprite);
//	switch(m_gsCurrentSpot->GetSpotIndex())
//	{
//		case 1:
//			m_pSprite->setPosition(ccp(160, 300));
//			break;
//		case 2:
//			break;
//		case 3:
//			break;
//		case 4:
//			break;
//		case 5:
//			break;
//		case 6:
//			break;
//		case 7:
//			break;
//		case 8:
//			break;
//		case 9:
//			break;
//		case 10:
//			break;
//		case 11:
//			break;
//		case 12:
//			break;
//		case 13:
//			break;
//		case 14:
//			break;
//		case 15:
//			break;
//		default:
//			break;
//	}
	
	//this->addChild(m_pSprite, m_gsCurrentSpot->GetZOrder());
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
	vector<int> vJumpSpots = m_gsCurrentSpot->GetJumpSpots();
	int i = 0;
	for(; i < vJumpSpots.size(); i++)
	{
		//if(nSpot == vJumpSpots[i]->GetSpotIndex())
		//{
		//m_gsCurrentSpot = vGameSpots[nSpot];
		//}
	}
	
	if(nCurrentSpotIndex == m_gsCurrentSpot->GetSpotIndex())
		m_gsCurrentSpot = NULL;
}