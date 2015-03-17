#ifndef __CPU_JANGGAB_H__
#define __CPU_JANGGAB_H__

#include "CpuChar.h"
#include "Stone\Stone_Sock.h"

class CpuJanggab : public CpuChar
{
public:
	CpuJanggab();
	virtual int seachString(char* str) const;
};

#endif