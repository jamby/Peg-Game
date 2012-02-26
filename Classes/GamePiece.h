/*
 *  GamePiece.h
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#ifndef __GAMEPIECE_H_
#define __GAMEPIECE_H_

#include "cocos2d.h"
using namespace cocos2d;
#include "GameSpot.h"

class GameLayer;

class GamePiece : public CCNode
{
private:
	int m_nColor;
	bool m_bIsPlayable;
	bool m_bIsChosen;
	GameSpot* m_gsCurrentSpot;
	GameSpot* m_gsPreviousSpot;
	CCSprite* m_pSprite;
	int m_nZOrder;
	
	CCPoint m_ccpTop;
	float m_fRadius;
	
	GameLayer* m_pGameLayer;

	
public:
	GamePiece(GameSpot* pSpot);
	~GamePiece(void);
	
	bool GetIsChosen(void) {return m_bIsChosen; }
	bool CanJump(void);
	void JumpToSpot(int nSpot);
	GameSpot* GetCurrentSpot(void) { return m_gsCurrentSpot; }
	int GetCurrentSpotNumber(void) { return m_gsCurrentSpot->GetSpotIndex(); }
	void SetCurrentSpot(GameSpot* gsCurrentSpot) { m_gsCurrentSpot = gsCurrentSpot; }
	CCSprite* GetSprite(void) { return m_pSprite; }
	
	void SetTopPoint(CCPoint ccpTop) { m_ccpTop = ccpTop; }
	CCPoint GetTopPoint(void) { return m_ccpTop; }
	float GetRadius(void) { return m_fRadius; }
	
	void SetZOrder(int nZOrder) { m_nZOrder = nZOrder; }
	int GetZOrder(void) { return m_nZOrder; }
};

#endif // __GAMEPIECE_H_