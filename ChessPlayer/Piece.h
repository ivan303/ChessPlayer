//#include <stdlib.h>
//#include "GL\glew.h"
//#include "GL\glut.h"




#include "Model.h"
#include <iostream>
#include <map>
#include <utility>

class Piece{
public:
	int speedOfAnimation;
	std::map<std::pair<char,char>,Model*> pieceDictionary;
	//Model *tab[];
	glm::mat4 V;

	Piece();
	void drawPiece(Model*);
	void movePiece(char,char,char,char);
	glm::mat4 moveInit(Model*);
	void initDictionary(Model*[4][8]);
};