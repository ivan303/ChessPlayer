#include "stdafx.h"
#include "Initialization.h"


Initialization::Initialization(){
	lightPosition[0] = 5;
	lightPosition[1] = 2;
	lightPosition[2] = 4;
	lightPosition[3] = 0;
	P = glm::perspective(50.0f,1.0f,1.0f,50.0f);
	V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));

};

void Initialization::initLight(){
	glLoadMatrixf(glm::value_ptr(V));
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
};

void Initialization::init(){
	glClearColor(0.66,0.66,0.66,1);
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

