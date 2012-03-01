/*
 *  FPGMath.cpp
 *  Peg Game
 *
 *  Created by jamby on 3/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */
#include "FPGMath.h"

float Lerp(float fStart, float fEnd, float fPercent)
{
	return fStart + ((fEnd - fStart) * fPercent);
}

bool PointInCircle(cocos2d::CCPoint ccpPoint, cocos2d::CCPoint ccpCircleCenter, float fRadius)
{
	float fDistance = sqrt((ccpPoint.x - ccpCircleCenter.x) * (ccpPoint.x - ccpCircleCenter.x) + 
						   (ccpPoint.y - ccpCircleCenter.y) * (ccpPoint.y - ccpCircleCenter.y));
	
	if(fRadius >= fDistance )
		return true;
	else
		return false;
}