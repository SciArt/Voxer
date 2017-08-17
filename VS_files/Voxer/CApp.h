/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CApp.h
// Desc.: Zawiera podstawowπ klasÍ aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CApp_h
#define CApp_h

#include "declarations.h"
#include "AppSettings.h"

// Deklaracje zapowiadajπce
class CWindow;
class CCamera;
class CLogic;
class CGraphic;

class CGame;

// Podstawowa klasa aplikacji
class CApp
{
	public:
		CGraphic	*graphic;	// Wskaünik na obiekt grafiki
		CLogic		*logic;		// Wskaünik na obiekt logiki
		CWindow		*window;	// Wskaünik na obiekt okna
		CCamera		*camera;	// Wskaünik na kamerÍ
		CGame		*game;		// Wskaünik na obiekt gry

		CApp();
		~CApp();
		
		AppSettings settings;	// Ustawienia programu

		// Inicjalizowanie programu
		bool init( AppSettings settings );

		// Wykonywanie programu
		void run();
};

#endif