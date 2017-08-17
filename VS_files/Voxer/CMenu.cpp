/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMenu.cpp
// Desc.: Ekran menu g³ównego
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CMenu.h"
#include "CMesh.h"
#include "CCursor.h"
#include "CButton.h"
#include "CSwitch.h"
#include "CApp.h"
#include "CWindow.h"
#include "CGraphic.h"
#include "CGame.h"
#include "CHighscores.h"
#include "AppSettings.h"

CMenu::CMenu()
{
	background = NULL;
	voxer = NULL;

	startgame = NULL;
	highscores = NULL;
	author = NULL;
	exit = NULL;

	switch_fs = NULL;
	switch_sound = NULL;
	switch_music = NULL;
}

CMenu::~CMenu()
{
	if( background )
		delete background;
	if( voxer )
		delete voxer;

	if( startgame )
		delete startgame;
	if( highscores )
		delete highscores;
	if( author )
		delete author;
	if( exit )
		delete exit;
}

bool CMenu::init( CApp *app )
{
	this->app = app; // Kopiowanie wskaŸnika na obiekt nadrzêdny

	// Wczytywanie t³a
	background = new CMesh();
	if( !background ) return false;
	if( !background->Load( "Menu/Graphic/background.obj", "Menu/Graphic/background.png" ) )
		return false;

	// Wczytywanie napisu VOXER
	voxer = new CMesh();
	if( !voxer ) return false;
	if( !voxer->Load( "Menu/Graphic/voxer.obj", "Menu/Graphic/voxer.png" ) )
		return false;
	voxer->y = 1.07;

	// Wczytywanie przycisku Start Game
	startgame = new CButton();
	if( !startgame ) return false;
	if( !startgame->Load( "Menu/Graphic/startgame.obj", "Menu/Graphic/startgame1.png" ) )
		return false;
	if( !startgame->LoadTex2( "Menu/Graphic/startgame2.png" ) )
		return false;
	startgame->x = -1.73;
	startgame->y = 0.29;
	startgame->width = 1.314;
	startgame->height = 0.153;

	// Wczytywanie przycisku Highscores
	highscores = new CButton();
	if( !highscores ) return false;
	if( !highscores->Load( "Menu/Graphic/highscores.obj", "Menu/Graphic/highscores1.png" ) )
		return false;
	if( !highscores->LoadTex2( "Menu/Graphic/highscores2.png" ) )
		return false;
	highscores->x = startgame->x;
	highscores->y = startgame->y - 0.5;
	highscores->width = 1.431;
	highscores->height = 0.153;

	// Wczytywanie przycisku Author
	author = new CButton();
	if( !author ) return false;
	if( !author->Load( "Menu/Graphic/author.obj", "Menu/Graphic/author1.png" ) )
		return false;
	if( !author->LoadTex2( "Menu/Graphic/author2.png" ) )
		return false;
	author->x = highscores->x;
	author->y = highscores->y - 0.5;
	author->width = 0.85;
	author->height = 0.145;

	// Wczytywanie przycisku Exit
	exit = new CButton();
	if( !exit ) return false;
	if( !exit->Load( "Menu/Graphic/exit.obj", "Menu/Graphic/exit1.png" ) )
		return false;
	if( !exit->LoadTex2( "Menu/Graphic/exit2.png" ) )
		return false;
	exit->x = author->x;
	exit->y = author->y - 0.5;
	exit->width = 0.472;
	exit->height = 0.142;

	// Wczytywanie prze³¹cznika Fullscreen
	switch_fs = new CSwitch();
	if( !switch_fs )
		return false;
	if( !switch_fs->Load( "Menu/Graphic/switch.obj", 
		"Menu/Graphic/switchon.png", "Menu/Graphic/switchoff.png",
		0.256, 0.256, 1.372 , -0.125, 0.0 ) )
		return false;
	switch_fs->state = app->settings.fullscreen;

	// Wczytywanie prze³¹cznika Sound
	switch_sound = new CSwitch();
	if( !switch_sound )
		return false;
	if( !switch_sound->Load( "Menu/Graphic/switch.obj", 
		"Menu/Graphic/switchon.png", "Menu/Graphic/switchoff.png",
		0.256, 0.256, 1.372 , -0.5, 0.0 ) )
		return false;
	switch_sound->state = true;

	// Wczytywanie prze³¹cznika Music
	switch_music = new CSwitch();
	if( !switch_music )
		return false;
	if( !switch_music->Load( "Menu/Graphic/switch.obj", 
		"Menu/Graphic/switchon.png", "Menu/Graphic/switchoff.png",
		0.256, 0.256, 1.372 , -0.875, 0.0 ) )
		return false;
	switch_music->state = true;

	return true;
}

