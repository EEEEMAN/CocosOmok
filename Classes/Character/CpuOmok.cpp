#include "CpuOmok.h"

CpuOmok::CpuOmok(){
	characterID = CharacterID::CHAR_OMOK;
	readTurn = 2;
	imageName = "omok.png";
	name = "오징어목사";
	stone = new Stone_Cross();
	money = 100;
	stoneProbability = 0.6;
}

int CpuOmok::seachString(char* str) const{
	if (str[0] == '\n'){
		return 0;
	}
	int util = 0;

	if (strstr(str, "oo---")){
		util += 1;
	}
	if (strstr(str, "---oo")){
		util += 1;
	}
	if (strstr(str, "--oo-")){
		util += 5;
	}
	if (strstr(str, "-oo--")){
		util += 5;
	}
	if (strstr(str, "-o-o-")){
		util += 5;
	}
	if (strstr(str, "o-o--")){
		util += 1;
	}
	if (strstr(str, "--o-o")){
		util += 1;
	}
	if (strstr(str, "ooo--")){
		util += 10;
	}
	if (strstr(str, "oo-o-")){
		util += 10;
	}
	if (strstr(str, "oo--o")){
		util += 5;
	}
	if (strstr(str, "o-o-o")){
		util += 10;
	}
	if (strstr(str, "o--oo")){
		util += 5;
	}
	if (strstr(str, "-o-oo")){
		util += 10;
	}
	if (strstr(str, "--ooo")){
		util += 10;
	}
	if (strstr(str, "-ooo-")){
		util += 50;
	}
	if (strstr(str, "o-ooo")){
		util += 50;
	}
	if (strstr(str, "ooo-o")){
		util += 50;
	}
	if (strstr(str, "-oooo")){
		util += 50;
	}
	if (strstr(str, "oooo-")){
		util += 50;
	}
	if (strstr(str, "oo-oo")){
		util += 50;
	}
	if (strstr(str, "ooooo")){
		util += 900;
	}

	if (strstr(str, "xx---")){
		util -= 1;
	}
	if (strstr(str, "---xx")){
		util -= 1;
	}
	if (strstr(str, "--xx-")){
		util -= 5;
	}
	if (strstr(str, "-xx--")){
		util -= 5;
	}
	if (strstr(str, "-x-x-")){
		util -= 5;
	}
	if (strstr(str, "x-x--")){
		util -= 1;
	}
	if (strstr(str, "--x-x")){
		util -= 1;
	}
	if (strstr(str, "xxx--")){
		util -= 10;
	}
	if (strstr(str, "xx-x-")){
		util -= 10;
	}
	if (strstr(str, "xx--x")){
		util -= 5;
	}
	if (strstr(str, "x-x-x")){
		util -= 10;
	}
	if (strstr(str, "x--xx")){
		util -= 5;
	}
	if (strstr(str, "-x-xx")){
		util -= 10;
	}
	if (strstr(str, "--xxx")){
		util -= 10;
	}
	if (strstr(str, "-xxx-")){
		util -= 50;
	}
	if (strstr(str, "x-xxx")){
		util -= 50;
	}
	if (strstr(str, "xxx-x")){
		util -= 50;
	}
	if (strstr(str, "-xxxx")){
		util -= 50;
	}
	if (strstr(str, "xxxx-")){
		util -= 50;
	}
	if (strstr(str, "xx-xx")){
		util -= 50;
	}
	if (strstr(str, "-xxxx-")){
		util -= 100;
	}
	if (strstr(str, "oxxxx-")){
		util -= 50;
	}
	if (strstr(str, "-xxxxo")){
		util -= 50;
	}
	if (strstr(str, "xxxxx")){
		util -= 900;
	}

	if (strstr(str, "oxxxxo")){
		util += 900;
	}
	if (strstr(str, "oxxxo")){
		util += 10;
	}
	if (strstr(str, "-xoxx-")){
		util += 100;
	}
	if (strstr(str, "-xxox-")){
		util += 100;
	}
	if (strstr(str, "xxoxx")){
		util += 900;
	}
	if (strstr(str, "xoxxx")){
		util += 900;
	}
	if (strstr(str, "xxxox")){
		util += 900;
	}
	if (strstr(str, "oxxx-")){
		util += 100;
	}
	if (strstr(str, "-xxxo")){
		util += 100;
	}

	return util;
}
