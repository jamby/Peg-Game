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

class GameScene;

class GameLayer : public CCLayerColor
{
private:
	Gameboard* m_Gameboard;
	vector<GamePiece*> m_vGamePieces;
	vector<GamePiece*> m_vUsedPieces;
	GamePiece* m_pSelectedPiece;
	GameSpot* m_pNewSpot;
	
	//	b2World* m_b2World;
	
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	
	void update(ccTime dt);
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	GameSpot* GetNewSpot(void) { return m_pNewSpot; }
	void SetNewSpot(GameSpot* newSpot) { m_pNewSpot = newSpot; }
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	GamePiece* GetSelectedPiece(void) { return m_pSelectedPiece; }
	
	LAYER_NODE_FUNC(GameLayer);
};

class GameScene : public CCScene
{
private:
	
public:
	static GameScene* GetSceneInstance();
	static GameLayer* GetLayerInstance();
	
	SCENE_NODE_FUNC(GameScene);
};

#endif // __MENU_SCENE_H__
