#include "stdafx.h"
//#include <Windows.h>
#include "MovingPieces.h"
#include "tga.h"


GLuint tex;

MovingPieces::MovingPieces(ObjFileLoader *loadedModels[7],ObjFileLoader *board){
	this->loadedModels = loadedModels;
	this->board = board;
	moveInProgress = false;
	factor = 1.1;
	
	
	//initialize.V = glm::lookAt(
	//	//glm::vec3(-15.0f,15.0f,4.0f),
	//	glm::vec3(4.0f,10.0f,10.0f),
	//	glm::vec3(4.0f,0.0f,4.0f),
	//	glm::vec3(0.0f,1.0f,0.0f));
	
	
	
	/*V = glm::lookAt(
		glm::vec3(4.0f,10.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(1.0f,0.0f,0.0f));*/
	
};

void MovingPieces::drawPiece(Model *piece){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,piece->object->verticesArrayToDraw);
	glNormalPointer(GL_FLOAT,0,piece->object->normalsArrayToDraw);
	glDrawArrays(GL_TRIANGLES,0,piece->object->verticesArrayToDrawSize);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
};

void MovingPieces::drawBoard(){
	TGAImg img;
	if (img.Load("plansza.tga") == IMG_OK) {
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D,tex);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, img.GetWidth(), img.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.GetImg());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glEnable(GL_TEXTURE_2D);
	} else {
		cout << "Error loading texture!" << endl;
	}



	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,boardModel->object->verticesArrayToDraw);
	glNormalPointer(GL_FLOAT,0,boardModel->object->normalsArrayToDraw);
	glTexCoordPointer(2, GL_FLOAT, 0, boardModel->object->texturesArrayToDraw);
	glDrawArrays(GL_TRIANGLES,0,boardModel->object->verticesArrayToDrawSize);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

	initialize.init();
	initialize.initLight();
	
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);



	modelToMove = pieceDictionary[pieceToMove];
	
	//transformacje zwi¹zane z animacj¹
	float xAxisShift;
	float zAxisShift;
	float xzAxisShift;
	xAxisShift = (endDigit - startDigit)*factor;	//iloœæ jednostek przesuniêcia po x
	zAxisShift = (endLetter - startLetter)*factor; //iloœæ jednostek przesuniêcia po z
	xzAxisShift = sqrt(pow(xAxisShift,2)+pow(zAxisShift,2)); //iloœæ jednostek do przesuniêcia xz
	modelToMove->speedHorizontal = xzAxisShift*modelToMove->speedVertical;
	modelToMove->shifted = true;
	

	while(modelToMove->shifted){

		initialize.init();
		initialize.initLight();
		glEnable(GL_COLOR_MATERIAL);
		glShadeModel(GL_SMOOTH);

		M = moveInit(boardModel);
		glLoadMatrixf(glm::value_ptr(initialize.V*M));
		glColor3d(0.5f,0.5f,0.5f);
		drawBoard();
	
		for(iter = pieceDictionary.begin(); iter!=pieceDictionary.end(); iter++){
			if(iter->second != NULL && iter->first != pieceToMove && !(iter->second->isCaptured)){
				M = moveInit(iter->second);
				glLoadMatrixf(glm::value_ptr(initialize.V*M));
				if(iter->second->color == 0)
					glColor3d(1.0f,1.0f,1.0f);
				else
					glColor3d(0.0f,0.0f,0.0f);
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
			if(pieceDictionary[pieceToMove] != NULL)
				piecesCaptured.push_back(pieceDictionary[pieceToMove]);
				//alternatywnie mo¿na po prostu usuwaæ
				
			pieceDictionary[pieceToMove] = modelToMove;
		}

		glLoadMatrixf(glm::value_ptr(initialize.V*M));
		if(modelToMove->color == 0)
			glColor3d(1.0f,1.0f,1.0f);
		else
			glColor3d(0.0f,0.0f,0.0f);
		drawPiece(modelToMove);
		glutSwapBuffers();
	}
};
glm::mat4 MovingPieces::moveInit(Model *model){
	glm::mat4 M = glm::mat4();
	//transformacje
	
	M = glm::translate(M,glm::vec3(model->xStartingShift,0.0f,model->zStartingShift));
	/*if(model->color == 1 && model->pieceName == "knight")
		M = glm::rotate(M,90.0f,glm::vec3(0.0f,1.0f,0.0f));*/
	return M;
};

