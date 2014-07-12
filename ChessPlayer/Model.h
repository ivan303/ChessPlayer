#include <string>
#include "ObjFileLoader.h"

class Model{
public:
	Model(std::string fileName);

	std::string fileName;
	ObjFileLoader *object;
	
	std::vector<glm::vec4> v;
	std::vector<glm::vec3> n;
	std::vector<glm::vec2> e;

	std::vector<std::vector<int>> vi;
	std::vector<std::vector<int>> ni;
	std::vector<std::vector<int>> ti;

	float *vertices;
	float **twoDimensionVertices;
	float **twoDimensionNormals;
	float *verticesArrayToDraw;
	float *normalsArrayToDraw;
	int verticesArrayToDrawSize;
	int normalsArrayToDrawSize;

	void loadVerticesIntoArray();
	void loadVerticesInto2DArray();
	void loadNormalsInto2DArray();
	void loadVerticesArrayToDraw();
	void loadNormalsArrayToDraw();
	
};