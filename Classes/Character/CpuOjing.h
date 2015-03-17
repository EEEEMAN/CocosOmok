#ifndef __CPU_OJING_H__
#define __CPU_OJING_H__

#include "CpuChar.h"
#include "Stone\Stone_Ojing.h"

class CpuOjing : public CpuChar
{
public:
	CpuOjing();
	virtual int seachString(char* str) const;
};

#endif