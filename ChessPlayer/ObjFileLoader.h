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
	ObjFileLoader();
//private:
	void loadObj(std::string fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textures); 
	void loadIndices(std::string fileName, std::vector<std::vector<int>> &verIndicies, std::vector<std::vector<int>> &norIndicies, std::vector<std::vector<int>> &texIndicies);
};