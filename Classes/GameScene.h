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
	GamePiece* m_gpSelectedPiece;
	GameSpot* m_gsNewSpot;
	int m_nEmptyStartingSpot;
	int m_nRemovingPiece;
	
	bool m_bRemovingPiece;
	float m_fOpacityPer;
	float m_fOpacityLerp;
	float m_fYPer;
	float m_fYLerp;
	
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	
	void update(ccTime dt);
	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	
	GameSpot* GetNewSpot(void) { return m_gsNewSpot; }
	void SetNewSpot(GameSpot* newSpot) { m_gsNewSpot = newSpot; }
	vector<GamePiece*> GetGamePieces(void) { return m_vGamePieces; }
	void AddUsedPiece(GamePiece* pGamePiece) { m_vGamePieces.push_back(pGamePiece); }
	vector<GamePiece*> GetUsedPieces(void) { return m_vUsedPieces; }
	
	void SetRemovingPiece(int nRemovingPiece) { m_nRemovingPiece = nRemovingPiece; }
	void SetBoolRemovingPiece(bool bRemovingPiece) { m_bRemovingPiece = bRemovingPiece; }
	
	void StartUpGame(CCPoint location);
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	GamePiece* GetSelectedPiece(void) { return m_gpSelectedPiece; }
	
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
