/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CCursor.cpp
// Desc.: Klasa opisuj�ca kursor
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
	speed = 0.002; // Czu�o�� myszki
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
	glDisable( GL_DEPTH_TEST ); // Wy��czenie g��bi

	glTranslated( x, y, 0 ); // Ustawienie pozycji kursora
	glScaled( 0.75, 0.75, 1.0 ); // Przeskalowanie kursora
	if( clicked ) // Je�li LPM wci�ni�ty
		glScaled( 0.8, 0.8, 1.0 ); // Przeskalowanie
	
	if( *game_status == INGAME ) // Je�li status gry to INGAME
		mesh1->Draw(); // Rysuj kursor nr 1
	else // W pozosta�ych przypadkach
	{
		glTranslated( 0.12, -0.12, 0 ); // Ustaw punkt wodz�cy w lewym g�rnym rogu kursora
		mesh2->Draw(); // Rysuj kursor nr 2
	}

	glEnable( GL_DEPTH_TEST ); // W��cz g��bi�
}

void CCursor::logic( CApp *app )
{
	if( app->logic->mouse_release ) // Je�li myszka jest "uwolniona" od sterowania kamer�
	{
		int mPosX, mPosY; // Przesuni�cie
		
		// Pobierz przesuni�cie
		SDL_GetRelativeMouseState( &mPosX, &mPosY );
		
		// Obliczanie nowej pozycji
		x += speed * mPosX;
		y -= speed * mPosY;

		// Utrzymywanie kursora w obr�bie planszy

		if( x > 2.0 )
			x = 2.0;
		if( x < -2.0 )
			x = -2.0;

		if( y > 1.5 )
			y = 1.5;
		if( y < -1.5 )
			y = -1.5;
	}

	// Sprawdzanie czy LPM jest wci�ni�ty

	if( SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1) )
		clicked = true;
	else
		clicked = false;
}