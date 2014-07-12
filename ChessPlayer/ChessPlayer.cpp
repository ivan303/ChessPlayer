// ChessPlayer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <windows.h>

//#include <stdlib.h>
#include "GL\glew.h"

#include "GL\glut.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

#include <vector>
//#include "ObjFileLoader.h"
#include "Model.h"



float speed=0; //360 stopni/s
int lastTime=0;
float angle;
float angle1;

Model *king;
Model *bishop;

void displayFrame(void){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
	glm::mat4 V=glm::lookAt(
		glm::vec3(0.0f,0.0f,-5.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));


	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);



	glm::mat4 M=glm::mat4();
	
	M = glm::rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
	M = glm::translate(M,glm::vec3(0.0f,-1.0f,-2.0f));
	glLoadMatrixf(glm::value_ptr(V*M));

	float lightPOs[] = {0, 70, 70, 0};
	glLightfv(GL_LIGHT0,GL_POSITION,lightPOs);

	//glColor3d(1.0f,0.5f,0.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,king->verticesArrayToDraw);
	glNormalPointer(GL_FLOAT,0,king->normalsArrayToDraw);
	glDrawArrays(GL_TRIANGLES,0,king->verticesArrayToDrawSize);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	/*GLuint bufGeomVertices[2];

	glGenBuffers(1,&(bufGeomVertices[0]));
	glBindBuffer(GL_ARRAY_BUFFER,bufGeomVertices[0]);

	glBufferData(GL_ARRAY_BUFFER,
		geomVertexCount*sizeof(float)*3,
		geomVertices,
		GL_STATIC_DRAW);

	
	glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
	glm::mat4 V=glm::lookAt(
		glm::vec3(0.0f,0.0f,-5.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	glm::mat4 M=glm::mat4();
	glLoadMatrixf(glm::value_ptr(V*M));

	glColor3d(0.0f,1.0f,0.0f);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER,bufGeomVertices[0]);
	glVertexPointer(3,GL_FLOAT,0,NULL);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glDrawArrays(GL_LINE_LOOP,0,geomVertexCount);
	glDisableClientState(GL_VERTEX_ARRAY);*/

	glutSwapBuffers();
}
void nextFrame(void){
	int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	angle+=speed*interval/1000.0;
	angle1+=speed*interval/2000.0;
	if (angle>360) angle-=360;
	if (angle1>360) angle1-=360;
	glutPostRedisplay();
}

void keyDown(int c, int x, int y){
	if(c==GLUT_KEY_RIGHT)
		speed = 360;
	if(c==GLUT_KEY_LEFT)
		speed = -360;
}
void keyUp(int c, int x, int y){
	speed = 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	king = new Model("king.obj");
	//bishop = new Model("bishop.obj");
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Program OpenGL");        
	

	glutSpecialFunc(keyDown);
	glutSpecialUpFunc(keyUp);

	
	glutDisplayFunc(displayFrame);
	glutIdleFunc(nextFrame);
	glewInit();


	glutMainLoop();

	
	return 0;
}

