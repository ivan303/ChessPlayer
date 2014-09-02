#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

#include "glm\gtc\type_ptr.hpp"
#include "GL\glut.h"

#include <iostream>
#include "ObjFileLoader.h"

ObjFileLoader::ObjFileLoader(std::string fileName) {
	this->fileName=fileName;
	this->loadObj(this->fileName,v,n,e);
	this->loadIndices(this->fileName,vi,ni,ti);

	loadVerticesIntoArray();
	loadVerticesInto2DArray();
	loadNormalsInto2DArray();
	loadVerticesArrayToDraw();
	loadNormalsArrayToDraw();
}

void ObjFileLoader::loadObj(std::string fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textures){
	std::ifstream in;
	in.open(fileName);
	if(in.is_open())
		std::cout << "otwarty";

	

	//std::string line;
	char line [255];
	char s [3];


	while(in.getline(line,255)){
		//printf("%s\n",line);
		
		if(!strncmp(line,"v ",2)){
			glm::vec4 v;
			sscanf_s(line,"v %f %f %f",&v.x,&v.y,&v.z);
			//v.w=1.0f;
			vertices.push_back(v);
		}
		else if(!strncmp(line,"vn ",3)){
			glm::vec3 n;
			sscanf_s(line,"vn %f %f %f",&n.x,&n.y,&n.z);
			normals.push_back(n);
		}
		else if(!strncmp(line,"vt ",3)){
			glm::vec2 t;
			sscanf_s(line,"vt %f %f",&t.x,&t.y);
			textures.push_back(t);
		}

				//przy vt 1-y
	}
	in.close();

}
void ObjFileLoader::loadIndices(std::string fileName, std::vector<std::vector<int>> &verIndicies, std::vector<std::vector<int>> &norIndicies, std::vector<std::vector<int>> &texIndicies){
	std::ifstream in;
	in.open(fileName);
	if(in.is_open())
		std::cout << "otwarty";

	char line[255];
	int v[3], n[3], t[3];
	std::vector<int> temp;

	while(in.getline(line, 255)){
		if(!strncmp(line, "f ", 2)){
			sscanf_s(line,"f %d/%d/%d %d/%d/%d %d/%d/%d",&v[0],&t[0],&n[0],&v[1],&t[1],&n[1],&v[2],&t[2],&n[2]);
			temp.push_back(v[0]);
			temp.push_back(v[1]);
			temp.push_back(v[2]);
			verIndicies.push_back(temp);
			temp.clear();
			temp.push_back(n[0]);
			temp.push_back(n[1]);
			temp.push_back(n[2]);
			norIndicies.push_back(temp);
			temp.clear();
			temp.push_back(t[0]);
			temp.push_back(t[1]);
			temp.push_back(t[2]);
			texIndicies.push_back(temp);
			temp.clear();
		}
	}
	in.close();
	
}
void ObjFileLoader::loadVerticesIntoArray(){
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
void ObjFileLoader::loadVerticesInto2DArray(){
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
void ObjFileLoader::loadNormalsInto2DArray(){
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
void ObjFileLoader::loadVerticesArrayToDraw(){
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
void ObjFileLoader::loadNormalsArrayToDraw(){
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
//void ObjFileLoader::clone(){
