// ChessPlayer.cpp : Defines the entry point for the console application.
//

//#pragma once
#include "stdafx.h"
#include <windows.h>

#include <stdlib.h>

//#include <cstdlib>
#include "GL\glew.h"
#include "GL\glut.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "Piece.h"

#include <iostream>

#include <vector>

//#include "Initialization.h"

//Initialization inits;

float speed=0; //360 stopni/s
int lastTime=0;
float angle;
float angle1;

//struct directions{
//	int up = 0;
//	int right = 1;
//	int down = 2;
//	int left = 3;
//}directions;
//enum directions{
//	up,
//	right,
//	down,
//	left
//};

int trans = 0;
//enum directions dir = up;
//int dir = directions.up;
bool buttonPressed = false;


Model *king;
Model *bishop;
Model *queen;
Model *rook;
Model *pawn;
Model *knight;

Model *tableOfPieces[4][8];

Piece piece;

void displayFrame(void){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
	
	glm::mat4 V=glm::lookAt(
		glm::vec3(0.0f,0.0f,-10.0f),
		glm::vec3(0.0f,0.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f));


	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);
	//inits.init();



	float lightPOs[] = {5, 2, 4, 0};
	
	glLoadMatrixf(glm::value_ptr(V));
	glLightfv(GL_LIGHT0,GL_POSITION,lightPOs);

	//glm::mat4 M=glm::mat4();
	/*
	
	
	if(dir == up && trans < 1000){
		M = glm::translate(M,glm::vec3(0.0f,trans/1000.f,0.0f));
		trans += 1;
	}
	else if(dir == up && trans == 1000){
		dir = right;
		trans = 0;
	}
	else if(dir == right && trans > -2000){
		M = glm::translate(M,glm::vec3(trans/1000.f,1.0f,0.0f));
		trans -= 1;
	}
	else if(dir == right && trans == -2000){
		dir = down;
		trans = 0;
	}
	else if(dir == down && trans < 1000){
		M = glm::translate(M,glm::vec3(-2.0f,1.0f-trans/1000.f,0.0f));
		trans += 1;
	}
	else{
		M = glm::translate(M,glm::vec3(-2.0f,0.0f,0.0f));
	}*/
	
	
	
	//glLoadMatrixf(glm::value_ptr(V*M));
	
	
	piece.movePiece('a','7','b','6');

	//glColor3d(1.0f,0.5f,0.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
	
	//piece.drawPiece(tableOfPieces[3][0]);
	

	//próba drugiego modelu
	//M=glm::mat4();
	//
	//M = glm::rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
	//M = glm::translate(M,glm::vec3(1.0f,0.0f,0.0f));
	//glLoadMatrixf(glm::value_ptr(V*M));

	//piece.drawPiece(king);


	//M=glm::mat4();
	//
	//M = glm::rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
	//M = glm::translate(M,glm::vec3(-1.0f,0.0f,0.0f));
	//glLoadMatrixf(glm::value_ptr(V*M));

	//piece.drawPiece(bishop);

	//M=glm::mat4();
	//
	//M = glm::rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
	//M = glm::translate(M,glm::vec3(2.0f,0.0f,0.0f));
	//glLoadMatrixf(glm::value_ptr(V*M));

	//
	//piece.drawPiece(rook);

	//M=glm::mat4();
	//
	//M = glm::rotate(M,angle,glm::vec3(0.0f,1.0f,0.0f));
	//M = glm::translate(M,glm::vec3(-2.0f,0.0f,0.0f));
	//glLoadMatrixf(glm::value_ptr(V*M));

	//
	//piece.drawPiece(pawn);



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
	/*int actTime=glutGet(GLUT_ELAPSED_TIME);
	int interval=actTime-lastTime;
	lastTime=actTime;
	angle+=speed*interval/1000.0;
	angle1+=speed*interval/2000.0;
	if (angle>360) angle-=360;
	if (angle1>360) angle1-=360;*/
	if(buttonPressed)
		glutPostRedisplay();


}

void keyDown(int c, int x, int y){
	if(c==GLUT_KEY_UP)
		buttonPressed = true;
	/*if(c==GLUT_KEY_LEFT)
		speed = -360;*/

}
void keyUp(int c, int x, int y){
	/*speed = 0;*/
	if(c==GLUT_KEY_UP)
		buttonPressed = false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	for(int i=0; i<4; i++)
		for(int j=0; j<8; j++)
			tableOfPieces[i][j] = NULL;
	/*tableOfPieces[0][0] = new Model("rook.obj",1,8.0,1.0);
	tableOfPieces[0][1] = new Model("rook.obj",1,8.0,2.0);
	tableOfPieces[0][2] = new Model("bishop.obj",1,8.0,3.0);
	tableOfPieces[0][3] = new Model("queen.obj",1,8.0,4.0);
	tableOfPieces[0][4] = new Model("king.obj",1,8.0,5.0);
	tableOfPieces[0][5] = new Model("bishop.obj",1,8.0,6.0);
	tableOfPieces[0][6] = new Model("rook.obj",1,8.0,7.0);
	tableOfPieces[0][7] = new Model("rook.obj",1,8.0,8.0);*/
	
	//for(int i=0; i<8; i++){
		//tableOfPieces[1][i] = new Model("pawn.obj",1,7.0,i+1);
		//tableOfPieces[2][i] = new Model("pawn.obj",0,2.0,i+1);
	//}
	tableOfPieces[1][0] = new Model("pawn.obj",1,7.0,1);

	/*tableOfPieces[3][0] = new Model("rook.obj",0,1.0,1.0);
	tableOfPieces[3][1] = new Model("rook.obj",0,1.0,2.0);
	tableOfPieces[3][2] = new Model("bishop.obj",0,1.0,3.0);
	tableOfPieces[3][3] = new Model("queen.obj",0,1.0,4.0);
	tableOfPieces[3][4] = new Model("king.obj",0,1.0,5.0);
	tableOfPieces[3][5] = new Model("bishop.obj",0,1.0,6.0);
	tableOfPieces[3][6] = new Model("rook.obj",0,1.0,7.0);
	tableOfPieces[3][7] = new Model("rook.obj",0,1.0,8.0);*/
	
	piece.initDictionary(tableOfPieces);

	//king = new Model("king.obj");
	//bishop = new Model("bishop.obj");
	//queen = new Model("queen.obj");
	//rook = new Model("rook.obj");
	//pawn = new Model("pawn.obj");
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

