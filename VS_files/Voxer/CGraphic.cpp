/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGraphic.cpp
// Desc.: Zawiera klas� odpowiedzialn� za cz�� graficzn�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CGraphic.h"
#include "AppSettings.h"
#include "CApp.h"
#include "CGame.h"
#include "CCamera.h"

// Ustawienia �wiate�
GLfloat LightAmbient[]={ 2.0f, 2.0f, 2.0f, 1.0f }; // �wiat�o otoczenia
GLfloat LightDiffuse[]={ 2.0f, 2.0f, 2.0f, 1.0f }; // �wiat�o rozproszone
GLfloat LightPosition[]={ 0.0f, 0.0f, 4.0f, 1.0f }; // Pozycja �wiat�a

// Ustawienia grafiki
void CGraphic::init( AppSettings &settings )
{
	// Model cieniowania
	glShadeModel( GL_FLAT );
 
	// Kolor czyszczenia ekranu (czarny)
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	// Czyszczenie bufora g��bi
	glClearDepth( 1.0f );
 
	// W��czenie testowania g��bi
	glEnable( GL_DEPTH_TEST );
 
    glDepthFunc( GL_LEQUAL );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	// Ustawienie wyg�adzania kraw�dzi
	if( settings.MultiSampleSamples > 0 )
	{
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	
		glEnable(GL_MULTISAMPLE);
	}

	// W��czenie mieszania kolor�w (przezroczysto��)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Ustawienie obszaru rysowania i perspektywy
	set_viewport( settings.src_width, settings.src_height );

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);         // Ustaw �wiat�o otaczaj�ce
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);         // Ustaw �wiat�o rozproszone
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);         // Pozycja �wiat�a

	glEnable(GL_LIGHT1); // W��czenie �wiata�a
}

// Ustawienie obszaru rysowania i perspektywy
void CGraphic::set_viewport( unsigned int width, unsigned int height )
{
    if ( height == 0 ) {
        height = 1;
    }
	
	// Utrzymywanie formatu 4:3

	GLint width_offset = 0; // Odst�p na osi X
	GLint height_offset = 0; // Odst�p na osi Y

	// Je�eli wysoko�� jest wi�ksza ni� powinna
	if( height > (3.0/4.0 * width) )
	{
		height_offset = (unsigned int)( (double)height - ( 3.0/4.0 * width ) ) / 2;
		height = (unsigned int)( 3.0/4.0 * (double)width );
	}
	// Je�eli szeroko�� jest wi�ksza ni� powinna
	else if( width > (4.0/3.0 * height) )
	{
		width_offset = (unsigned int)( width - ( 4.0/3.0 * (double)height ) ) / 2;
		width = (unsigned int)( 4.0/3.0 * (double)height );
	}

	// Ustawienie obszaru rysowania (format 4:3, �rodek ekranu)
	glViewport( width_offset, height_offset, width, height );

	// Zresetowanie macierzy GL_PROJECTION
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( ); 

	// Ustawienie perspektywy, k�t widzenia 70 stopni
	gluPerspective( 70.0f, ( GLfloat )width / ( GLfloat )height, 0.01f, 100.0f );

	// Utawienie i zresetowanie macierzy GL_MODELVIEW
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}

// Rysowanie
void CGraphic::draw()
{
	// Pozycja �wiat�a wzgl�dem kamery
	LightPosition[0] = GLfloat(-app->camera->PosX);
	LightPosition[1] = GLfloat(-app->camera->PosY);
	LightPosition[2] = GLfloat(4.0f - app->camera->PosZ);
	
	// Czyszczenie bufor�w koloru i g��bi
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
	app->camera->UpdateScene(); // Uwzgl�dnienie pozycji i obrotu kamery

	app->game->draw(); // Rysowanie gry
}