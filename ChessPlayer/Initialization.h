#include <stdlib.h>
#include "GL\glut.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"



class Initialization{
public:
	glm::mat4 P;
	glm::mat4 V;
	float lightPosition[4];
	float secondLightPosition[4];
	
	Initialization();

	void initLight();
	void init();
};