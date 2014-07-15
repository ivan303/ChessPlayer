#include "stdafx.h"
#include "GameModel.h"

#include <fstream>
#include <iostream>

/*
TODO:
Zaimplementowaæ promocje
Zaimplementowaæ bicie en passant
*/

GameModel::GameModel(void (*drawInGLFunc)(char, char, char, char)) {
	games = new pgn::GameCollection();
	loadGame("C:/games.pgn"); // tymczasowo
	doMoveInGL = drawInGLFunc;
}

void GameModel::loadGame(string filename) {
	try {
		ifstream pgnfile(filename);
		pgnfile >> *games;
	}
	catch (exception &e) {
		std::cerr << e.what();
	}
	currentGame = &*(games->begin()); // tylko pierwsza gra
	gameInfo.moves = currentGame->moves();
	gameInfo.result = currentGame->result();
	gameInfo.tags = currentGame->tags();
	gameInfo.white = currentGame->white();
	gameInfo.black = currentGame->black();
	gameInfo.date = currentGame->date();

	gameInfo.moveStrings.clear();
	for (pgn::MoveList::iterator it = gameInfo.moves.begin(); it != gameInfo.moves.end(); it++) {
		pgn::Move move = *it;

		string whiteMoveStr = "";
		whiteMoveStr += move.white().str();
		gameInfo.moveStrings.push_back(whiteMoveStr);

		string blackMoveStr = "";
		blackMoveStr += move.black().str();
		gameInfo.moveStrings.push_back(blackMoveStr);

	}

	nextMoveStrIter = gameInfo.moveStrings.begin();
	nextMoveColor = WHITE;

	board['a']['8'] = BROOK;
	board['b']['8'] = BKNIGHT;
	board['c']['8'] = BBISHOP;
	board['d']['8'] = BQUEEN;
	board['e']['8'] = BKING;
	board['f']['8'] = BBISHOP;
	board['g']['8'] = BKNIGHT;
	board['h']['8'] = BROOK;
	board['a']['1'] = WROOK;
	board['b']['1'] = WKNIGHT;
	board['c']['1'] = WBISHOP;
	board['d']['1'] = WQUEEN;
	board['e']['1'] = WKING;
	board['f']['1'] = WBISHOP;
	board['g']['1'] = WKNIGHT;
	board['h']['1'] = WROOK;

	board['a']['7'] = BPAWN;
	board['b']['7'] = BPAWN;
	board['c']['7'] = BPAWN;
	board['d']['7'] = BPAWN;
	board['e']['7'] = BPAWN;
	board['f']['7'] = BPAWN;
	board['g']['7'] = BPAWN;
	board['h']['7'] = BPAWN;

	board['a']['2'] = WPAWN;
	board['b']['2'] = WPAWN;
	board['c']['2'] = WPAWN;
	board['d']['2'] = WPAWN;
	board['e']['2'] = WPAWN;
	board['f']['2'] = WPAWN;
	board['g']['2'] = WPAWN;
	board['h']['2'] = WPAWN;

	board['a']['3'] = EMPTY;
	board['b']['3'] = EMPTY;
	board['c']['3'] = EMPTY;
	board['d']['3'] = EMPTY;
	board['e']['3'] = EMPTY;
	board['f']['3'] = EMPTY;
	board['g']['3'] = EMPTY;
	board['h']['3'] = EMPTY;

	board['a']['4'] = EMPTY;
	board['b']['4'] = EMPTY;
	board['c']['4'] = EMPTY;
	board['d']['4'] = EMPTY;
	board['e']['4'] = EMPTY;
	board['f']['4'] = EMPTY;
	board['g']['4'] = EMPTY;
	board['h']['4'] = EMPTY;

	board['a']['5'] = EMPTY;
	board['b']['5'] = EMPTY;
	board['c']['5'] = EMPTY;
	board['d']['5'] = EMPTY;
	board['e']['5'] = EMPTY;
	board['f']['5'] = EMPTY;
	board['g']['5'] = EMPTY;
	board['h']['5'] = EMPTY;

	board['a']['6'] = EMPTY;
	board['b']['6'] = EMPTY;
	board['c']['6'] = EMPTY;
	board['d']['6'] = EMPTY;
	board['e']['6'] = EMPTY;
	board['f']['6'] = EMPTY;
	board['g']['6'] = EMPTY;
	board['h']['6'] = EMPTY;



}

