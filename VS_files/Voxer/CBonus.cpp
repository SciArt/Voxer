/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CBonus.cpp
// Desc.: Klasa opisuj¹ca bonus
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
	this->mesh = mesh; // WskaŸnik do modelu
	this->size = size; // Rozmiar
	this->type = type; // Rodzaj bonusu
	this->value = value; // Iloœc pieniêdzy
	this->radius = 0.175 * 0.85 * size; // Obliczanie promienia
	this->y = 1.5 + this->radius; // Wysokoœæ pocz¹tkowa
	this->x = pos_x; // Pozycja pocz¹tkowa
	this->xk = pos_xk; // Pozycja koñcowa
	rotate_z = atan((xk-x)/(y+1.2)); // K¹t obrotu na osi Z
	this->speed = speed; // Szybkoœæ
}

void CBonus::draw()
{
	// Rysowanie
	glPushMatrix();
		glTranslated( x, y, z + (0.175 * 0.85) ); // Ustawienie pozycji (nad plansz¹)
		glScaled( size, size, size ); // Przeskalowanie
		glRotated( rotate_z * 180.0 / PI, 0.0, 0.0, 1.0 ); // Obrót na osi Z
		glRotated( rotate * 180.0 / PI, 0.0, 1.0, 0.0 ); // Obrót na osi Y
		mesh->Draw(); // Rysowanie modelu
	glPopMatrix();
}

bool CBonus::logic( int DeltaTime )
{
	y -= cos( rotate_z) * speed * DeltaTime/1000.0; // Liczenie nowej wspó³rzêdnej po³o¿enia Y
	x += sin( rotate_z ) * speed * DeltaTime/1000.0; // Liczenie nowej wspó³rzêdnej po³o¿enia X
	rotate += 4.0 * (1.0/size) * speed * DeltaTime/1000.0; // Liczenie nowego obrotu
	if( y <= (-1.05 - 0.15)) // Jeœli przekroczy³o margines
		return true; // Proœba o usuniêcie

	return false;
}