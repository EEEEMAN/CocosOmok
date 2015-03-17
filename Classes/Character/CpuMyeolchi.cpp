#include "CpuMyeolchi.h"

CpuMyeolchi::CpuMyeolchi(){
	characterID = CharacterID::CHAR_MYEOLCHI;
	readTurn = 0;
	imageName = "myeolchi.png";
	name = "멸치";
	stone = new Stone_Fish();
	money = 60;
	stoneProbability = 0.8;
}

int CpuMyeolchi::seachString(char* str) const{
	if (str[0] == '\n'){
		return 0;
	}
	int util = 0;

	if (strstr(str, "o-o--")){
		util += 1;
	}
	if (strstr(str, "--o-o")){
		util += 1;
	}
	if (strstr(str, "oo---")){
		util += 1;
	}
	if (strstr(str, "---oo")){
		util += 1;
	}

	if (strstr(str, "-oo--")){
		util += 5;
	}
	if (strstr(str, "--oo-")){
		util += 5;
	}
	if (strstr(str, "-o-o-")){
		util += 5;
	}
	if (strstr(str, "o-o-o")){
		util += 5;
	}

	if (strstr(str, "ooo--")){
		util += 10;
	}
	if (strstr(str, "oo-o-")){
		util += 10;
	}
	if (strstr(str, "--ooo")){
		util += 10;
	}
	if (strstr(str, "-o-oo")){
		util += 10;
	}

	if (strstr(str, "-ooo-")){
		util += 70;
	}
	if (strstr(str, "o-ooo")){
		util += 70;
	}
	if (strstr(str, "ooo-o")){
		util += 70;
	}
	if (strstr(str, "-oooo")){
		util += 70;
	}
	if (strstr(str, "oooo-")){
		util += 70;
	}
	if (strstr(str, "oo-oo")){
		util += 70;
	}
	if (strstr(str, "-oooo-")){
		util += 700;
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
		util -= 5;
	}
	if (strstr(str, "--x-x")){
		util -= 5;
	}

	if (strstr(str, "xxx--")){
		util -= 10;
	}
	if (strstr(str, "xx-x-")){
		util -= 10;
	}
	if (strstr(str, "-xx-x")){
		util -= 10;
	}
	if (strstr(str, "x-x-x")){
		util -= 10;
	}
	if (strstr(str, "-x-xx")){
		util -= 10;
	}
	if (strstr(str, "x-xx-")){
		util -= 10;
	}
	if (strstr(str, "--xxx")){
		util -= 10;
	}

	if (strstr(str, "-xxx-")){
		util -= 70;
	}
	if (strstr(str, "-xxxx")){
		util -= 70;
	}
	if (strstr(str, "xxxx-")){
		util -= 70;
	}
	if (strstr(str, "x-xxx")){
		util -= 70;
	}
	if (strstr(str, "xx-xx")){
		util -= 70;
	}
	if (strstr(str, "xxx-x")){
		util -= 70;
	}
	if (strstr(str, "-xxxx-")){
		util -= 700;
	}
	if (strstr(str, "xxxxx")){
		util -= 900;
	}

	if (strstr(str, "oxxxxo")){
		util += 900;
	}
	if (strstr(str, "oxxxo")){
		util += 5;
	}
	if (strstr(str, "-xoxx-")){
		util += 900;
	}
	if (strstr(str, "-xxox-")){
		util += 900;
	}
	if (strstr(str, "xxxox")){
		util += 900;
	}
	if (strstr(str, "xoxxx")){
		util += 900;
	}
	if (strstr(str, "xxoxx")){
		util += 900;
	}
	if (strstr(str, "-oxxx-")){
		util += 900;
	}
	if (strstr(str, "-xxxo-")){
		util += 900;
	}

	return util;
}