vector<pair<char,char>> GameModel::getPossibleMoveSources(BoardPiece piece, char toLetter, char toDigit, bool isPawnCapture) {
	vector<pair<char,char>> fromCoordsVector;
	switch (piece) {
	case WPAWN:
		if (!isPawnCapture) {
			fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit-1));
			if (toDigit == '4') fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit-2));
		}
		else {
			fromCoordsVector.push_back(pair<char,char>(toLetter-1, toDigit-1));
			fromCoordsVector.push_back(pair<char,char>(toLetter+1, toDigit-1));
		}

		break;
	case BPAWN:
		if (!isPawnCapture) {
			fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit+1));
			if (toDigit == '5') fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit+2));
		}
		else {
			fromCoordsVector.push_back(pair<char,char>(toLetter-1, toDigit+1));
			fromCoordsVector.push_back(pair<char,char>(toLetter+1, toDigit+1));
		}
		break;
	case WROOK: case BROOK:
		for (char letter = 'a'; letter <= 'h'; letter++) {
			if (letter != toLetter) fromCoordsVector.push_back(pair<char,char>(letter, toDigit));
		}

		for (char digit = '1'; digit <= '8'; digit++) {
			if (digit != toDigit) fromCoordsVector.push_back(pair<char,char>(toLetter, digit));
		}

		break;
	case WBISHOP: case BBISHOP:
		for (char letter=toLetter+1, digit=toDigit+1; letter<='h' && digit<='8'; letter++, digit++) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter-1, digit=toDigit-1; letter>='a' && digit>='1'; letter--, digit--) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter+1, digit=toDigit-1; letter<='h' && digit<='8'; letter++, digit--) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter-1, digit=toDigit+1; letter>='a' && digit>='1'; letter--, digit++) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		break;
	case WKNIGHT: case BKNIGHT:
		fromCoordsVector.push_back(pair<char,char>(toLetter-1, toDigit-2));
		fromCoordsVector.push_back(pair<char,char>(toLetter-1, toDigit+2));
		fromCoordsVector.push_back(pair<char,char>(toLetter+1, toDigit-2));
		fromCoordsVector.push_back(pair<char,char>(toLetter+1, toDigit+2));
		fromCoordsVector.push_back(pair<char,char>(toLetter-2, toDigit-1));
		fromCoordsVector.push_back(pair<char,char>(toLetter-2, toDigit+1));
		fromCoordsVector.push_back(pair<char,char>(toLetter+2, toDigit-1));
		fromCoordsVector.push_back(pair<char,char>(toLetter+2, toDigit+1));
		break;
	case WQUEEN: case BQUEEN:
		for (char letter=toLetter+1, digit=toDigit+1; letter<='h' && digit<='8'; letter++, digit++) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter-1, digit=toDigit-1; letter>='a' && digit>='1'; letter--, digit--) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter+1, digit=toDigit-1; letter<='h' && digit<='8'; letter++, digit--) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter=toLetter-1, digit=toDigit+1; letter>='a' && digit>='1'; letter--, digit++) {
			fromCoordsVector.push_back(pair<char,char>(letter, digit));
		}
		for (char letter = 'a'; letter <= 'h'; letter++) {
			if (letter != toLetter) fromCoordsVector.push_back(pair<char,char>(letter, toDigit));
		}
		for (char digit = '1'; digit <= '8'; digit++) {
			if (digit != toDigit) fromCoordsVector.push_back(pair<char,char>(toLetter, digit));
		}
		break;
	case WKING: case BKING:
		fromCoordsVector.push_back(pair<char,char>(toLetter-1,toDigit-1));
		fromCoordsVector.push_back(pair<char,char>(toLetter-1,toDigit));
		fromCoordsVector.push_back(pair<char,char>(toLetter-1,toDigit+1));
		fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit-1));
		fromCoordsVector.push_back(pair<char,char>(toLetter,toDigit+1));
		fromCoordsVector.push_back(pair<char,char>(toLetter+1,toDigit-1));
		fromCoordsVector.push_back(pair<char,char>(toLetter+1,toDigit));
		fromCoordsVector.push_back(pair<char,char>(toLetter+1,toDigit+1));
		break;
	}
	// tutaj trzeba wyczyscic fromCoordsVector z nieprawidlowych koordynat tj. poza plansz¹
	vector<pair<char,char>> tmp;
	for (int i=0; i<fromCoordsVector.size(); i++) {
		if (!(fromCoordsVector[i].first < 'a' || fromCoordsVector[i].first > 'h' || fromCoordsVector[i].second < '1' || fromCoordsVector[i].second > '8')) {
			tmp.push_back(fromCoordsVector[i]);
		}
	}
	return tmp;
}

