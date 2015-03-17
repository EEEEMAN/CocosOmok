#include "CpuOri.h"

CpuOri::CpuOri(){
	characterID = CharacterID::CHAR_ORI;
	readTurn = 0;
	imageName = "ori.png";
	name = "오리";
	stone = new Stone_Ori();
	money = 65;
	stoneProbability = 0.85;
}

int CpuOri::seachString(char* str) const{
	int util = 0;

	if (strstr(str, "ox")){
		util += 1;
	}
	if (strstr(str, "xo")){
		util += 1;
	}
	if (strstr(str, "oxo")){
		util += 15;
	}
	if (strstr(str, "oo---")){
		util += 5;
	}
	if (strstr(str, "-oo--")){
		util += 10;
	}
	if (strstr(str, "--oo-")){
		util += 10;
	}
	if (strstr(str, "---oo")){
		util += 5;
	}
	if (strstr(str, "o-o--")){
		util += 5;
	}
	if (strstr(str, "-o-o-")){
		util += 10;
	}
	if (strstr(str, "--o-o")){
		util += 5;
	}
	if (strstr(str, "ooo--")){
		util += 15;
	}
	if (strstr(str, "oo-o-")){
		util += 15;
	}
	if (strstr(str, "oo--o")){
		util += 5;
	}
	if (strstr(str, "o-o-o")){
		util += 15;
	}
	if (strstr(str, "o--oo")){
		util += 5;
	}
	if (strstr(str, "-o-oo")){
		util += 15;
	}
	if (strstr(str, "--ooo")){
		util += 15;
	}
	if (strstr(str, "-ooo-")){
		util += 50;
	}
	if (strstr(str, "o-ooo")){
		util += 70;
	}
	if (strstr(str, "ooo-o")){
		util += 70;
	}
	if (strstr(str, "-oooo")){
		util += 75;
	}
	if (strstr(str, "oooo-")){
		util += 75;
	}
	if (strstr(str, "oo-oo")){
		util += 75;
	}
	if (strstr(str, "-oooo-")){
		util += 100;
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
		util -= 10;
	}
	if (strstr(str, "-xx--")){
		util -= 10;
	}
	if (strstr(str, "-x-x-")){
		util -= 10;
	}
	if (strstr(str, "x-x--")){
		util -= 5;
	}
	if (strstr(str, "--x-x")){
		util -= 5;
	}
	if (strstr(str, "xxx--")){
		util -= 15;
	}
	if (strstr(str, "xx-x-")){
		util -= 15;
	}
	if (strstr(str, "xx--x")){
		util -= 10;
	}
	if (strstr(str, "x-x-x")){
		util -= 15;
	}
	if (strstr(str, "x--xx")){
		util -= 10;
	}
	if (strstr(str, "-x-xx")){
		util -= 15;
	}
	if (strstr(str, "--xxx")){
		util -= 15;
	}
	if (strstr(str, "-xxx-")){
		util -= 50;
	}
	if (strstr(str, "-xxxx")){
		util -= 50;
	}
	if (strstr(str, "xxxx-")){
		util -= 50;
	}
	if (strstr(str, "x-xxx")){
		util -= 50;
	}
	if (strstr(str, "xx-xx")){
		util -= 50;
	}
	if (strstr(str, "xxx-x")){
		util -= 50;
	}
	if (strstr(str, "-xxxx-")){
		util -= 100;
	}
	if (strstr(str, "xxxxx")){
		util -= 900;
	}

	if (strstr(str, "oxxxxo")){
		util += 900;
	}
	if (strstr(str, "xoxx")){
		util += 75;
	}
	if (strstr(str, "xxox")){
		util += 75;
	}
	if (strstr(str, "xxoxx")){
		util += 150;
	}
	if (strstr(str, "oxxx")){
		util += 50;
	}
	if (strstr(str, "xxxo")){
		util += 50;
	}

	return util;
}
