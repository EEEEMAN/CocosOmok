#ifndef __CPU_OMOK_H__
#define __CPU_OMOK_H__

#include "CpuChar.h"
#include "Stone\Stone_Cross.h"

class CpuOmok : public CpuChar
{
public:
	CpuOmok();
	virtual int seachString(char* str) const;
};

#endif
