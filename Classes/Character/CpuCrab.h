#ifndef __CPU_CRAB_H__
#define __CPU_CRAB_H__

#include "CpuChar.h"
#include "Stone\Stone_Crab.h"

class CpuCrab : public CpuChar
{
public:
	CpuCrab();
	virtual int seachString(char* str) const;
};

#endif