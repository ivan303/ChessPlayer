#include "stdafx.h"
#include "Initialization.h"


Initialization::Initialization(){
	lightPosition[0] = 10;
	lightPosition[1] = 10;
	lightPosition[2] = 4;
	lightPosition[3] = 1;

	secondLightPosition[0] = 15;
	secondLightPosition[1] = -10;
	secondLightPosition[2] = 9;
	secondLightPosition[3] = 1;


	P = glm::perspective(20.0f,1.333333f,1.0f,50.0f);
	V=glm::lookAt(
	glm::vec3(-15.0f,15.0f,4.8f),
	glm::vec3(4.0f,1.0f,4.8f),
	glm::vec3(0.0f,1.0f,0.0f));

};

void Initialization::initLight(){
	glLoadMatrixf(glm::value_ptr(V));
	GLfloat mat1[] = {0.4f, 0.4f, 0.4f, 1.0f};
	GLfloat mat2[] = {0.3f, 0.3f, 0.3f, 1.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glLightfv(GL_LIGHT0,GL_SPECULAR,mat1);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,mat1);
	glLightfv(GL_LIGHT0,GL_AMBIENT,mat1);

	glLightfv(GL_LIGHT1,GL_POSITION,lightPosition);
	glLightfv(GL_LIGHT1,GL_SPECULAR,mat2);
	glLightfv(GL_LIGHT1,GL_DIFFUSE,mat2);
	glLightfv(GL_LIGHT1,GL_AMBIENT,mat2);

	
};

void Initialization::init(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*P = glm::perspective(50.0f,1.0f,1.0f,50.0f);
	glm::mat4 V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));*/
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
};

