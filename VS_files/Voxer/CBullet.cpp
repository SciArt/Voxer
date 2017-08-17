/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CLogic.cpp
// Desc.: Klasa pocisku
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CBullet.h"
#include "CMesh.h"

void CBullet::draw()
{
	glPushMatrix();

	glTranslated( x, y, 0.0 ); // Przemieszczenie
	glRotated( Rotate, 0.0, 0.0, 1.0 ); // Obrót na osi Z
	glScaled( 0.65, 0.65, 0.65 ); // Przeskalowanie
	mesh->Draw(); // Rysowanie modelu

	glPopMatrix();
}