/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGame.h
// Desc.: Klasa opisuj¹ca kursor
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CGame_h
#define CGame_h

#include "GameStatus.h"
#include "CFont.h"
#include "declarations.h"

// Deklaracje zapowiadaj¹ce

class CIngame;
class CMenu;
class CHighscores;
class CAuthor;

class CCursor;
class CApp;

class CGame
{
private:
	std::ostringstream convert;
	CFont FPS_text;
	Mix_Music *music;

public:
	CApp		*app; // WskaŸnik na obiekt app (nie usuwaæ zawartoœci)
	
	CMenu		*menu; // Menu
	CIngame		*ingame; // Ingame
	CCursor		*cursor; // Kursor	
	CHighscores	*highscores; // Highscores
	CAuthor		*author; // Author

	GameStatus game_status; // Status gry	

	CGame();
	~CGame();

	bool init( CApp *App); // Inicjalizacja
	void draw(); // Rysowanie
	bool logic(); // Czêœæ logiczna
};

#endif