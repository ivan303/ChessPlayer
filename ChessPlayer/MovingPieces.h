//#include <stdlib.h>
//#include "GL\glew.h"
//#include "GL\glut.h"

#pragma once

#include "GameModel.h"
#include "Model.h"

#include "Initialization.h"
#include "tga.h"
#include <iostream>
#include <map>
#include <utility>
#include <list>

enum BoardPiece; // "forward declaration" dla swietego spokoju kompilatora

class MovingPieces{
public:
	int speedOfAnimation;
	std::map<std::pair<char,char>,Model*> pieceDictionary;
	Model *boardModel;
	int sratatatat;
	std::list<Model*> piecesCaptured;
	float factor;

	TGAImg img;

	bool moveInProgress;
	Initialization initialize;
	std::list<Model*> tableOfPromotedPieces;
	ObjFileLoader **loadedModels;
	ObjFileLoader *board;

	MovingPieces(ObjFileLoader*[7],ObjFileLoader*);
	
	void drawBoard();
	void drawPiece(Model*);
	void movePieceGL(char,char,char,char);
	void swapPieceGL(char letter, char digit, BoardPiece newPiece);
	glm::mat4 moveInit(Model*);
	void initDictionary(Model*[4][8],Model*);
	void initDraw();

	void drawAllPieces(std::pair<char,char> = pair<char,char>());
};