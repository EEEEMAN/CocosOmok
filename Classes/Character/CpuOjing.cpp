#include "CpuOjing.h"


CpuOjing::CpuOjing(){
	characterID = CharacterID::CHAR_OJING;
	readTurn = 0;
	imageName = "ojing.png";
	name = "오징어";
	stone = new Stone_Ojing();
	money = 50;
	stoneProbability = 1.0;
}

int CpuOjing::seachString(char* str) const {
	int util = 0;
	

	if (strstr(str, "--oo-") || strstr(str, "-o-o-") || strstr(str, "-oo--")) {
		util += 4;
	}
	else if (strstr(str, "--xoo") || strstr(str, "-xoo-") || strstr(str, "xoo--")
		|| strstr(str, "oox--") || strstr(str, "-oox-") || strstr(str, "--oox")
		|| strstr(str, "-oxo-")) {
		util -= 4;
	}
	if (strstr(str, "ooo--") || strstr(str, "--ooo")) {
		util += 16;
	}
	else if (strstr(str, "ooox-") || strstr(str, "-xooo")){
		util -= 16;
	}
	if (strstr(str, "o-oo-") || strstr(str, "-oo-o") || strstr(str, "-o-oo") || strstr(str, "oo-o-")){
		util += 16;
	}
	else if (strstr(str, "oxoo-") || strstr(str, "-ooxo") || strstr(str, "-oxoo") || strstr(str, "ooxo-")){
		util -= 16;
	}
	if (strstr(str, "-ooo-")) {
		util += 64;
	}
	else if (strstr(str, "xooo-") || strstr(str, "-ooox")) {
		util -= 64;
	}
	if (strstr(str, "oooo-") || strstr(str, "ooo-o") || strstr(str, "oo-oo") || strstr(str, "o-ooo") || strstr(str, "-oooo")) {
		util += 64;
	}
	else if (strstr(str, "oooox") || strstr(str, "oooxo") || strstr(str, "ooxoo") || strstr(str, "xoooo")){
		util -= 64;
	}
	if (strstr(str, "-oooo-")){
		util += 256;
	}

	if (strstr(str, "x----") || strstr(str, "----x") || strstr(str, "--x--") || strstr(str, "-x---") || strstr(str, "---x-")) {
		util -= 1;
	}
	else if (strstr(str, "xo---") || strstr(str, "-xo--") || strstr(str, "--xo-") || strstr(str, "---xo-")
		|| strstr(str, "---ox") || strstr(str, "--ox-") || strstr(str, "-ox--") || strstr(str, "ox---")) {
		util += 1;
	}
	if (strstr(str, "---xx") || strstr(str, "xx---") || strstr(str, "--xx-") || strstr(str, "-x-x-") || strstr(str, "-xx--")) {
		util -= 4;
	}
	else if (strstr(str, "--oxx") || strstr(str, "-oxx-") || strstr(str, "oxx--")
		|| strstr(str, "xxo--") || strstr(str, "-xxo-") || strstr(str, "--xxo")
		|| strstr(str, "-xox-")) {
		util += 4;
	}
	if (strstr(str, "xxx--") || strstr(str, "--xxx")) {
		util -= 16;
	}
	else if (strstr(str, "xxxo-") || strstr(str, "-oxxx")){
		util += 16;
	}
	if (strstr(str, "x-xx-") || strstr(str, "-xx-x") || strstr(str, "-x-xx") || strstr(str, "xx-x-")){
		util -= 16;
	}
	else if (strstr(str, "xoxx-") || strstr(str, "-xxox") || strstr(str, "-xoxx") || strstr(str, "xxox-")){
		util += 16;
	}
	if (strstr(str, "-xxx-")) {
		util -= 64;
	}
	else if (strstr(str, "oxxx-") || strstr(str, "-xxxo")) {
		util += 64;
	}
	if (strstr(str, "xxxx-") || strstr(str, "xxx-x") || strstr(str, "xx-xx") || strstr(str, "x-xxx") || strstr(str, "-xxxx")) {
		util -= 64;
	}
	else if (strstr(str, "xxxxo") || strstr(str, "xxxox") || strstr(str, "xxoxx") || strstr(str, "oxxxx")){
		util += 64;
	}
	if (strstr(str, "-xxxx-")){
		util -= 256;
	}

	return util;
}
