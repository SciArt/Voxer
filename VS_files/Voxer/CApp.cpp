/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CApp.cpp
// Desc.: Zawiera podstawow� klas� aplikacji
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CApp.h"
#include "AppSettings.h"

#include "CWindow.h"
#include "CLogic.h"
#include "CCamera.h"
#include "CGraphic.h"

#include "CGame.h"

#include "CFont.h"

CApp::CApp()
{
	// Zerowanie wska�nik�w
	graphic	= NULL;
	logic	= NULL;
	window	= NULL;
	camera	= NULL;

	game	= NULL;
}

CApp::~CApp()
{
	// Czyszczenie pami�ci, usuwanie obiekt�w je�li istniej�
	if( graphic )
		delete graphic;
	if( logic )
		delete logic;
	if( window )
		delete window;
	if( camera )
		delete camera;

	if( game )
		delete game;

	// Wy��czenie miksera d�wi�k�w, zatrzymywanie odtwarzanych d�wi�k�w
	Mix_CloseAudio(); 

	// Usuwanie czcionki
	DestroyFont();
}

bool CApp::init( AppSettings settings )
{
	// Kopiowanie ustawie�
	this->settings = settings;

	// Inicjalizowanie biblioteki SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error (SDL_Init)", SDL_GetError(), NULL);

		return false;
	}

	// W��czanie miksera d�wi�k�w
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 ) == -1 )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Mix_OpenAudio failed", NULL);
		return false;
	}

	// Tworzenie obiektu odpowiedzialnego za cz�� graficzn�
	graphic = new CGraphic(this);
	if( !graphic ) return false;

	// Tworzenie obiektu odpowiedzialnego za cz�� logiczn�
	logic = new CLogic(this);
	if( !logic ) return false;
	
	// Tworzenie obiektu odpowiadaj�cego za obs�ug� okna
	window = new CWindow;
	if( !window ) return false;

	// Tworzenie okna
	if( !window->create( settings ) )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error (window->create)", SDL_GetError(), NULL);
		return false;
	}

	// Konfigurowanie ustawie� graficznych
	graphic->init( settings );

	// Wczytywanie czcionki 
	if( !InitFont( "System/calibrib.ttf", 48 ) )
		return false;

	// Tworzenie obiektu kamery
	camera = new CCamera;
	if( !camera ) return false;
	
	// Ustawianie pozycji kamery
	camera->SetPos( 0.0, 0.0, -2.1445 );

	// Tworzenie obiektu gry w�asciwej
	game = new CGame();
	if( !game ) return false;
	if( !game->init( this ) )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","(game->init)", NULL);
		return false;
	}

	// Ustawianie trybu relatywnego myszki (przechwytywanie ruch�w myszki)
	if( SDL_SetRelativeMouseMode( SDL_TRUE ) != 0 )
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
			"Initializing Error","Cannot set Relative Mouse Mode.", NULL);
		return false;
	}
	
	// Rozpocz�cie wprowadzania tekstu
	SDL_StartTextInput();
	return true;
}

void CApp::run()
{
	// Sprawdzanie zdarze�, 
	// W razie pro�by o zamkni�cie programu, ko�czy p�tle
	while( !logic->check_events() )
	{
		logic->DT_Begin(); // Rozpocz�cie pomiaru up�ywu czasu

		// Obs�uga cz�ci logicznej gry
		// W razie pro�by o zamkni�cie programu, ko�czy p�tle
		if( game->logic() ) break;

		// Rysowanie obrazu w buforze
		graphic->draw();

		// Przerzucenie obrazu z bufora na ekran
		SDL_GL_SwapWindow( window->window );

		logic->DT_End(); // Zako�czenie pomiaru up�ywu czasu
	}
}