void CMenu::draw()
{
	background->Draw(); // Rysowanie t³a
	voxer->Draw(); // Rysowanie napisu VOXER

	// Rysowanie przycisków
	startgame->Draw();
	highscores->Draw();
	author->Draw();
	exit->Draw();

	// Rysowanie prze³¹czników
	switch_fs->Draw();
	switch_sound->Draw();
	switch_music->Draw();
}

GameStatus CMenu::logic( CCursor *cursor )
{
	// Obs³uga przycisków

	if( startgame->Logic( cursor ) )
		return INGAME; // Przejœcie do gry

	if( highscores->Logic( cursor ) )
	{
		app->game->highscores->refresh(); // Odœwie¿anie wyników
		return HIGHSCORES; // Przejœcie do ekranu z wynikami
	}

	if( author->Logic( cursor ) )
		return AUTHOR; // Przejœcie do ekranu z info. o autorze

	if( exit->Logic( cursor ) )
		return EXIT; // Wyjœcie z aplikacji

	// Obs³uga prze³¹czników

	if( switch_fs->Logic( cursor ) )
	{
		SDL_DisplayMode mode;	// Tryb ekranu (do pobrania aktualnej rozdzielczoœci)
		SDL_GetCurrentDisplayMode( 0, &mode ); // Pozyskiwanie aktualnego trybu ekranu
		if( switch_fs->state ) // Jeœli przycisk ustawiony na tryb pe³nego ekranu
		{
			// Ustawianie maksymalnej rozdzielczoœci 
			SDL_SetWindowSize( app->window->window, mode.w, mode.h );
			
			// Ustawianie trybu pe³nego ekranu
			SDL_SetWindowFullscreen( app->window->window, SDL_WINDOW_FULLSCREEN );

			// Ustawianie obszaru roboczego i perspektywy
			app->graphic->set_viewport( mode.w, mode.h );

			// Ustawianie przechwytywanie urz¹dzeñ wejœcia na okno
			SDL_SetWindowGrab( app->window->window, SDL_TRUE );
		}
		else
		{
			// Wy³¹czenie trybu pe³nego ekranu
			SDL_SetWindowFullscreen( app->window->window, 0  );	
			
			// Ustawienie maksymalnej rozdzielczoœci
			SDL_SetWindowSize( app->window->window, 4/3 * mode.h, mode.h - (mode.h / 4) ); 
			
			// Ustawienie obszaru roboczego i perspektywy
			app->graphic->set_viewport( 4/3 * mode.h, mode.h - (mode.h / 4) );
			
			// Wyœrodkowanie okna
			SDL_SetWindowPosition( app->window->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED );

			// Ustawianie przechwytywanie urz¹dzeñ wejœcia na okno
			SDL_SetWindowGrab( app->window->window, SDL_TRUE );
		}
	}

	if( switch_sound->Logic( cursor ) )
	{
		if( switch_sound->state )
			Mix_Volume( -1, SDL_MIX_MAXVOLUME ); // Maksymalna g³oœnoœæ efektów dŸwiêkowych
		else
			Mix_Volume( -1, 0 ); // Wyciszenie efektów dŸwiêkowych
	}
	if( switch_music->Logic( cursor ) )
	{
		if( switch_music->state )
			Mix_VolumeMusic( SDL_MIX_MAXVOLUME ); // Maksymalna g³oœnoœæ muzyki
		else
			Mix_VolumeMusic( 0 ); // Wyciszenie muzyki
	}

	return MENU;
}