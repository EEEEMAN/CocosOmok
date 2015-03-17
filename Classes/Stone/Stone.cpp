#include "Stone.h"

Stone::Stone(){
}

Stone::Stone(Stone &T){
	this->imgName1P = T.imgName1P;
	this->imgName2P = T.imgName2P;
	this->stoneID = T.stoneID;
}

char* Stone::getImgName1P(){
	return imgName1P;
}

char* Stone::getImgName2P(){
	return imgName2P;
}

StoneID Stone::getStoneID(){
	return stoneID;
}