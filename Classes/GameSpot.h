/*
 *  GameSpot.h
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#ifndef __GAMESPOT_H_
#define __GAMESPOT_H_

#include "cocos2d.h"
using namespace cocos2d;

class GamePiece;

enum eSPOTRETURNS
{
	eBOTH_SPOTS_TAKEN = 0,
	eBOTH_SPOTS_EMPTY,
	eADJACENT_SPOT_TAKEN,
	eJUMP_SPOT_TAKEN
};

class GameSpot : public CCNode
{
private:
	GamePiece* m_gpPiece;
	int m_nSpotIndex;
	int m_nZOrder;
	vector<GameSpot*> m_vJumpSpots;
	vector<GameSpot*> m_vAdjacentSpots;
	
	CCPoint m_ccpPegTip;
	CCPoint m_ccpCirclePoint;
	
	void SetSpotIndex(int nSpotIndex) { m_nSpotIndex = nSpotIndex; }
	
public:
	GameSpot(int nSpotIndex);
	~GameSpot(void);
	
	void AddJumpSpot(GameSpot* gsJumpSpot) { m_vJumpSpots.push_back(gsJumpSpot); }
	void AddAdjacentSpot(GameSpot* gsAdjacentSpot) { m_vAdjacentSpots.push_back(gsAdjacentSpot); }
	void SetZOrder(int nNum) { m_nZOrder = nNum; }
	int GetZOrder(void) { return m_nZOrder; }
	
	int GetSpotIndex(void) { return m_nSpotIndex; }
	int CheckConnectors(int nSubscript);
	vector<int> GetAdjacentSpots(void);
	GameSpot* GetSpecificAdjacentSpot(int nSpot);
	vector<int> GetJumpSpots(void);
	GameSpot* GetSpecificJumpSpot(int nSpot);
	
	CCPoint GetPegTip(void) { return m_ccpPegTip; }
};

#endif // __GAMESPOT_H_