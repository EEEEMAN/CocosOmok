#ifndef __CPU_MYEOLCHI_H__
#define __CPU_MYEOLCHI_H__

#include "CpuChar.h"
#include "Stone\Stone_Fish.h"

class CpuMyeolchi : public CpuChar
{
public:
	CpuMyeolchi();
	virtual int seachString(char* str) const;
};

#endif
