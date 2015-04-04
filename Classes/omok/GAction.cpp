#include "GAction.h"

GAction::GAction() :x(-1), y(-1)
{
}

GAction::GAction(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool GAction::isEqual(GAction act) const{
	if (this->x == act.x && this->y == act.y) return true;
	else return false;
}

bool GAction::isEqual(int x, int y) const{
	if (this->x == x && this->y == y) return true;
	else return false;
}

float GAction::getLength(GAction act){
	int xlen = this->x - act.x;
	if (xlen < 0) xlen *= -1;
	int ylen = this->y - act.y;
	if (ylen < 0) ylen *= -1;
	return (xlen > ylen) ? xlen : ylen;
}