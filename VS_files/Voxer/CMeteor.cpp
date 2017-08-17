/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CMeteor.cpp
// Desc.: Klasa opisuj¹ca meteoroid
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CMeteor.h"
#include "CMesh.h"
#include <sstream>

#include "declarations.h"

#define PI 3.14159265359

CMeteor::CMeteor()
{
	z = 0.0;
	rotate = 0.0;
	scale_z = 1.0;
	alpha = 1.0;
}

CMeteor::~CMeteor()
{
}

void CMeteor::load( CMesh *mesh, unsigned int lives, double speed, double size, double pos_x, double pos_xk  )
{
	this->mesh = mesh; // Model
	this->size = size; // Rozmiar
	this->radius = 0.25 * 0.9 * 0.65 * size; // Obliczanie promienia
	this->y = 1.5 + this->radius; // Wysokoœc pocz¹tkowa
	this->x = pos_x; // Pozycja pocz¹tkowa
	this->xk = pos_xk; // Pozycja koñcowa
	rotate_z = atan((xk-x)/(y+1.2)); // Obrót na osi Z
	this->base_lives = lives; // Iloœæ ¿yæ bazowych
	this->lives = lives; // Iloœæ ¿yæ aktualnych
	this->speed = speed; // Szybkoœæ
}

void CMeteor::draw()
{
	glPushMatrix();
		// Ustawienia pozycji i obrotu meteoroidu
		glTranslated( x, y, z );
		glScaled( size, size, size );
		glScaled( radius/0.25 * (1 + ((1-scale_z)*1.05)), radius/0.25 * (1 + ((1-scale_z)*0.5)), radius/0.25 * scale_z );
		glRotated( rotate_z * 180.0 / PI, 0.0, 0.0, 1.0 );
		glRotated( rotate, 1.0, 0.0, 0.0 );		

		// Rysowanie podstawowego meteoroidu, jeœli niezniszczony
		if( lives != 0 )
			mesh->Draw();

		// Rysowanie pó³przezroczystego zabarwionego meteoroidu
		glColor4d(0.0,0.2,0.5, (base_lives-lives)*1.0/base_lives * alpha);
		glCallList( mesh->MeshList );
		glColor4d(1.0,1.0,1.0,1.0);
	glPopMatrix();
}

bool CMeteor::logic( int DeltaTime )
{
	// Obliczanie nowej pozycji
	y -= cos( rotate_z) * speed * DeltaTime/1000.0 * lives * 1.0/base_lives;
	x += sin( rotate_z ) * speed * DeltaTime/1000.0 * lives * 1.0/base_lives;
	if( y <= (-1.05 - 0.15))
	{
		return true;
	}
	// Obliczanie nowego obrotu
	rotate += 360.0 * speed * DeltaTime/1000.0 / (2 * PI * radius ) * lives * 1.0/base_lives;

	// Sp³asczanie meteoroidu
	if( lives == 0 && scale_z > 0.1 )
	{
		scale_z -= 2.8 * DeltaTime/1000.0;
		if( scale_z < 0.1 )
			scale_z = 0.1;
	}

	// Znikanie meteoroidu
	if( scale_z == 0.1 && alpha > 0.0 )
	{
		alpha -= 2.0 * DeltaTime/1000.0;
		if( alpha < 0.0 )
			alpha = 0.0;
	}

	// Proœba o usuniêcie
	if( alpha == 0.0 )
	{
		return true;
	}

	return false;
}