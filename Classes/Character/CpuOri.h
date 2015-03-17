#ifndef __CPU_ORI_H__
#define __CPU_ORI_H__

#include "CpuChar.h"
#include "Stone\Stone_Ori.h"

class CpuOri : public CpuChar
{
public:
	CpuOri();
	virtual int seachString(char* str) const;
};

#endif
