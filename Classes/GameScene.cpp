//
//  GameScene.cpp
//  Peg Game
//
//  Created by Jared Hamby on 8/28/11.
//  Copyright Fruit-Punched Games, LLC 2011. All rights reserved.
//

#include "GameScene.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	GameScene *layer = GameScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	if(!CCLayerColor::initWithColor(ccc4(0, 0, 255, 255)))
		return false;
	
	
	bool bRet = false;
	do
	{
		//////////////////////////////
		// 1. super init first
		CC_BREAK_IF(!CCLayer::init());
		
		this->setIsTouchEnabled(true);
		
		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.
		
		// add a "close" icon to exit the progress. it's an autorelease object
		//CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
		//										"CloseNormal.png",
		//										"CloseSelected.png",
		//										this,
		//										menu_selector(HelloWorld::menuCloseCallback) );
		//	pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );
		
		// create menu, it's an autorelease object
		//CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
		//pMenu->setPosition( CCPointZero );
		//this->addChild(pMenu, 1);
		
		/////////////////////////////
		// 3. add your codes below...
		
		// add a label shows "Hello World"
		// create and initialize a label
		//CCLabelTTF* pLabel = CCLabelTTF::labelWithString("Hello World", "Thonburi", 34);
		
		// ask director the window size
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		// position the label on the center of the screen
		//pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
		
		// add the label as a child to this layer
		//this->addChild(pLabel, 1);
		
		// add "HelloWorld" splash screen"
		//CCSprite* pSprite = new CCSprite;
		//pSprite = spriteWithFile("Triangle01.png");
		//pSprite->setPosition(ccp(0, 0));
		//this->addChild(pSprite);
		
		// position the sprite on the center of the screen
		//pSprite->setPosition( ccp(size.width/2, size.height/2) );
		
		// add the sprite as a child to this layer
		//this->addChild(pSprite, 0);
		
		m_Gameboard = new Gameboard();
		for(int i = 0; i < 14; i++)
			m_vGamePieces.push_back(new GamePiece(m_Gameboard->GetSpot(i)));
		//ccDrawCircle(ccp(50, 50), 1.0f, 0.0f, 6, false);
		
		this->addChild(m_Gameboard);

		for(int i = 0; i < 6; i++)
			this->addChild(m_Gameboard->GetBoardSprite(i), i*2);
		this->addChild(m_vGamePieces[0], m_vGamePieces[0]->GetCurrentSpot()->GetZOrder());
		

		bRet = true;
	} while(0);
	
	return bRet;
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}
