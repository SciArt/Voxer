/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CCursor.h
// Desc.: Klasa opisuj�ca kursor
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CCursor_h
#define CCursor_h

#include "GameStatus.h"

// Deklaracje zapowiadaj�ce
class CMesh;
class CApp;

class CCursor
{
private:
	CMesh *mesh1; // Model nr 1 kursora
	CMesh *mesh2; // Model nr 2 kursora
public:
	CCursor();
	~CCursor();

	double x, y; // Wsp�rz�dne kursora
	double speed; // Czu�o�� kursora
	bool clicked; // Flaga wci�ni�cia LPM

	bool load( char* file_model, char* file_texture1, char* file_texture2 ); // Wczytywanie kursora

	void logic( CApp *app ); // Obs�uga kursora - obliczanie pozycji
	void draw( GameStatus *game_status ); // Rysowanie kursora

};

#endif