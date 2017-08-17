/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLevel.cpp
// Desc.: Klasa zawieraj�ca level, struktura zawieraj�ca obiekt
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CLevel_h
#define CLevel_h

#include <vector>

struct CObject
{
	unsigned int type; // Typ obiektu
	unsigned int value; // Warto�� (twardo�� metorytu lub warto�� bonusu)
	double speed; // Szybko��
	double size; // Wielko��
	double pos_x; // Pozycja
	double pos_xk; // Pozycja ko�cowa
	int delay; // Op�nienie
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