/*
 *  MenuScene.h
 *  Peg Game
 *
 *  Created by jamby on 12/23/11.
 *  Copyright 2011 Fruit-Punched Games. All rights reserved.
 *
 */

#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class MenuScene : public CCLayerColor
{
public:
	CCScene* GetInstance();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(MenuScene);
};

#endif // __MENU_SCENE_H__