MoveInfo GameModel::getNextMove() {
	MoveInfo moveInfo;
	moveInfo.isEnding = false;

	if (nextMoveStrIter == gameInfo.moveStrings.end()) {
		moveInfo.isEnding = true;
		return moveInfo;
	}

	bool isCapture = false;
	bool isPromotion = false;
	bool isSmallCastling = false;
	bool isLargeCastling = false;
	bool isCheck = false;
	bool isCheckMate = false;
	char fromLetter, fromDigit, toLetter, toDigit;
	char promoteTo = 0;
	string moveStr = *nextMoveStrIter;
	moveInfo.algebraicStr = moveStr;
	Color color = nextMoveColor;

	// sprawdzenie specjalnych flag ruchu i wywalenie zbêdnych informacji
	if (moveStr.find('x') != string::npos) { // mamy bicie
		isCapture = true;
		moveStr.erase(moveStr.begin() + moveStr.find('x'));
	}

	if (moveStr.find('+') != string::npos) { // szach
		isCheck = true;
		moveStr.erase(moveStr.begin() + moveStr.find('+'));
	}

	if (moveStr.find('#') != string::npos) { // szach mat
		isCheckMate = true;
		moveStr.erase(moveStr.begin() + moveStr.find('#'));
	}

	if (moveStr.find('=') != string::npos) { // mamy promocjê
		isPromotion = true;
		moveStr.erase(moveStr.begin() + moveStr.find('='));
		promoteTo = moveStr[moveStr.size()-1];
		moveStr.erase(moveStr.begin() + moveStr.find(promoteTo));
	}




	if (moveStr[0] == 'O') { // roszada
		if (moveStr.size() == 3) isSmallCastling = true;
		else isLargeCastling = true;
	}

	BoardPiece piece;
	if (color == WHITE) {
		switch(moveStr[0]) {
		case 'K': piece = WKING; break;
		case 'N': piece = WKNIGHT; break;
		case 'Q': piece = WQUEEN; break;
		case 'B': piece = WBISHOP; break;
		case 'R': piece = WROOK; break;
		default: piece = WPAWN; break;
		}
	} else if (color == BLACK) {
		switch(moveStr[0]) {
		case 'K': piece = BKING; break;
		case 'N': piece = BKNIGHT; break;
		case 'Q': piece = BQUEEN; break;
		case 'B': piece = BBISHOP; break;
		case 'R': piece = BROOK; break;
		default: piece = BPAWN; break;
		}
	}

	if (moveStr[0] == 'N' || moveStr[0] == 'K' || moveStr[0] == 'Q' || moveStr[0] == 'R' || moveStr[0] == 'B') {
		moveStr.erase(moveStr.begin());
	}

	if (!isSmallCastling && !isLargeCastling) { // nie roszada
		toLetter = moveStr[moveStr.size()-2];
		toDigit = moveStr[moveStr.size()-1];
		vector<pair<char,char>> possibleFrom = getPossibleMoveSources(piece, toLetter, toDigit, isCapture);
		for (vector<pair<char,char>>::iterator it=possibleFrom.begin(); it!=possibleFrom.end(); it++) {
			char letter = it->first;
			char digit = it->second;
			char specifier = 0;
			if (moveStr.size() == 3) specifier = moveStr[0];
			if (board[letter][digit] == piece) {
				if (!specifier || ((specifier >= 'a' && specifier <= 'h' && letter == specifier) || (specifier >= '1' && specifier <= '8' && digit == specifier))) {
					fromDigit = digit;
					fromLetter = letter;
					break;
				}
			}
		}

		string ret = "";
		ret += fromLetter;
		ret += fromDigit;
		ret += toLetter;
		ret += toDigit;
		moveInfo.moveStr = ret;
		//doMoveInGL(fromLetter, fromDigit, toLetter, toDigit);
	}
	else { // roszada
		//cout << moveStr << endl;
		if (isLargeCastling) {
			moveInfo.moveStr = "O-O-O";
		}
		else if (isSmallCastling) {
			moveInfo.moveStr = "O-O";
		}
	}
	moveInfo.isCapture = isCapture;
	moveInfo.isCheck = isCheck;
	moveInfo.isKingsideCastling = isSmallCastling;
	moveInfo.isQueensideCastling = isLargeCastling;
	moveInfo.isMate = isCheckMate;
	moveInfo.isPromotion = isPromotion;
	if (isPromotion) {
		if (promoteTo == 'q') if (color == WHITE) moveInfo.promoteTo = WQUEEN; else moveInfo.promoteTo = BQUEEN;
		else if (promoteTo == 'n') if (color == WHITE) moveInfo.promoteTo = WKNIGHT; else moveInfo.promoteTo = BKNIGHT;
		else if (promoteTo == 'r') if (color == WHITE) moveInfo.promoteTo = WROOK; else moveInfo.promoteTo = BROOK;
		else if (promoteTo == 'b') if (color == WHITE) moveInfo.promoteTo = WBISHOP; else moveInfo.promoteTo = BBISHOP;
		//moveInfo.promoteTo = 
	}

	return moveInfo;
}


