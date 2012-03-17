/*
 *  GameSpot.cpp
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#include "GameSpot.h"

GameSpot::GameSpot(int nSpotIndex)
{
	SetSpotIndex(nSpotIndex);
	m_gpPiece = NULL;
	m_vJumpSpots.clear();
	m_vAdjacentSpots.clear();
	m_nZOrder = -1;
	m_fRadius = 6.0f;
	
	switch(m_nSpotIndex)
	{
		case 1:
			m_ccpCirclePoint = ccp(159, 318);
			m_ccpPegTip = ccp(159, 303);
			break;
		case 2:
			m_ccpCirclePoint = ccp(136, 283);
			m_ccpPegTip = ccp(136, 268);
			break;
		case 3:
			m_ccpCirclePoint = ccp(182, 283);
			m_ccpPegTip = ccp(182, 268);
			break;
		case 4:
			m_ccpCirclePoint = ccp(113, 247);
			m_ccpPegTip = ccp(113, 232);
			break;
		case 5:
			m_ccpCirclePoint = ccp(159, 247);
			m_ccpPegTip = ccp(159, 232);
			break;
		case 6:
			m_ccpCirclePoint = ccp(206, 247);
			m_ccpPegTip = ccp(206, 232);
			break;
		case 7:
			m_ccpCirclePoint = ccp(89, 212);
			m_ccpPegTip = ccp(89, 197);
			break;
		case 8:
			m_ccpCirclePoint = ccp(136, 212);
			m_ccpPegTip = ccp(136, 197);
			break;
		case 9:
			m_ccpCirclePoint = ccp(183, 212);
			m_ccpPegTip = ccp(183, 197);
			break;
		case 10:
			m_ccpCirclePoint = ccp(229, 212);
			m_ccpPegTip = ccp(229, 197);
			break;
		case 11:
			m_ccpCirclePoint = ccp(66, 177);
			m_ccpPegTip = ccp(66, 162);
			break;
		case 12:
			m_ccpCirclePoint = ccp(113, 177);
			m_ccpPegTip = ccp(113, 162);
			break;
		case 13:
			m_ccpCirclePoint = ccp(159, 177);
			m_ccpPegTip = ccp(159, 162);
			break;
		case 14:
			m_ccpCirclePoint = ccp(206, 177);
			m_ccpPegTip = ccp(206, 162);
			break;
		case 15:
			m_ccpCirclePoint = ccp(253, 177);
			m_ccpPegTip = ccp(253, 162);
			break;
		default:
			break;
	}
}

GameSpot::~GameSpot(void)
{
	m_vJumpSpots.clear();
	m_vAdjacentSpots.clear();
}

bool GameSpot::CheckConnectors(int nSubscript)
{
	if(m_vAdjacentSpots[nSubscript]->GetGamePiece() != NULL && m_vJumpSpots[nSubscript]->GetGamePiece() == NULL)
		return true;
	else
		return false;
}

GameSpot* GameSpot::GetSpecificAdjacentSpot(int nSpot)
{
	bool bIsThere = false;
	int i = 0;
	for(; i < m_vAdjacentSpots.size(); i++)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// Will be able to use the GamePlayState's set of CGameSpots, which can use the actual spot number.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if(nSpot == m_vAdjacentSpots[i]->GetSpotIndex())
			bIsThere = true;
		if(bIsThere == true)
			break;
	}
	
	if(bIsThere == true)
		return m_vAdjacentSpots[i];
	else
		return NULL;
	
}

GameSpot* GameSpot::GetSpecificJumpSpot(int nSpot)
{
	bool bIsThere = false;
	int i = 0;
	for(; i < m_vJumpSpots.size(); i++)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// Will be able to use the GamePlayState's set of CGameSpots, which can use the actual spot number.
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		if(nSpot == m_vJumpSpots[i]->GetSpotIndex())
			bIsThere = true;
		if(bIsThere	= true)
			break;
	}
	
	if(bIsThere == true)
		return m_vJumpSpots[i];
	else
		return NULL;
	
}