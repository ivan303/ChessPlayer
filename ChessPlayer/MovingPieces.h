//#include <stdlib.h>
//#include "GL\glew.h"
//#include "GL\glut.h"

#pragma once

#include "GameModel.h"
#include "Model.h"

#include "Initialization.h"
#include <iostream>
#include <map>
#include <utility>

enum BoardPiece; // "forward declaration" dla swietego spokoju kompilatora

class MovingPieces{
public:
	int speedOfAnimation;
	std::map<std::pair<char,char>,Model*> pieceDictionary;
	//Model *tab[];
	glm::mat4 V;
	int sratatatat;

	bool moveInProgress;
	Initialization initialize;

	MovingPieces();
	void static displayFrame(void);
	void drawPiece(Model*);
	void movePieceGL(char,char,char,char);
	void swapPieceGL(char letter, char digit, BoardPiece newPiece);
	glm::mat4 moveInit(Model*);
	void initDictionary(Model*[4][8]);
};