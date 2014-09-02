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
//#include "GameModel.h"
#include "MovingPieces.h"


#include <iostream>

#include <vector>


int trans = 0;
bool buttonPressed = false;


Model *king;
Model *bishop;
Model *queen;
Model *rook;
Model *pawn;
Model *knight;

Model *tableOfPieces[4][8];
ObjFileLoader *tableOfLoadedModels[7];

MovingPieces *piecesMoving;
GameModel *gameModel;

int licznik = 0;

void displayFrame(void){
	piecesMoving->initialize.init();
	piecesMoving->initialize.initLight();
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);
		
	piecesMoving->initDraw();

	
	
	
	
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
	if(buttonPressed)
		glutPostRedisplay();


}

void specialKeyDown(int c, int x, int y){
	if(c==GLUT_KEY_UP && !piecesMoving->moveInProgress){
		//buttonPressed = true;
		piecesMoving->moveInProgress = true;
		gameModel->doNextMove();
	}
	if(c==GLUT_KEY_RIGHT){
		/*piecesMoving->V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));*/
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	}
		//if(!piecesMoving->moveInProgress)
		//	//...
		//	gameModel->doNextMove();
	

}

void keyDown(unsigned char c, int x, int y){
	switch(c){
	case '1':
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));
		break;
	case '2':
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));	
		break;
	}
		
}
void specialKeyUp(int c, int x, int y){
	if(c==GLUT_KEY_UP)
		buttonPressed = false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	tableOfLoadedModels[0] = new ObjFileLoader("pawn.obj");
	tableOfLoadedModels[1] = new ObjFileLoader("bishop.obj");
	tableOfLoadedModels[2] = new ObjFileLoader("rook.obj");
	tableOfLoadedModels[3] = new ObjFileLoader("queen.obj");
	tableOfLoadedModels[4] = new ObjFileLoader("king.obj");
	tableOfLoadedModels[5] = new ObjFileLoader("knightw.obj");
	tableOfLoadedModels[6] = new ObjFileLoader("knightb.obj");

	for(int i=0; i<4; i++)
		for(int j=0; j<8; j++)
			tableOfPieces[i][j] = NULL;
	tableOfPieces[0][0] = new Model(tableOfLoadedModels[2],1,8.0,1.0);
	tableOfPieces[0][1] = new Model(tableOfLoadedModels[6],1,8.0,2.0);
	tableOfPieces[0][2] = new Model(tableOfLoadedModels[1],1,8.0,3.0);
	tableOfPieces[0][3] = new Model(tableOfLoadedModels[3],1,8.0,4.0);
	tableOfPieces[0][4] = new Model(tableOfLoadedModels[4],1,8.0,5.0);
	tableOfPieces[0][5] = new Model(tableOfLoadedModels[1],1,8.0,6.0);
	tableOfPieces[0][6] = new Model(tableOfLoadedModels[6],1,8.0,7.0);
	tableOfPieces[0][7] = new Model(tableOfLoadedModels[2],1,8.0,8.0);
	
	for(int i=0; i<8; i++){
		tableOfPieces[1][i] = new Model(tableOfLoadedModels[0],1,7.0,i+1);
		tableOfPieces[2][i] = new Model(tableOfLoadedModels[0],0,2.0,i+1);
	}
	//tableOfPieces[1][0] = new Model("pawn.obj",1,7.0,1);
	//tableOfPieces[1][2] = new Model("bishop.obj",1,7.0,3);

	tableOfPieces[3][0] = new Model(tableOfLoadedModels[2],0,1.0,1.0);
	tableOfPieces[3][1] = new Model(tableOfLoadedModels[5],0,1.0,2.0);
	tableOfPieces[3][2] = new Model(tableOfLoadedModels[1],0,1.0,3.0);
	tableOfPieces[3][3] = new Model(tableOfLoadedModels[3],0,1.0,4.0);
	tableOfPieces[3][4] = new Model(tableOfLoadedModels[4],0,1.0,5.0);
	tableOfPieces[3][5] = new Model(tableOfLoadedModels[1],0,1.0,6.0);
	tableOfPieces[3][6] = new Model(tableOfLoadedModels[5],0,1.0,7.0);
	tableOfPieces[3][7] = new Model(tableOfLoadedModels[2],0,1.0,8.0);
	
	piecesMoving = new MovingPieces(tableOfLoadedModels);
	piecesMoving->initDictionary(tableOfPieces);


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

	/*
	void (*firstPointer)(char,char,char,char);
	firstPointer = (piecesMoving->movePieceGL);//piecesMoving->movePieceGL;
	void (*secondPointer)(char,char,BoardPiece);
	secondPointer = (piecesMoving->swapPieceGL);//piecesMoving->swapPieceGL;

	*/

	//gameModel = new GameModel(firstPointer,secondPointer);
	gameModel = new GameModel(*piecesMoving);
	 
	

	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyDown);

	
	glutDisplayFunc(displayFrame);
	//glutIdleFunc(nextFrame);
	glewInit();


	glutMainLoop();

	
	return 0;
}

