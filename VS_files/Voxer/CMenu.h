/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMenu.h
// Desc.: Ekran menu g��wnego
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMenu_h
#define CMenu_h

#include "GameStatus.h"

// Deklaracje zapowiadaj�ce
class CCursor;
class CButton;
class CMesh;
class CSwitch;
class CApp;

class CMenu
{
private:
	CApp *app; // Wska�nik do obiektu nadrz�dnego

public:
	CMenu();
	~CMenu();
	
	bool init( CApp *app ); // Inicjalizacja
	void draw(); // Rysowanie
	GameStatus logic( CCursor *cursor ); // Cz�� logiczna

	CMesh *background; // T�o
	CMesh *voxer; // Napis VOXER
	
	// Przyciski
	CButton *startgame;
	CButton *highscores;
	CButton *author;
	CButton *exit;

	// Prze��czniki
	CSwitch *switch_fs;
	CSwitch *switch_sound;
	CSwitch *switch_music;
};

#endif