/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CSwitch.cpp
// Desc.: Klasa opisuj¹ca przycisk - prze³¹cznik
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CSwitch.h"
#include "CMesh.h"
#include "CCursor.h"

#define NULL 0

CSwitch::CSwitch()
{
	SwitchON = NULL;
	SwitchOFF = NULL;
	state = false;
}

CSwitch::~CSwitch()
{
	if( SwitchON )
		delete SwitchON;
	if( SwitchOFF )
		delete SwitchOFF;
}

bool CSwitch::Load( char *mesh, char *tex_on, char *tex_off, 
				   double height, double width, double x, double y, double z )
{
	// Wczytywanie w³¹czonego przycisku
	SwitchON = new CMesh();
	if( !SwitchON )
		return false;
	if( !SwitchON->Load( mesh, tex_on ) )
		return false;
	
	// Wczytywanie wy³¹czonego przycisku
	SwitchOFF = new CMesh();
	if( !SwitchOFF )
		return false;
	if( !SwitchOFF->Load( mesh, tex_off ) )
		return false;

	this->height = height;
	this->width = width;
	this->x = x;
	this->y = y;
	this->z = z;

	return true;
}

bool CSwitch::Logic( CCursor *cursor )
{
	// Sprawdzanie kolizji z myszk¹
	if( cursor->x > this->x && cursor->x < (this->x + this->width) && cursor->y > this->y && cursor->y < (this->y + this->height) )
		mouse_on = true;
	else
		mouse_on = false;

	// Sprawdzanie czy przycisk wciœniêty
	if( mouse_on && cursor->clicked )
		clicked = true;
	else
	{
		// Sprawdzanie czy przycisk klikniêty
		if( mouse_on && !cursor->clicked && clicked )
		{
			clicked = false;
			state = !state; // Zmiana statusu przycisku
			return true;
		}
		else
			clicked = false;
	}

	return false;
}

void CSwitch::Draw()
{
	glPushMatrix();

	glTranslated( x, y, z ); // Ustawienie pozycji

	if( state )
		SwitchON->Draw(); // Rysowanie w³¹czonego przycisku
	else
		SwitchOFF->Draw(); // Rysowanie wy³¹czonego przycisku

	glPopMatrix();
}