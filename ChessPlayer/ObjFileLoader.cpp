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

ObjFileLoader::ObjFileLoader() {
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
		printf("%s\n",line);
		
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