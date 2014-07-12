#include <vector>
#include <string>
#include "glm\gtc\type_ptr.hpp"
#include "gl\glut.h"

class ObjFileLoader{
public:
	ObjFileLoader();
//private:
	void loadObj(std::string fileName, std::vector<glm::vec4> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &textures); 
	void loadIndices(std::string fileName, std::vector<std::vector<int>> &verIndicies, std::vector<std::vector<int>> &norIndicies, std::vector<std::vector<int>> &texIndicies);
};