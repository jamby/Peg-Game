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
	float m_fRadius;
	
	void SetSpotIndex(int nSpotIndex) { m_nSpotIndex = nSpotIndex; }
	
public:
	GameSpot(int nSpotIndex);
	~GameSpot(void);
	
	void AddJumpSpot(GameSpot* gsJumpSpot) { m_vJumpSpots.push_back(gsJumpSpot); }
	void AddAdjacentSpot(GameSpot* gsAdjacentSpot) { m_vAdjacentSpots.push_back(gsAdjacentSpot); }
	void SetZOrder(int nNum) { m_nZOrder = nNum; }
	int GetZOrder(void) { return m_nZOrder; }
	void SetGamePiece(GamePiece* gpPiece) { m_gpPiece = gpPiece; }
	GamePiece* GetGamePiece(void) { return m_gpPiece; }
	
	int GetSpotIndex(void) { return m_nSpotIndex; }
	bool CheckConnectors(int nSubscript);
	vector<GameSpot*> GetAdjacentSpots(void) { return m_vAdjacentSpots; }
	GameSpot* GetSpecificAdjacentSpot(int nSpot);
	vector<GameSpot*> GetJumpSpots(void) { return m_vJumpSpots; }
	GameSpot* GetSpecificJumpSpot(int nSpot);
	
	CCPoint GetPegTip(void) { return m_ccpPegTip; }
	CCPoint GetCirclePoint(void) { return m_ccpCirclePoint; }
	float GetRadius(void) { return m_fRadius; }
};

#endif // __GAMESPOT_H_