bool GameModel::doNextMove() {
	MoveInfo nextMove = getNextMove();
	string nextMoveStr = nextMove.moveStr;
	if (nextMove.isEnding)  return false;
	Color color = nextMoveColor;

	if (nextMove.isQueensideCastling) {
		if (color == WHITE) {
			board['c']['1'] = board['e']['1'];
			board['e']['1'] = EMPTY;
			board['d']['1'] = board['a']['1'];
			board['a']['1'] = EMPTY;
		}
		else if (color == BLACK) {
			board['c']['8'] = board['e']['8'];
			board['e']['8'] = EMPTY;
			board['d']['8'] = board['a']['8'];
			board['a']['8'] = EMPTY;
		}
	}
	else if (nextMove.isKingsideCastling) {
		if (color == WHITE) {
			board['f']['1'] = board['h']['1'];
			board['h']['1'] = EMPTY;
			board['g']['1'] = board['e']['1'];
			board['e']['1'] = EMPTY;
		}
		else if (color == BLACK) {
			board['f']['8'] = board['h']['8'];
			board['h']['8'] = EMPTY;
			board['g']['8'] = board['e']['8'];
			board['e']['8'] = EMPTY;
		}
	}
	else {
		char
			fromLetter = nextMoveStr[0],
			fromDigit = nextMoveStr[1],
			toLetter = nextMoveStr[2],
			toDigit = nextMoveStr[3];
		board[toLetter][toDigit] = board[fromLetter][fromDigit];
		board[fromLetter][fromDigit] = EMPTY;
	}


	if (nextMoveColor == WHITE) nextMoveColor = BLACK;
	else nextMoveColor = WHITE;
	++nextMoveStrIter;
	return true;
}

void GameModel::printBoard() {
	cout << "   A B C D E F G H" << endl << endl;
	for (char i = '8'; i >= '1'; i--) {
		cout << i << ' ' << ' ';
		for (char j = 'a'; j <= 'h'; j++) {
			printf_s("%c ", board[j][i]);
		}
		cout << endl;
	}cout << endl;
}
