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
Model *boardModel;
ObjFileLoader *tableOfLoadedModels[7];
ObjFileLoader *board;

MovingPieces *piecesMoving;
GameModel *gameModel;

double factor = 1.075;

int licznik = 0;

void displayFrame(void){
	
	piecesMoving->initialize.init();
	piecesMoving->initialize.initLight();
	
		
	piecesMoving->initDraw();
	
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
	if(c==GLUT_KEY_F1){
		/*piecesMoving->V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));*/
		piecesMoving->initialize.P = glm::perspective(20.0f,1.333333f,1.0f,50.0f);
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.8f),
		glm::vec3(4.0f,1.0f,4.8f),
		glm::vec3(0.0f,1.0f,0.0f));
	}
	if(c==GLUT_KEY_F2){
		piecesMoving->initialize.P = glm::perspective(40.0f,1.333333f,1.0f,50.0f);
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(4.85f,12.0f,13.0f),
		glm::vec3(4.85f,0.0f,5.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	}
	if(c==GLUT_KEY_F3){
		piecesMoving->initialize.P = glm::perspective(45.0f,1.333333f,1.0f,50.0f);
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(4.85f,12.0f,5.0f),
		glm::vec3(4.85f,0.0f,5.0f),
		glm::vec3(1.0f,0.0f,0.0f));
	}
	if(c==GLUT_KEY_F4){
		piecesMoving->initialize.P = glm::perspective(40.0f,1.333333f,1.0f,50.0f);
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(4.85f,12.0f,13.0f),
		glm::vec3(4.85f,0.0f,5.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	}
	if(c==GLUT_KEY_F11){
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(-5.0f,1.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	}
	if(c==GLUT_KEY_F12){
		piecesMoving->initialize.V=glm::lookAt(
		glm::vec3(1.0f,6.0f,4.0f),
		glm::vec3(1.0f,0.0f,4.0f),
		glm::vec3(0.0f,0.0f,1.0f));
	}	
		
	displayFrame();

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

	board = new ObjFileLoader("plansza.obj");

	tableOfLoadedModels[0] = new ObjFileLoader("pawn.obj");
	tableOfLoadedModels[1] = new ObjFileLoader("bishop.obj");
	tableOfLoadedModels[2] = new ObjFileLoader("rook.obj");
	tableOfLoadedModels[3] = new ObjFileLoader("queen.obj");
	tableOfLoadedModels[4] = new ObjFileLoader("king.obj");
	tableOfLoadedModels[5] = new ObjFileLoader("knightw.obj");
	tableOfLoadedModels[6] = new ObjFileLoader("knightb.obj");


	boardModel = new Model(board,1,1.0*factor,1.0*factor);

	for(int i=0; i<4; i++)
		for(int j=0; j<8; j++)
			tableOfPieces[i][j] = NULL;
	tableOfPieces[0][0] = new Model(tableOfLoadedModels[2],1,8.0*factor,1.0*factor);
	tableOfPieces[0][1] = new Model(tableOfLoadedModels[6],1,8.0*factor,2.0*factor);
	tableOfPieces[0][2] = new Model(tableOfLoadedModels[1],1,8.0*factor,3.0*factor);
	tableOfPieces[0][3] = new Model(tableOfLoadedModels[3],1,8.0*factor,4.0*factor);
	tableOfPieces[0][4] = new Model(tableOfLoadedModels[4],1,8.0*factor,5.0*factor);
	tableOfPieces[0][5] = new Model(tableOfLoadedModels[1],1,8.0*factor,6.0*factor);
	tableOfPieces[0][6] = new Model(tableOfLoadedModels[6],1,8.0*factor,7.0*factor);
	tableOfPieces[0][7] = new Model(tableOfLoadedModels[2],1,8.0*factor,8.0*factor);
	
	for(int i=0; i<8; i++){
		tableOfPieces[1][i] = new Model(tableOfLoadedModels[0],1,7.0*factor,(i+1)*factor);
		tableOfPieces[2][i] = new Model(tableOfLoadedModels[0],0,2.0*factor,(i+1)*factor);
	}
	//tableOfPieces[1][0] = new Model("pawn.obj",1,7.0,1);
	//tableOfPieces[1][2] = new Model("bishop.obj",1,7.0,3);

	tableOfPieces[3][0] = new Model(tableOfLoadedModels[2],0,1.0*factor,1.0*factor);
	tableOfPieces[3][1] = new Model(tableOfLoadedModels[5],0,1.0*factor,2.0*factor);
	tableOfPieces[3][2] = new Model(tableOfLoadedModels[1],0,1.0*factor,3.0*factor);
	tableOfPieces[3][3] = new Model(tableOfLoadedModels[3],0,1.0*factor,4.0*factor);
	tableOfPieces[3][4] = new Model(tableOfLoadedModels[4],0,1.0*factor,5.0*factor);
	tableOfPieces[3][5] = new Model(tableOfLoadedModels[1],0,1.0*factor,6.0*factor);
	tableOfPieces[3][6] = new Model(tableOfLoadedModels[5],0,1.0*factor,7.0*factor);
	tableOfPieces[3][7] = new Model(tableOfLoadedModels[2],0,1.0*factor,8.0*factor);
	
	piecesMoving = new MovingPieces(tableOfLoadedModels,board);
	piecesMoving->initDictionary(tableOfPieces,boardModel);


	//king = new Model("king.obj");
	//bishop = new Model("bishop.obj");
	//queen = new Model("queen.obj");
	//rook = new Model("rook.obj");
	//pawn = new Model("pawn.obj");
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
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
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();

	
	return 0;
}

