#include "stdafx.h"
#include "Model.h"
//#include <string>

//TODO posprz�ta�


Model::Model(ObjFileLoader *pieceLoaded, int color, float xShift, float zShift){
	//this->fileName = fileName;
	this->object = pieceLoaded;
	this->color = color;
	this->speedHorizontal = 0;
	this->speedVertical = 10; //tutaj zmieni� na 100
	this->dir = up;
	this->verticalShift = 2,3;
	this->counter = 0;
	this->shifted = false;
	this->isCaptured = false;
	this->pieceName = pieceLoaded->fileName.substr(0,pieceLoaded->fileName.size()-4);


	this->xStartingShift = xShift;
	this->zStartingShift = zShift;
	this->xAnimationShift = this->xStartingShift;
	this->zAnimationShift = this->zStartingShift;


	//object = new ObjFileLoader();
	//object->loadObj(fileName,v,n,e);
	//object->loadIndices(fileName,vi,ni,ti);

	//chamskie rozwi�zanie, wszystkie wywo�ania w konstruktorze
	
};
