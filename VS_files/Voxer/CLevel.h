/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLevel.cpp
// Desc.: Klasa zawieraj¹ca level, struktura zawieraj¹ca obiekt
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLevel_h
#define CLevel_h

#include <vector>

struct CObject
{
	unsigned int type; // Typ obiektu
	unsigned int value; // Wartoœæ (twardoœæ metorytu lub wartoœæ bonusu)
	double speed; // Szybkoœæ
	double size; // Wielkoœæ
	double pos_x; // Pozycja
	double pos_xk; // Pozycja koñcowa
	int delay; // OpóŸnienie
};

class CLevel
{
public:
	unsigned int level_number; // Numer levela
	unsigned int object_number; // Numer obiektu
	CLevel(){level_number = 0; object_number = 0;}
	~CLevel(){}
	bool Load( const char *level_file); // Wczytywanie level'a z pliku
	std::vector<CObject> objects; // Obiekty
};

#endif