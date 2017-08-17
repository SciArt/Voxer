/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CBonus.cpp
// Desc.: Klasa opisuj�ca bonus
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CBonus.h"
#include "CMesh.h"

#define PI 3.14159265359

CBonus::CBonus()
{
	z = 0.0;
	rotate = 0.0;
}
CBonus::~CBonus()
{
}

void CBonus::load( CMesh *mesh, unsigned int type, unsigned int value, double speed, double size, double pos_x, double pos_xk )
{
	this->mesh = mesh; // Wska�nik do modelu
	this->size = size; // Rozmiar
	this->type = type; // Rodzaj bonusu
	this->value = value; // Ilo�c pieni�dzy
	this->radius = 0.175 * 0.85 * size; // Obliczanie promienia
	this->y = 1.5 + this->radius; // Wysoko�� pocz�tkowa
	this->x = pos_x; // Pozycja pocz�tkowa
	this->xk = pos_xk; // Pozycja ko�cowa
	rotate_z = atan((xk-x)/(y+1.2)); // K�t obrotu na osi Z
	this->speed = speed; // Szybko��
}

void CBonus::draw()
{
	// Rysowanie
	glPushMatrix();
		glTranslated( x, y, z + (0.175 * 0.85) ); // Ustawienie pozycji (nad plansz�)
		glScaled( size, size, size ); // Przeskalowanie
		glRotated( rotate_z * 180.0 / PI, 0.0, 0.0, 1.0 ); // Obr�t na osi Z
		glRotated( rotate * 180.0 / PI, 0.0, 1.0, 0.0 ); // Obr�t na osi Y
		mesh->Draw(); // Rysowanie modelu
	glPopMatrix();
}

bool CBonus::logic( int DeltaTime )
{
	y -= cos( rotate_z) * speed * DeltaTime/1000.0; // Liczenie nowej wsp�rz�dnej po�o�enia Y
	x += sin( rotate_z ) * speed * DeltaTime/1000.0; // Liczenie nowej wsp�rz�dnej po�o�enia X
	rotate += 4.0 * (1.0/size) * speed * DeltaTime/1000.0; // Liczenie nowego obrotu
	if( y <= (-1.05 - 0.15)) // Je�li przekroczy�o margines
		return true; // Pro�ba o usuni�cie

	return false;
}