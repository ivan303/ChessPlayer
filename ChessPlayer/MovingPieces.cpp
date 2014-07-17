#include "stdafx.h"
//#include <Windows.h>
#include "MovingPieces.h"


MovingPieces::MovingPieces(){
	moveInProgress = false;
	V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	/*V = glm::lookAt(
		glm::vec3(4.0f,10.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(1.0f,0.0f,0.0f));*/
	
};

void MovingPieces::drawPiece(Model *piece){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,piece->verticesArrayToDraw);
	glNormalPointer(GL_FLOAT,0,piece->normalsArrayToDraw);
	glDrawArrays(GL_TRIANGLES,0,piece->verticesArrayToDrawSize);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
};

void MovingPieces::movePieceGL(char startLetter, char startDigit, char endLetter, char endDigit){
	std::map<std::pair<char,char>,Model*>::iterator iter;
	glm::mat4 M;
	std::pair<char,char> pieceToMove;
	std::pair<char,char> pieceToCapture;
	pieceToMove.first = startLetter;
	pieceToMove.second = startDigit;
	pieceToCapture.first = endLetter;
	pieceToCapture.second = endDigit;

	Model *modelToMove;

	//rzeczy zwi¹zane z opengl
	/*glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
	glm::mat4 V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);*/
	initialize.init();

	/*float lightPOs[] = {5, 2, 4, 0};
	
	glLoadMatrixf(glm::value_ptr(V));
	glLightfv(GL_LIGHT0,GL_POSITION,lightPOs);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);*/
	initialize.initLight();
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);



	modelToMove = pieceDictionary[pieceToMove];
	
	//transformacje zwi¹zane z animacj¹
	int xAxisShift;
	int zAxisShift;
	float xzAxisShift;
	xAxisShift = endDigit - startDigit;	//iloœæ jednostek przesuniêcia po x
	zAxisShift = endLetter - startLetter; //iloœæ jednostek przesuniêcia po z
	xzAxisShift = sqrt(pow(xAxisShift,2)+pow(zAxisShift,2)); //iloœæ jednostek do przesuniêcia xz
	modelToMove->speedHorizontal = xzAxisShift*modelToMove->speedVertical;
	modelToMove->shifted = true;
	
	while(modelToMove->shifted){

		initialize.init();
		initialize.initLight();
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);
	
		for(iter = pieceDictionary.begin(); iter!=pieceDictionary.end(); iter++){
			if(iter->second != NULL && iter->first != pieceToMove && !(iter->second->isCaptured)){
				M = moveInit(iter->second);
				glLoadMatrixf(glm::value_ptr(V*M));
				if(iter->second->color == 0)
					glColor3d(1.0f,1.0f,1.0f);
				else
					glColor3d(1.0f,0.5f,0.0f);
				drawPiece(iter->second);
			}
		}


		M = moveInit(modelToMove);

		if(modelToMove->dir == up && (modelToMove->counter < modelToMove->speedVertical)){
			M = glm::translate(M,glm::vec3(0.0,(modelToMove->verticalShift/modelToMove->speedVertical)*modelToMove->counter,0.0));
			modelToMove->counter++;
		}
		else if(modelToMove->dir == up && (modelToMove->counter == modelToMove->speedVertical)){
			modelToMove->dir = horizontal;
			M = glm::translate(M,glm::vec3(0.0,(modelToMove->verticalShift/modelToMove->speedVertical)*modelToMove->counter,0.0));
			modelToMove->counter = 0;
		}
		else if(modelToMove->dir == horizontal && (modelToMove->counter < modelToMove->speedHorizontal)){
			M = glm::translate(M,glm::vec3(
				((float)xAxisShift/modelToMove->speedHorizontal)*modelToMove->counter,
				modelToMove->verticalShift,
				((float)zAxisShift/modelToMove->speedHorizontal)*modelToMove->counter));
			modelToMove->counter++;
		}
		else if(modelToMove->dir == horizontal && (modelToMove->counter == modelToMove->speedHorizontal)){
			modelToMove->dir = down;
			M = glm::translate(M,glm::vec3(
				((float)xAxisShift/modelToMove->speedHorizontal)*modelToMove->counter,
				modelToMove->verticalShift,
				((float)zAxisShift/modelToMove->speedHorizontal)*modelToMove->counter));
			modelToMove->counter = 0;
			if(pieceDictionary[pieceToCapture] != NULL){
				pieceDictionary[pieceToCapture]->isCaptured = true;
			}
		}
		else if(modelToMove->dir == down && (modelToMove->counter < modelToMove->speedVertical)){
			M = glm::translate(M,glm::vec3(
				xAxisShift,
				modelToMove->verticalShift-(modelToMove->verticalShift/modelToMove->speedVertical)*modelToMove->counter,
				zAxisShift));
			modelToMove->counter++;
		}
		else if(modelToMove->dir == down && (modelToMove->counter == modelToMove->speedVertical)){
			modelToMove->dir = up;
			M = glm::translate(M,glm::vec3(
				xAxisShift,
				modelToMove->verticalShift-(modelToMove->verticalShift/modelToMove->speedVertical)*modelToMove->counter,
				zAxisShift));
			modelToMove->counter = 0;

			//nadanie nowych wartoœci startowego przesuniêcia
			modelToMove->xStartingShift += xAxisShift;
			modelToMove->zStartingShift += zAxisShift;
			modelToMove->shifted = false;
			moveInProgress = false;

			//aktualizacja s³ownika
			pieceDictionary[pieceToMove] = NULL;
			pieceToMove.first = endLetter;
			pieceToMove.second = endDigit;
			pieceDictionary[pieceToMove] = modelToMove;
		}

		glLoadMatrixf(glm::value_ptr(V*M));
		if(modelToMove->color == 0)
			glColor3d(1.0f,1.0f,1.0f);
		else
			glColor3d(1.0f,0.5f,0.0f);
		drawPiece(modelToMove);
		glutSwapBuffers();
	}
};
glm::mat4 MovingPieces::moveInit(Model *model){
	glm::mat4 M = glm::mat4();
	//transformacje
	M = glm::translate(M,glm::vec3(model->xStartingShift,0.0f,model->zStartingShift));
	return M;
};
void MovingPieces::initDictionary(Model *pieces[4][8]){
	std::pair<char,char> coords;
	for(int i=0; i<8; i++)
		for(int j=0; j<8; j++){
			coords.first = 0x61+i;
			coords.second = 0x31+j;
			pieceDictionary[coords] = NULL;
			
			
			if(coords.second == '7'){ //czarne pionki
				pieceDictionary[coords] = pieces[1][i];
			}
			else if(coords.second == '2'){ //bia³e pionki
				pieceDictionary[coords] = pieces[2][i];
			}
			else if(coords.second == '8'){ //czarne figury
				pieceDictionary[coords] = pieces[0][i];
			}
			else if(coords.second == '1'){ //bia³e figury
				pieceDictionary[coords] = pieces[3][i];
			}
		}
};
void MovingPieces::swapPieceGL(char letter, char digit, BoardPiece newPiece){};
void MovingPieces::displayFrame(void){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 P=glm::perspective(50.0f,1.0f,1.0f,50.0f);
	glm::mat4 V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(P));
	glMatrixMode(GL_MODELVIEW);

	float lightPOs[] = {5, 2, 4, 0};
	
	glLoadMatrixf(glm::value_ptr(V));
	glLightfv(GL_LIGHT0,GL_POSITION,lightPOs);



	glutSwapBuffers();
}