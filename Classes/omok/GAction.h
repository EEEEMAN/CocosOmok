#ifndef __GACTION_H__
#define __GACTION_H__

#include <math.h>
#include "OmokDefine.h"

class GAction
{
public:
	GAction();
	GAction(int x,int y);

	bool isEqual(GAction act) const;
	bool isEqual(int x, int y) const;
	float getLength(GAction act); //거리계산
public:
	//0~ROW-1
	int x;
	int y;
};

#endif
