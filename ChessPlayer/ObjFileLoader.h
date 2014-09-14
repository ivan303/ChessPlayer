#include <stdlib.h>
//#include "GL\glew.h"
#include "gl\glut.h"
//#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"


#include <vector>
#include <string>


class ObjFileLoader{
public:
	std::string fileName;
	ObjFileLoader(std::string fileName);
//private:
	void loadObj(std::string fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textures); 
	void loadIndices(std::string fileName, std::vector<std::vector<int>> &verIndicies, std::vector<std::vector<int>> &norIndicies, std::vector<std::vector<int>> &texIndicies);

	std::vector<glm::vec4> v;
	std::vector<glm::vec3> n;
	std::vector<glm::vec2> t;

	std::vector<std::vector<int>> vi;
	std::vector<std::vector<int>> ni;
	std::vector<std::vector<int>> ti;

	float *vertices;
	float **twoDimensionVertices;
	float **twoDimensionNormals;
	float **twoDimensionTextures;
	
	float *verticesArrayToDraw;
	float *normalsArrayToDraw;
	float *texturesArrayToDraw;
	
	int verticesArrayToDrawSize;
	int normalsArrayToDrawSize;
	int texturesArrayToDrawSize;

	void loadVerticesIntoArray();
	
	void loadVerticesInto2DArray();
	void loadNormalsInto2DArray();
	void loadTexturesInto2DArray();

	void loadVerticesArrayToDraw();
	void loadNormalsArrayToDraw();
	void loadTexturesArrayToDraw();

	// clone();




};

