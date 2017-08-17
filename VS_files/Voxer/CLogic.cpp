/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLogic.cpp
// Desc.: Zawiera klas� odpowiedzialn� za cz�� logiczn�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CLogic.h"
#include "CApp.h"

#include "CCamera.h"
#include "CWindow.h"
#include "CGame.h"

#include "CIngame.h"
#include "CTurret.h"
#include "CGameover.h"

void CLogic::DT_Begin()
{
	// Pobieranie czasu dzia�ania programu
	DT_Start = SDL_GetTicks();
}

void CLogic::DT_End()
{
	// Obliczanie up�ywu czasu
	DeltaTime = SDL_GetTicks() - DT_Start;
	
	// Liczenie klatek na sekund� z aktualizacj� co 1 sekund�
	++FPS_Buffer; FPS_ResetTime -= DeltaTime;
	if( FPS_ResetTime <= 0 )
	{
		FPS = FPS_Buffer;
		FPS_Buffer = 0;
		FPS_ResetTime = 1000;
	}
}

const int CLogic::DT_Return()
{
	return DeltaTime;
}

bool CLogic::check_events()
{	
	// Dop�ki s� zdarzenia do odebrania
	while( SDL_PollEvent( &ev ) )
	{
		if( ev.type == SDL_QUIT )
		{
			return true;	// Zamykanie programu
		}

		// Wprowadzanie tekstu
		if( ev.type == SDL_TEXTINPUT )
		{
			// Je�li status gry to GAMEOVER i pierwsza litera tekstu to nie spacja
			if( app->game->game_status == GAMEOVER && ev.text.text[0] != ' ' )
			{
				// Rozszerz nazw� gracza o dodatkow� liter�, max. 16 znak�w
				app->game->ingame->gameover->name += ev.text.text[0];
				if( app->game->ingame->gameover->name.size() > 16 )
					app->game->ingame->gameover->name.resize(16);
			}
		}

		// Wci�ni�cie przycisku
		if( ev.type == SDL_KEYDOWN )
		{
			switch( ev.key.keysym.sym )
			{
				// Je�li wci�ni�tu klawisz ESCAPE:
				// Cofni�cie do poprzedniego ekranu gry
				// Lub wyj�cie z programu
				case SDLK_ESCAPE:
					if( app->game->game_status ==  MENU )
						app->game->game_status = EXIT;
					else
					if( app->game->game_status == INGAME )
					{
						app->game->game_status = MENU;
						Mix_Pause( 0 );
					}
					else
					if( app->game->game_status == SHOP )
						app->game->game_status = INGAME;
					else
					if( app->game->game_status == HIGHSCORES )
						app->game->game_status = MENU;
					else
					if( app->game->game_status == AUTHOR )
						app->game->game_status = MENU;
					break;

				case SDLK_BACKSPACE:
					// Je�li status gry to GAMEOVER i nazwa gracza ma wi�cej ni� 0 liter to usu� 1 liter�
					if( app->game->game_status == GAMEOVER && app->game->ingame->gameover->name.size() > 0)
						app->game->ingame->gameover->name.pop_back();
					break;

				case SDLK_p:
					if( debug_mode ) // Je�li w��czony tryb debugowania
						mouse_release = !mouse_release; // W��czenie/wy��czenie sterowania kamer� za pomoc� myszki
					break;

				case SDLK_o:
					if( debug_mode ) // Je�li w��czony tryb debugowania
					{
						mouse_center = !mouse_center; // W��czenie/wy��czenie p�ynnego sterowania kamer� za pomoc� myszki
						SDL_SetRelativeMouseMode( static_cast<SDL_bool>(mouse_center) ); // W��czenie/wy��czenie trybu relatywnego
					}
					break;

				case SDLK_F1:
					debug_mode = !debug_mode; break; // W��czenie/wy��czenie trybu debugowania (wolnej kamery)

				case SDLK_F2:
					draw_FPS = !draw_FPS; break; // W��czenie/wy��czenie rysowania ilo�ci klatek na sekund�

				case SDLK_F3:
					SDL_GL_SetSwapInterval( !SDL_GL_GetSwapInterval() ); break; // W��czenie wy��czenie synchronizacji pionowej
			}
		}
	}
	
	if( debug_mode )
		CameraControl(); // Sterowanie kamer�

	return false;
}

void CLogic::CameraControl( void )
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	// Ustawianie pr�dko�ci kamery w zale�o�ci od up�ywu czasu
	app->camera->SetSpeed(4.0 * DeltaTime/1000);

	// Poruszanie kamer� za pomoc� klawiatury
	if( keystate[SDL_SCANCODE_W] )
		app->camera->MoveForward();
	if( keystate[SDL_SCANCODE_A] )
		app->camera->MoveLeft();
	if( keystate[SDL_SCANCODE_S] )
		app->camera->MoveBackward();
	if( keystate[SDL_SCANCODE_D] )
		app->camera->MoveRight();
	if( keystate[SDL_SCANCODE_E] )
		app->camera->MoveUp();
	if( keystate[SDL_SCANCODE_Q] )
		app->camera->MoveDown();

	// Obracanie kamer� za pomoc� klawiatury
	if(	keystate[SDL_SCANCODE_RIGHT] )
		app->camera->Rotate( 0.0, 45.0 * DeltaTime/1000, 0.0 );

	if(	keystate[SDL_SCANCODE_LEFT] )
		app->camera->Rotate( 0.0, -45.0 * DeltaTime/1000, 0.0 );	

	if(	keystate[SDL_SCANCODE_UP] )
		app->camera->Rotate(45.0 * DeltaTime/1000, 0.0, 0.0);

	if(	keystate[SDL_SCANCODE_DOWN] )
		app->camera->Rotate(-45.0 * DeltaTime/1000, 0.0, 0.0);

	if(	keystate[SDL_SCANCODE_J] )
		app->camera->Rotate(0.0, 0.0, -45.0 * DeltaTime/1000);

	if(	keystate[SDL_SCANCODE_K] )
		app->camera->Rotate(0.0, 0.0, 45.0 * DeltaTime/1000);

	if( keystate[SDL_SCANCODE_SPACE] )
	{
		app->camera->SetRotate( 0.0, 0.0, 0.0 );
		app->camera->SetPos( 0.0, 0.0, -2.1445 );
	}

	// Obracanie kamer� za pomoc� myszki
	if(!mouse_release)
	{
		int mPosX, mPosY;

		if(mouse_center)
		{
			SDL_GetRelativeMouseState( &mPosX, &mPosY ); // Pobieranie przemieszczenia kursora myszki
			app->camera->Rotate(0.2 * mPosY, 0.2 * mPosX, 0.0); // Ustawianie obrotu
		}
		else
		{
			SDL_GetMouseState( &mPosX, &mPosY ); // Pobieranie wsp�rz�dnych kursora myszki
			const int CenterX = app->window->src_width/2;
			const int CenterY = app->window->src_height/2;
			app->camera->Rotate( 0.4 * DeltaTime/1000 * (mPosY-CenterY), 0.4 * DeltaTime/1000 * (mPosX-CenterX), 0.0); // Ustawianie obrotu
		}
	}
}