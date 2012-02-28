/*
 *  Gameboard.h
 *  Peg Game
 *
 *  Created by jamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include "cocos2d.h"
using namespace cocos2d;
#include "GameSpot.h"

class Gameboard : public CCNode
{
private:
	vector<GameSpot*> m_vSpots;
	CCSprite* m_vSprites[6];
	
	void CleanUpBoard(void);
	
public:
	Gameboard();
	~Gameboard();
	void init(void);
	
	GameSpot* GetSpot(int nSpot) { return m_vSpots[nSpot]; }
	CCSprite* GetBoardSprite(int nSprite) { return m_vSprites[nSprite]; }
	vector<GameSpot*> GetSpots(void) { return m_vSpots; }
};

#endif // __GAMEBOARD_H__
