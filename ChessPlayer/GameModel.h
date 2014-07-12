#include <string.h>


#include "Parser\PGNTagList.h"
#include "Parser\PGNMoveList.h"
#include "Parser\PGNGameResult.h"
#include "Parser\PGNGame.h"
#include "Parser\PGNMove.h"


using namespace std;

struct GameInfo{
	pgn::TagList tags;
	pgn::MoveList moves;
	string date;
	string white;
	string black;
	pgn::GameResult result;
};
		


class GameModel{
public:
	GameModel();


	char** getBoard();
	GameInfo getGameInfo();
	pgn::Move getNextMove();
	void loadGame(string fileName);

	void stepNext();
	void stepPrevios();

private:
	GameInfo gameInfo;
	pgn::Game game;
	char board[8][8];
	int nextMoveIndex;

	void updateGameInfoView();
	void updateGameBoardView();



	 
};