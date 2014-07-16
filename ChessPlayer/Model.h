#include <string>
#include "ObjFileLoader.h"


enum directions{
	up,
	horizontal,
	down
};
class Model{
public:
	Model(std::string,int,int,int);

	std::string fileName;
	ObjFileLoader *object;

	//char position 
	int color; //0-white,1-black
	int speedHorizontal; //iloœæ iteracji
	int speedVertical; 

	float verticalShift;

	int counter;
	bool shifted;

	enum directions dir;

	float xStartingShift;
	float zStartingShift;

	float xAnimationShift;
	float zAnimationShift;
	
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