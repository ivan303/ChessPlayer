#include <string.h>

#include "GameInfoView.h"
#include "GameBoardView.h"
#include "GameModel.h"


using namespace std;

class GameController{
public:
	GameController();

	void loadGame(string fileName);
	void nextMove();
	void previousMove();
	void jumpToBegin();
	void jumpToEnd();

private:
	GameInfoView gameInfoView;
	GameBoardView gameBoardView;
	GameModel model;


};