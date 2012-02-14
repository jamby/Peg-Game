/*
 *  Gameboard.cpp
 *  Peg Game
 *
 *  Created by Jared Hamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#include "Gameboard.h"

Gameboard::Gameboard()
{
	m_vSpots.clear();
	
	for(int i = 0; i < 6; i++)
		m_vSprites[i] = NULL;
	
	init();
}

Gameboard::~Gameboard()
{
	CleanUpBoard();
}

void Gameboard::init(void)
{
	for(int i = 0; i < 15; i++)
		m_vSpots.push_back(new GameSpot(i+1));
	
	//////////////////
	// Spot 1 ([0])
	//////////////////
	// Adjacent Spots
	m_vSpots[0]->AddAdjacentSpot(m_vSpots[1]);
	m_vSpots[0]->AddAdjacentSpot(m_vSpots[2]);
	
	// Jump Spots
	m_vSpots[0]->AddJumpSpot(m_vSpots[3]);
	m_vSpots[0]->AddJumpSpot(m_vSpots[5]);
	
	m_vSpots[0]->SetZOrder(1);
	
	//////////////////
	// Spot 2 ([1])
	//////////////////
	// Adjacent Spots
	m_vSpots[1]->AddAdjacentSpot(m_vSpots[3]);
	m_vSpots[1]->AddAdjacentSpot(m_vSpots[4]);
	
	// Jump Spots
	m_vSpots[1]->AddJumpSpot(m_vSpots[6]);
	m_vSpots[1]->AddJumpSpot(m_vSpots[8]);
	
	m_vSpots[1]->SetZOrder(3);
	
	//////////////////
	// Spot 3 ([2])
	//////////////////
	// Adjacent Spots
	m_vSpots[2]->AddAdjacentSpot(m_vSpots[4]);
	m_vSpots[2]->AddAdjacentSpot(m_vSpots[5]);
	
	// Jump Spots
	m_vSpots[2]->AddJumpSpot(m_vSpots[7]);
	m_vSpots[2]->AddJumpSpot(m_vSpots[9]);
	
	m_vSpots[2]->SetZOrder(3);
	
	//////////////////
	// Spot 4 ([3])
	//////////////////
	// Adjacent Spots
	m_vSpots[3]->AddAdjacentSpot(m_vSpots[1]);
	m_vSpots[3]->AddAdjacentSpot(m_vSpots[4]);
	m_vSpots[3]->AddAdjacentSpot(m_vSpots[6]);
	m_vSpots[3]->AddAdjacentSpot(m_vSpots[7]);
	
	// Jump Spots
	m_vSpots[3]->AddJumpSpot(m_vSpots[0]);
	m_vSpots[3]->AddJumpSpot(m_vSpots[5]);
	m_vSpots[3]->AddJumpSpot(m_vSpots[10]);
	m_vSpots[3]->AddJumpSpot(m_vSpots[12]);
	
	//////////////////
	// Spot 5 ([4])
	//////////////////
	// Adjacent Spots
	m_vSpots[4]->AddAdjacentSpot(m_vSpots[7]);
	m_vSpots[4]->AddAdjacentSpot(m_vSpots[8]);
	
	// Jump Spots
	m_vSpots[4]->AddJumpSpot(m_vSpots[11]);
	m_vSpots[4]->AddJumpSpot(m_vSpots[13]);
	
	//////////////////
	// Spot 6 ([5])
	//////////////////
	// Adjacent Spots
	m_vSpots[5]->AddAdjacentSpot(m_vSpots[2]);
	m_vSpots[5]->AddAdjacentSpot(m_vSpots[4]);
	m_vSpots[5]->AddAdjacentSpot(m_vSpots[8]);
	m_vSpots[5]->AddAdjacentSpot(m_vSpots[9]);
	
	// Jump Spots
	m_vSpots[5]->AddJumpSpot(m_vSpots[0]);
	m_vSpots[5]->AddJumpSpot(m_vSpots[3]);
	m_vSpots[5]->AddJumpSpot(m_vSpots[12]);
	m_vSpots[5]->AddJumpSpot(m_vSpots[14]);
	
	//////////////////
	// Spot 7 ([6])
	//////////////////
	// Adjacent Spots
	m_vSpots[6]->AddAdjacentSpot(m_vSpots[3]);
	m_vSpots[6]->AddAdjacentSpot(m_vSpots[7]);
	
	// Jump Spots
	m_vSpots[6]->AddJumpSpot(m_vSpots[1]);
	m_vSpots[6]->AddJumpSpot(m_vSpots[8]);
	
	//////////////////
	// Spot 8 ([7])
	//////////////////
	// Adjacent Spots
	m_vSpots[7]->AddAdjacentSpot(m_vSpots[4]);
	m_vSpots[7]->AddAdjacentSpot(m_vSpots[8]);
	
	// Jump Spots
	m_vSpots[7]->AddAdjacentSpot(m_vSpots[2]);
	m_vSpots[7]->AddAdjacentSpot(m_vSpots[9]);
	
	//////////////////
	// Spot 9 ([8])
	//////////////////
	// Adjacent Spots
	m_vSpots[8]->AddAdjacentSpot(m_vSpots[4]);
	m_vSpots[8]->AddAdjacentSpot(m_vSpots[7]);
	
	// Jump Spots
	m_vSpots[8]->AddJumpSpot(m_vSpots[1]);
	m_vSpots[8]->AddJumpSpot(m_vSpots[6]);
	
	//////////////////
	// Spot 10 ([9])
	//////////////////
	// Adjacent Spots
	m_vSpots[9]->AddAdjacentSpot(m_vSpots[5]);
	m_vSpots[9]->AddAdjacentSpot(m_vSpots[8]);
	
	// Jump Spots
	m_vSpots[9]->AddJumpSpot(m_vSpots[2]);
	m_vSpots[9]->AddJumpSpot(m_vSpots[7]);
	
	//////////////////
	// Spot 11 ([10])
	//////////////////
	// Adjacent Spots
	m_vSpots[10]->AddAdjacentSpot(m_vSpots[6]);
	m_vSpots[10]->AddAdjacentSpot(m_vSpots[11]);
	
	// Jump Spots
	m_vSpots[10]->AddJumpSpot(m_vSpots[3]);
	m_vSpots[10]->AddJumpSpot(m_vSpots[12]);
	
	//////////////////
	// Spot 12 ([11])
	//////////////////
	// Adjacent Spots
	m_vSpots[11]->AddAdjacentSpot(m_vSpots[7]);
	m_vSpots[11]->AddAdjacentSpot(m_vSpots[12]);
	
	// Jump Spots
	m_vSpots[11]->AddJumpSpot(m_vSpots[4]);
	m_vSpots[11]->AddJumpSpot(m_vSpots[13]);
	
	//////////////////
	// Spot 13 ([12])
	//////////////////
	// Adjacent Spots
	m_vSpots[12]->AddAdjacentSpot(m_vSpots[7]);
	m_vSpots[12]->AddAdjacentSpot(m_vSpots[8]);
	m_vSpots[12]->AddAdjacentSpot(m_vSpots[11]);
	m_vSpots[12]->AddAdjacentSpot(m_vSpots[13]);
	
	// Jump Spots
	m_vSpots[12]->AddJumpSpot(m_vSpots[3]);
	m_vSpots[12]->AddJumpSpot(m_vSpots[5]);
	m_vSpots[12]->AddJumpSpot(m_vSpots[10]);
	m_vSpots[12]->AddJumpSpot(m_vSpots[14]);
	
	//////////////////
	// Spot 14 ([13])
	//////////////////
	// Adjacent Spots
	m_vSpots[13]->AddAdjacentSpot(m_vSpots[8]);
	m_vSpots[13]->AddAdjacentSpot(m_vSpots[12]);
	
	// Jump Spots
	m_vSpots[13]->AddJumpSpot(m_vSpots[4]);
	m_vSpots[13]->AddJumpSpot(m_vSpots[11]);
	
	//////////////////
	// Spot 15 ([14])
	//////////////////
	// Adjacent Spots
	m_vSpots[14]->AddAdjacentSpot(m_vSpots[9]);
	m_vSpots[14]->AddAdjacentSpot(m_vSpots[13]);
	
	// Jump Spots
	m_vSpots[14]->AddJumpSpot(m_vSpots[5]);
	m_vSpots[14]->AddJumpSpot(m_vSpots[12]);
	
//	m_vSprites[0] = CCSprite::spriteWithFile("Icon.png");
//	m_vSprites[1] = CCSprite::spriteWithFile("Triangle01.png");
//	m_vSprites[0]->setPosition(ccp(0, 0));
//	m_vSprites[0]->setAnchorPoint(ccp(.5, .5));
//	m_vSprites[1]->setPosition(ccp(0, 0));
//	m_vSprites[1]->setAnchorPoint(ccp(0, 0));
//	this->addChild(m_vSprites[0], 3);
//	this->addChild(m_vSprites[1], 2);
	
	m_vSprites[0] = CCSprite::spriteWithFile("Triangle01.png");
	m_vSprites[0]->setPosition(ccp(-85, 380));
	m_vSprites[0]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[0], 0);
	m_vSprites[1] = CCSprite::spriteWithFile("Triangle02.png");
	m_vSprites[1]->setPosition(ccp(-85, 380));
	m_vSprites[1]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[1], 2);
	m_vSprites[2] = CCSprite::spriteWithFile("Triangle03.png");
	m_vSprites[2]->setPosition(ccp(-85, 380));
	m_vSprites[2]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[2], 4);
	m_vSprites[3] = CCSprite::spriteWithFile("Triangle04.png");
	m_vSprites[3]->setPosition(ccp(-85, 380));
	m_vSprites[3]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[3], 6);
	m_vSprites[4] = CCSprite::spriteWithFile("Triangle05.png");
	m_vSprites[4]->setPosition(ccp(-85, 380));
	m_vSprites[4]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[4], 8);
	m_vSprites[5] = CCSprite::spriteWithFile("Triangle06.png");
	m_vSprites[5]->setPosition(ccp(-85, 380));
	m_vSprites[5]->setAnchorPoint(ccp(0, 1));
	//this->addChild(m_vSprites[5], 10);
}

void Gameboard::CleanUpBoard(void)
{
	for(int i = 0; i < 10; i++)
	{
		GameSpot* tempSpot = m_vSpots.back();
		m_vSpots.pop_back();
		delete tempSpot;
	}
}