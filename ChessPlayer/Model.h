#include <string>
#include "ObjFileLoader.h"


enum directions{
	up,
	horizontal,
	down
};
class Model{
public:
	//Model(std::string,int,int,int);
	Model(ObjFileLoader*,int,float,float);
	
	//std::string fileName;
	std::string pieceName;
	ObjFileLoader *object;

	//char position 
	int color; //0-white,1-black
	int speedHorizontal; //iloœæ iteracji
	int speedVertical; 

	float verticalShift;

	int counter;
	bool shifted;
	bool isCaptured;

	enum directions dir;

	float xStartingShift;
	float zStartingShift;

	float xAnimationShift;
	float zAnimationShift;
	
	


	
};