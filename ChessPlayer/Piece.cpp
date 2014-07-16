#include "stdafx.h"
//#include <Windows.h>
#include "Piece.h"


Piece::Piece(){
	V = glm::lookAt(
		glm::vec3(-15.0f,15.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(0.0f,1.0f,0.0f));
	/*V = glm::lookAt(
		glm::vec3(4.0f,10.0f,4.0f),
		glm::vec3(4.0f,0.0f,4.0f),
		glm::vec3(1.0f,0.0f,0.0f));*/
};

void Piece::drawPiece(Model *piece){
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,piece->verticesArrayToDraw);
	glNormalPointer(GL_FLOAT,0,piece->normalsArrayToDraw);
	glDrawArrays(GL_TRIANGLES,0,piece->verticesArrayToDrawSize);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
};

void Piece::movePiece(char startLetter, char startDigit, char endLetter, char endDigit){
	std::map<std::pair<char,char>,Model*>::iterator iter;
	glm::mat4 M;
	std::pair<char,char> pieceToMove;
	pieceToMove.first = startLetter;
	pieceToMove.second = startDigit;
	Model *modelToMove;

	//rzeczy zwi¹zane z opengl





	for(iter = pieceDictionary.begin(); iter!=pieceDictionary.end(); iter++){
		if(iter->second != NULL && iter->first != pieceToMove){
			M = moveInit(iter->second);
			glLoadMatrixf(glm::value_ptr(V*M));
			if(iter->second->color == 0)
				glColor3d(1.0f,1.0f,1.0f);
			else
				glColor3d(1.0f,0.5f,0.0f);
			drawPiece(iter->second);
		}
	}



	modelToMove = pieceDictionary[pieceToMove];
	M = moveInit(modelToMove);
	//transformacje zwi¹zane z animacj¹
	int xAxisShift;
	int zAxisShift;
	float xzAxisShift;
	xAxisShift = endDigit - startDigit;	//iloœæ jednostek przesuniêcia po x
	zAxisShift = endLetter - startLetter; //iloœæ jednostek przesuniêcia po z
	xzAxisShift = sqrt(pow(xAxisShift,2)+pow(zAxisShift,2)); //iloœæ jednostek do przesuniêcia xz
	modelToMove->speedHorizontal = xzAxisShift*modelToMove->speedVertical;
	modelToMove->shifted = true;
	
	if(modelToMove->shifted){
		if(modelToMove->dir == up && (modelToMove->counter < modelToMove->speedVertical)){
			M = glm::translate(M,glm::vec3(0.0,(modelToMove->verticalShift/modelToMove->speedVertical)*modelToMove->counter,0.0));
			modelToMove->counter++;
		}
		else if(modelToMove->dir == up && (modelToMove->counter == modelToMove->speedVertical)){
			modelToMove->dir = horizontal;
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
			modelToMove->counter = 0;
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
			modelToMove->counter = 0;

			//nadanie nowych wartoœci startowego przesuniêcia
			modelToMove->xStartingShift += xAxisShift;
			modelToMove->zStartingShift += zAxisShift;
			modelToMove->shifted = false;
		}
	}




	
	
	glLoadMatrixf(glm::value_ptr(V*M));
	if(modelToMove->color == 0)
		glColor3d(1.0f,1.0f,1.0f);
	else
		glColor3d(1.0f,0.5f,0.0f);
	drawPiece(modelToMove);




	
	//std::pair<char,char> para;
	//para.first = 'a';
	//para.second = '1';
	//glm::mat4 MM;// = glm::mat4();
	//MM = moveInit(pieceDictionary[para]);
	////glLoadMatrixf(glm::value_ptr(V**M));
	//glLoadMatrixf(glm::value_ptr(V*MM));
	//drawPiece(pieceDictionary[para]);
	 
};
glm::mat4 Piece::moveInit(Model *model){
	glm::mat4 M = glm::mat4();
	//transformacje
	M = glm::translate(M,glm::vec3(model->xStartingShift,0.0f,model->zStartingShift));
	return M;
};
void Piece::initDictionary(Model *pieces[4][8]){
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
