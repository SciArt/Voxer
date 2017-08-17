/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CApp.h
// Desc.: Zawiera podstawow� klas� aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CApp_h
#define CApp_h

#include "declarations.h"
#include "AppSettings.h"

// Deklaracje zapowiadaj�ce
class CWindow;
class CCamera;
class CLogic;
class CGraphic;

class CGame;

// Podstawowa klasa aplikacji
class CApp
{
	public:
		CGraphic	*graphic;	// Wska�nik na obiekt grafiki
		CLogic		*logic;		// Wska�nik na obiekt logiki
		CWindow		*window;	// Wska�nik na obiekt okna
		CCamera		*camera;	// Wska�nik na kamer�
		CGame		*game;		// Wska�nik na obiekt gry

		CApp();
		~CApp();
		
		AppSettings settings;	// Ustawienia programu

		// Inicjalizowanie programu
		bool init( AppSettings settings );

		// Wykonywanie programu
		void run();
};

#endif