#include "stdafx.h"
#include "Model.h"
//#include <string>

//TODO posprz¹taæ


Model::Model(std::string fileName, int color, int xShift, int zShift){
	this->fileName = fileName;
	this->color = color;
	this->speedHorizontal = 0;
	this->speedVertical = 500;
	this->dir = up;
	this->verticalShift = 1;
	this->counter = 0;
	this->shifted = false;
	this->isCaptured = false;


	this->xStartingShift = xShift;
	this->zStartingShift = zShift;
	this->xAnimationShift = this->xStartingShift;
	this->zAnimationShift = this->zStartingShift;


	object = new ObjFileLoader();
	object->loadObj(fileName,v,n,e);
	object->loadIndices(fileName,vi,ni,ti);

	//chamskie rozwi¹zanie, wszystkie wywo³ania w konstruktorze
	loadVerticesIntoArray();
	loadVerticesInto2DArray();
	loadNormalsInto2DArray();
	loadVerticesArrayToDraw();
	loadNormalsArrayToDraw();
};
void Model::loadVerticesIntoArray(){
	vertices = new float[3*v.size()];
	std::vector<glm::vec4>::iterator it;
	int j=0;
	for(it=v.begin(); it!=v.end(); it++){
		vertices[j*3] = (*it).x;
		vertices[j*3+1] = (*it).y;
		vertices[j*3+2] = (*it).z;
		j++;
	}
};
void Model::loadVerticesInto2DArray(){
	twoDimensionVertices = new float *[v.size()];
	std::vector<glm::vec4>::iterator it;
	for(int i=0; i<v.size(); i++)
		twoDimensionVertices[i] = new float[3];
	int j=0;
	for(it=v.begin(); it!=v.end(); it++){
		twoDimensionVertices[j][0] = (*it).x;
		twoDimensionVertices[j][1] = (*it).y;
		twoDimensionVertices[j][2] = (*it).z;
		j++;
	}
};
void Model::loadNormalsInto2DArray(){
	twoDimensionNormals = new float *[n.size()];
	std::vector<glm::vec3>::iterator it;
	for(int i=0; i<n.size(); i++)
		twoDimensionNormals[i] = new float[3];
	int j=0;
	for(it=n.begin(); it!=n.end(); it++){
		twoDimensionNormals[j][0] = (*it).x;
		twoDimensionNormals[j][1] = (*it).y;
		twoDimensionNormals[j][2] = (*it).z;
		j++;
	}
};
void Model::loadVerticesArrayToDraw(){
	verticesArrayToDraw = new float[9*vi.size()];
	std::vector<std::vector<int>>::iterator it0;
	std::vector<int>::iterator it1;
	int counter=0;
	for(it0=vi.begin(); it0!=vi.end(); it0++){
		for(it1=(*it0).begin(); it1!=(*it0).end(); it1++){
			for(int i=0; i<3; i++)
				verticesArrayToDraw[3*counter+i] = twoDimensionVertices[(*it1)-1][i];
			counter++;
		}
	}
	verticesArrayToDrawSize = 3*vi.size();
};
void Model::loadNormalsArrayToDraw(){
	normalsArrayToDraw = new float[9*ni.size()];
	std::vector<std::vector<int>>::iterator it0;
	std::vector<int>::iterator it1;
	int counter = 0;
	for(it0=ni.begin(); it0!=ni.end(); it0++){
		for(it1=(*it0).begin(); it1!=(*it0).end(); it1++){
			for(int i=0; i<3; i++)
				normalsArrayToDraw[3*counter+i] = twoDimensionNormals[(*it1)-1][i];
			counter++;
		}
	}
	normalsArrayToDrawSize = 3*vi.size();
};