//glm::mat4

void MovingPieces::initDictionary(Model *pieces[4][8], Model *boardModel){
	this->boardModel = boardModel;
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
void MovingPieces::swapPieceGL(char letter, char digit, BoardPiece newPiece){
	std::pair<char,char> destination;
	std::pair<char,char> shift;
	destination.first = letter;
	destination.second = digit;
	//std::map<std::pair<char,char>,Model*>::iterator iter;
	
	//std::list<Model*>::iterator iter;
	Model *pointer;
	bool found = false;

	piecesCaptured.push_back(pieceDictionary[destination]);
	/*iter = piecesCaptured.begin();
	(*iter)->pieceName;*/
	
	//while(!found){
	//	if(newPiece == 'Q' && (*iter)->pieceName == "queen" && (*iter)->color == 1){ //black
	//		//pointer = piecesCaptured.erase(iter);
	//		pointer = piecesCaptured.
	//	}
	shift.first = destination.first - 0x60;
	shift.second = destination.second - 0x30;
	Model *promotedPiece;
	switch(newPiece){
	case WPAWN:
		//tableOfPromotedPieces.push_back(new Model(loadedModels[0],0,shift.second,shift.first));
		promotedPiece = new Model(loadedModels[0],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case WBISHOP:
		promotedPiece = new Model(loadedModels[1],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case WROOK:
		promotedPiece = new Model(loadedModels[2],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case WQUEEN:
		promotedPiece = new Model(loadedModels[3],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case WKING:
		promotedPiece = new Model(loadedModels[4],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case WKNIGHT:
		promotedPiece = new Model(loadedModels[5],0,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BPAWN:
		promotedPiece = new Model(loadedModels[0],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BBISHOP:
		promotedPiece = new Model(loadedModels[1],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BROOK:
		promotedPiece = new Model(loadedModels[2],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BQUEEN:
		promotedPiece = new Model(loadedModels[3],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BKING:
		promotedPiece = new Model(loadedModels[4],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	case BKNIGHT:
		promotedPiece = new Model(loadedModels[6],1,shift.second,shift.first);
		pieceDictionary[destination] = promotedPiece;
		break;
	}

	std::map<std::pair<char,char>,Model*>::iterator iter;
	glm::mat4 M;
	for(iter = pieceDictionary.begin(); iter!=pieceDictionary.end(); iter++){
			if(iter->second != NULL){
				M = moveInit(iter->second);
				glLoadMatrixf(glm::value_ptr(initialize.V*M));
				if(iter->second->color == 0)
					glColor3d(1.0f,1.0f,1.0f);
				else
					glColor3d(0.0f,0.0f,0.0f);
				drawPiece(iter->second);
			}
		}
};
void MovingPieces::displayFrame(void){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 P=glm::perspective(25.0f,1.0f,1.0f,50.0f);
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
void MovingPieces::initDraw(){
	glm::mat4 M;
	std::map<std::pair<char,char>,Model*>::iterator iter;
	
	for(iter = pieceDictionary.begin(); iter!=pieceDictionary.end(); iter++){
			if(iter->second != NULL && !(iter->second->isCaptured)){
				M = moveInit(iter->second);
				glLoadMatrixf(glm::value_ptr(initialize.V*M));
				if(iter->second->color == 0)
					glColor3d(1.0f,1.0f,1.0f);
				else
					glColor3d(0.0f,0.0f,0.0f);
				drawPiece(iter->second);
			}
		}

	M = moveInit(boardModel);
	glLoadMatrixf(glm::value_ptr(initialize.V*M));
	glColor3d(0.5f,0.5f,0.5f);
	drawBoard();

}