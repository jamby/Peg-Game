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

float Lerp(float fStart, float fEnd, float fPercent)
{
	return fStart + ((fEnd - fStart) * fPercent);
}

bool PointInCircle(CCPoint ccpPoint, CCPoint ccpCircleCenter, float fRadius)
{
	float distance = sqrt((ccpPoint.x - ccpCircleCenter.x) * (ccpPoint.x - ccpCircleCenter.x) + 
						  (ccpPoint.y - ccpCircleCenter.y) * (ccpPoint.y - ccpCircleCenter.y));
	
	if(distance > fRadius)
		return false;
	else
		return true;
}