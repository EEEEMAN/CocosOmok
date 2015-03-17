#include "CpuJanggab.h"

CpuJanggab::CpuJanggab() {
	characterID = CharacterID::CHAR_JANGGAB;
	readTurn = 0;
	imageName = "janggab.png";
	name = "장갑";
	stone = new Stone_Sock();
	money = 70;
	stoneProbability = 0.75;
}

int CpuJanggab::seachString(char* str) const {
	int util = 0;

	if (strstr(str, "--o--")) {
		util += 1;
	}
	if (strstr(str, "--oo-")) {
		util += 2;
	}
	if (strstr(str, "-o-o-")) {
		util += 2;
	}
	if (strstr(str, "-oo--")) {
		util += 2;
	}
	if (strstr(str, "-ooo-")) {
		util += 10;
	}
	if (strstr(str, "oooo-")) {
		util += 15;
	}
	if (strstr(str, "ooo-o")) {
		util += 15;
	}
	if (strstr(str, "oo-oo")) {
		util += 15;
	}
	if (strstr(str, "o-ooo")) {
		util += 15;
	}
	if (strstr(str, "-oooo")) {
		util += 15;
	}
	if (strstr(str, "ooooo")) {
		util += 1000;
	}

	if (strstr(str, "--x--")) {
		util -= 1;
	}
	if (strstr(str, "--xx-")) {
		util -= 2;
	}
	if (strstr(str, "-x-x-")) {
		util -= 2;
	}
	if (strstr(str, "-xx--")) {
		util -= 2;
	}
	if (strstr(str, "-xxx-")) {
		util -= 10;
	}
	if (strstr(str, "xxxx-")) {
		util -= 15;
	}
	if (strstr(str, "xxx-x")) {
		util -= 15;
	}
	if (strstr(str, "xx-xx")) {
		util -= 15;
	}
	if (strstr(str, "x-xxx")) {
		util -= 15;
	}
	if (strstr(str, "-xxxx")) {
		util -= 15;
	}
	if (strstr(str, "xxxxx")) {
		util -= 1000;
	}

	if (strstr(str, "oxxxxo")) {
		util += 1000;
	}
	if (strstr(str, "xxxox")) {
		util += 100;
	}
	if (strstr(str, "xxoxx")) {
		util += 100;
	}
	if (strstr(str, "xoxxx")) {
		util += 100;
	}
	if (strstr(str, "oxxxx-")) {
		util += 50;
	}
	if (strstr(str, "-xxxxo")) {
		util += 50;
	}
	return util;
}