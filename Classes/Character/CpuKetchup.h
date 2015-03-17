#ifndef __CPU_KETCHUP_H__
#define __CPU_KETCHUP_H__

#include "CpuChar.h"
#include "Stone\Stone_ketchup.h"

class CpuKetchup : public CpuChar
{
public:
	CpuKetchup();
	virtual int seachString(char* str) const;
	virtual int utility(GNode* node) const;
};

#endif