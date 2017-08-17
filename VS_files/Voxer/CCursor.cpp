/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CCursor.cpp
// Desc.: Klasa opisuj¹ca kursor
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "declarations.h"

#include "CCursor.h"
#include "CMesh.h"

#include "CApp.h"
#include "CWindow.h"
#include "CLogic.h"

CCursor::CCursor()
{
	speed = 0.002; // Czu³oœæ myszki
	x = y = 0;
	mesh1 = NULL;
	mesh2 = NULL;
}
CCursor::~CCursor()
{
	if(mesh1) delete mesh1;
	if(mesh2) delete mesh2;
}

bool CCursor::load( char* file_model, char* file_texture1, char* file_texture2 )
{
	// Wczytywanie modelu kursora nr 1
	mesh1 = new CMesh;
	if( !mesh1 ) return false;
	if( !mesh1->Load( file_model, file_texture1 ) )	return false;

	// Wczytywanie modelu kursora nr 2
	mesh2 = new CMesh;
	if( !mesh2 ) return false;
	if( !mesh2->Load( file_model, file_texture2 ) ) return false;

	return true;
}

void CCursor::draw( GameStatus *game_status )
{
	glDisable( GL_DEPTH_TEST ); // Wy³¹czenie g³êbi

	glTranslated( x, y, 0 ); // Ustawienie pozycji kursora
	glScaled( 0.75, 0.75, 1.0 ); // Przeskalowanie kursora
	if( clicked ) // Jeœli LPM wciœniêty
		glScaled( 0.8, 0.8, 1.0 ); // Przeskalowanie
	
	if( *game_status == INGAME ) // Jeœli status gry to INGAME
		mesh1->Draw(); // Rysuj kursor nr 1
	else // W pozosta³ych przypadkach
	{
		glTranslated( 0.12, -0.12, 0 ); // Ustaw punkt wodz¹cy w lewym górnym rogu kursora
		mesh2->Draw(); // Rysuj kursor nr 2
	}

	glEnable( GL_DEPTH_TEST ); // W³¹cz g³êbiê
}

void CCursor::logic( CApp *app )
{
	if( app->logic->mouse_release ) // Jeœli myszka jest "uwolniona" od sterowania kamer¹
	{
		int mPosX, mPosY; // Przesuniêcie
		
		// Pobierz przesuniêcie
		SDL_GetRelativeMouseState( &mPosX, &mPosY );
		
		// Obliczanie nowej pozycji
		x += speed * mPosX;
		y -= speed * mPosY;

		// Utrzymywanie kursora w obrêbie planszy

		if( x > 2.0 )
			x = 2.0;
		if( x < -2.0 )
			x = -2.0;

		if( y > 1.5 )
			y = 1.5;
		if( y < -1.5 )
			y = -1.5;
	}

	// Sprawdzanie czy LPM jest wciœniêty

	if( SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1) )
		clicked = true;
	else
		clicked = false;
}