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
	
	switch(m_nSpotIndex)
	{
		case 1:
			m_ccpCirclePoint = ccp(159, 318);
			m_ccpPegTip = ccp(159, 308);
			break;
		case 2:
			m_ccpCirclePoint = ccp(136, 283);
			m_ccpPegTip = ccp(136, 273);
			break;
		case 3:
			m_ccpCirclePoint = ccp(182, 283);
			m_ccpPegTip = ccp(182, 273);
			break;
		case 4:
			m_ccpCirclePoint = ccp(113, 247);
			m_ccpPegTip = ccp(113, 237);
			break;
		case 5:
			m_ccpCirclePoint = ccp(159, 247);
			m_ccpPegTip = ccp(159, 237);
			break;
		case 6:
			m_ccpCirclePoint = ccp(206, 247);
			m_ccpPegTip = ccp(206, 237);
			break;
		case 7:
			m_ccpCirclePoint = ccp(89, 212);
			m_ccpPegTip = ccp(89, 202);
			break;
		case 8:
			m_ccpCirclePoint = ccp(136, 212);
			m_ccpPegTip = ccp(136, 202);
			break;
		case 9:
			m_ccpCirclePoint = ccp(183, 212);
			m_ccpPegTip = ccp(183, 202);
			break;
		case 10:
			m_ccpCirclePoint = ccp(229, 212);
			m_ccpPegTip = ccp(229, 212);
			break;
		case 11:
			m_ccpCirclePoint = ccp(66, 177);
			m_ccpPegTip = ccp(66, 167);
			break;
		case 12:
			m_ccpCirclePoint = ccp(113, 177);
			m_ccpPegTip = ccp(113, 167);
			break;
		case 13:
			m_ccpCirclePoint = ccp(159, 177);
			m_ccpPegTip = ccp(159, 167);
			break;
		case 14:
			m_ccpCirclePoint = ccp(206, 177);
			m_ccpPegTip = ccp(206, 167);
			break;
		case 15:
			m_ccpCirclePoint = ccp(253, 177);
			m_ccpPegTip = ccp(253, 167);
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

int GameSpot::CheckConnectors(int nSubscript)
{
	if(m_vAdjacentSpots[nSubscript] == NULL && m_vJumpSpots[nSubscript] == NULL)
		return eBOTH_SPOTS_EMPTY;
	else if(m_vAdjacentSpots[nSubscript] && m_vJumpSpots[nSubscript] == NULL)
		return eADJACENT_SPOT_TAKEN;
	else if(m_vJumpSpots[nSubscript] && m_vAdjacentSpots[nSubscript] == NULL)
		return eJUMP_SPOT_TAKEN;
	else
		return eBOTH_SPOTS_TAKEN;
}

vector<int> GameSpot::GetAdjacentSpots(void)
{
	vector<int> vTemporaryAdjacentSpots;
	for(int i = 0; i < m_vAdjacentSpots.size(); i++)
	{
		vTemporaryAdjacentSpots.push_back(m_vAdjacentSpots[i]->GetSpotIndex());
	}
	
	return vTemporaryAdjacentSpots;
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

vector<int> GameSpot::GetJumpSpots(void)
{
	vector<int> vTemporaryJumpSpots;
	for(int i = 0; i < m_vJumpSpots.size(); i++)
	{
		vTemporaryJumpSpots.push_back(m_vJumpSpots[i]->GetSpotIndex());
	}
	
	return vTemporaryJumpSpots;
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