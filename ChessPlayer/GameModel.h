#include <string.h>
#include <vector>
#include <map>
#include <utility>

#include <PGNTagList.h>
#include <PGNMoveList.h>
#include <PGNGameResult.h>
#include <PGNGame.h>
#include <PGNGameCollection.h>
#include <PGNMove.h>
  
using namespace std;

typedef struct GameInfo{
	pgn::TagList tags;
	pgn::MoveList moves;
	vector<string> moveStrings;
	string date;
	string white;
	string black;
	pgn::GameResult result;
} GameInfo;

typedef enum BoardPiece {
	EMPTY = '-',
	WPAWN = 'p',
	WKNIGHT = 'n',
	WROOK = 'r',
	WBISHOP = 'b',
	WQUEEN = 'q',
	WKING = 'k',
	BPAWN = 'P',
	BKNIGHT = 'N',
	BROOK = 'R',
	BBISHOP = 'B',
	BQUEEN = 'Q',
	BKING = 'K',
} Piece;

typedef enum Color {
	WHITE,
	BLACK
} Color;

typedef struct MoveInfo {
	string moveStr; // notacja przyjazna
	string algebraicStr; // notacja algebraiczna
	bool isQueensideCastling; // d³uga roszada
	bool isKingsideCastling; // krótka roszada
	bool isCapture; // bicie
	bool isPromotion; // promocja
	bool isCheck; // szach
	bool isMate; // mat
	bool isEnding;	// czy koniec gry
	BoardPiece promoteTo; // na co promowaæ
} MoveInfo;



class GameModel{
public:
	GameModel(void (*drawInGLFunc)(char, char, char, char));
	void loadGame(string fileName);
	void stepNext();
	GameInfo gameInfo;
	map<char, map<char, Piece> > board;
	bool doNextMove();
	vector<pair<char,char>> getPossibleMoveSources(BoardPiece piece, char toLetter, char toDigit, bool isPawnCapture = false);
	void printBoard();
	MoveInfo getNextMove();
private:
	void (*doMoveInGL)(char fromLetter, char fromDigit, char toLetter, char toDigit);
	vector<string>::iterator nextMoveStrIter;
	Color nextMoveColor;
	pgn::GameCollection *games;
	pgn::Game *currentGame;
};