//
//  GameScene.h
//  Peg Game
//
//  Created by Jared Hamby on 8/28/11.
//  Copyright Fruit-Punched Games, LLC 2011. All rights reserved.
//

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
#include "Gameboard.h"
#include "GamePiece.h"
//#include "Box2D.h"

class GameScene : public CCLayerColor
{
private:
	Gameboard* m_Gameboard;
	vector<GamePiece*> m_vGamePieces;
	vector<GamePiece*> m_vUsedPieces;
//	b2World* m_b2World;
	
public:
	static CCScene* GetInstance();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(GameScene);
};

#endif // __MENU_SCENE_H__
