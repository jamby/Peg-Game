/*
 *  FPGMath.h
 *  Peg Game
 *
 *  Created by jamby on 2/20/12.
 *  Copyright 2012 Fruit-Punched Games, LLC. All rights reserved.
 *
 */
#include "cocos2d.h"
#include <math.h>

float Lerp(float fStart, float fEnd, float fPercent);

bool PointInCircle(cocos2d::CCPoint ccpPoint, cocos2d::CCPoint ccpCircleCenter, float fRadius);