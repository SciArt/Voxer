/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMenu.h
// Desc.: Ekran menu g³ównego
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CMenu_h
#define CMenu_h

#include "GameStatus.h"

// Deklaracje zapowiadaj¹ce
class CCursor;
class CButton;
class CMesh;
class CSwitch;
class CApp;

class CMenu
{
private:
	CApp *app; // WskaŸnik do obiektu nadrzêdnego

public:
	CMenu();
	~CMenu();
	
	bool init( CApp *app ); // Inicjalizacja
	void draw(); // Rysowanie
	GameStatus logic( CCursor *cursor ); // Czêœæ logiczna

	CMesh *background; // T³o
	CMesh *voxer; // Napis VOXER
	
	// Przyciski
	CButton *startgame;
	CButton *highscores;
	CButton *author;
	CButton *exit;

	// Prze³¹czniki
	CSwitch *switch_fs;
	CSwitch *switch_sound;
	CSwitch *switch_music;
};

#endif