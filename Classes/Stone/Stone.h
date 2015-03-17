#ifndef __STONE_H__
#define __STONE_H__

#include "OmokDefine.h"

class Stone
{
protected:
	char* imgName1P = 0;
	char* imgName2P = 0;
	StoneID stoneID;
public:
	Stone();
	Stone(Stone &T);
	virtual char* getImgName1P();
	virtual char* getImgName2P();
	virtual StoneID getStoneID();
};

#endif