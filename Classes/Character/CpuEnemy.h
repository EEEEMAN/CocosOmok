#ifndef __CPU_ENEMY_H__
#define __CPU_ENEMY_H__

#include "CpuChar.h"
#include "Stone\Stone_Ojing.h"

class CpuEnemy : public CpuChar
{
public:
	CpuEnemy();
	virtual int seachString(char* str) const;
	virtual int alpha_beta(GNode* state, int alpha, int beta, int length);
	virtual GAction getBestAction(GNode* state);
};

#endif