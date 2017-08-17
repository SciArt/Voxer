/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGraphic.cpp
// Desc.: Zawiera klasê odpowiedzialn¹ za czêœæ graficzn¹
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CGraphic.h"
#include "AppSettings.h"
#include "CApp.h"
#include "CGame.h"
#include "CCamera.h"

// Ustawienia œwiate³
GLfloat LightAmbient[]={ 2.0f, 2.0f, 2.0f, 1.0f }; // Œwiat³o otoczenia
GLfloat LightDiffuse[]={ 2.0f, 2.0f, 2.0f, 1.0f }; // Œwiat³o rozproszone
GLfloat LightPosition[]={ 0.0f, 0.0f, 4.0f, 1.0f }; // Pozycja œwiat³a

// Ustawienia grafiki
void CGraphic::init( AppSettings &settings )
{
	// Model cieniowania
	glShadeModel( GL_FLAT );
 
	// Kolor czyszczenia ekranu (czarny)
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	// Czyszczenie bufora g³êbi
	glClearDepth( 1.0f );
 
	// W³¹czenie testowania g³êbi
	glEnable( GL_DEPTH_TEST );
 
    glDepthFunc( GL_LEQUAL );

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	// Ustawienie wyg³adzania krawêdzi
	if( settings.MultiSampleSamples > 0 )
	{
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
	
		glEnable(GL_MULTISAMPLE);
	}

	// W³¹czenie mieszania kolorów (przezroczystoœæ)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Ustawienie obszaru rysowania i perspektywy
	set_viewport( settings.src_width, settings.src_height );

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);         // Ustaw œwiat³o otaczaj¹ce
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);         // Ustaw œwiat³o rozproszone
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);         // Pozycja œwiat³a

	glEnable(GL_LIGHT1); // W³¹czenie œwiata³a
}

// Ustawienie obszaru rysowania i perspektywy
void CGraphic::set_viewport( unsigned int width, unsigned int height )
{
    if ( height == 0 ) {
        height = 1;
    }
	
	// Utrzymywanie formatu 4:3

	GLint width_offset = 0; // Odstêp na osi X
	GLint height_offset = 0; // Odstêp na osi Y

	// Je¿eli wysokoœæ jest wiêksza ni¿ powinna
	if( height > (3.0/4.0 * width) )
	{
		height_offset = (unsigned int)( (double)height - ( 3.0/4.0 * width ) ) / 2;
		height = (unsigned int)( 3.0/4.0 * (double)width );
	}
	// Je¿eli szerokoœæ jest wiêksza ni¿ powinna
	else if( width > (4.0/3.0 * height) )
	{
		width_offset = (unsigned int)( width - ( 4.0/3.0 * (double)height ) ) / 2;
		width = (unsigned int)( 4.0/3.0 * (double)height );
	}

	// Ustawienie obszaru rysowania (format 4:3, œrodek ekranu)
	glViewport( width_offset, height_offset, width, height );

	// Zresetowanie macierzy GL_PROJECTION
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( ); 

	// Ustawienie perspektywy, k¹t widzenia 70 stopni
	gluPerspective( 70.0f, ( GLfloat )width / ( GLfloat )height, 0.01f, 100.0f );

	// Utawienie i zresetowanie macierzy GL_MODELVIEW
	glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
}

// Rysowanie
void CGraphic::draw()
{
	// Pozycja œwiat³a wzglêdem kamery
	LightPosition[0] = GLfloat(-app->camera->PosX);
	LightPosition[1] = GLfloat(-app->camera->PosY);
	LightPosition[2] = GLfloat(4.0f - app->camera->PosZ);
	
	// Czyszczenie buforów koloru i g³êbi
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
	app->camera->UpdateScene(); // Uwzglêdnienie pozycji i obrotu kamery

	app->game->draw(); // Rysowanie gry
}