/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CButton.cpp
// Desc.: Klasa opisuj¹ca przycisk
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#include "CButton.h"
#include "CCursor.h"

bool CButton::LoadTex2( char * file_texture )
{
	SDL_Surface *tex = IMG_Load( file_texture ); // Wczytywanie tekstury (SDL)

    if(tex) // Jeœli wczytana
    {
		// Wczytywanie tekstury (OpenGL)

        glGenTextures(1, &texture2);
        glBindTexture(GL_TEXTURE_2D, texture2);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, tex->w, tex->h,
        0, GL_RGBA, GL_UNSIGNED_BYTE, tex->pixels);
        
        SDL_FreeSurface(tex); // Usuwanie tekstury (SDL)
    }
    else
    {
       SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, 
					"Data loading error...", file_texture, NULL);
	   return false;
    }
	return true;
}

void CButton::Draw()
{
	// Rysowanie przycisku

	glPushMatrix();
		glEnable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		if( mouse_on ) // Jeœli kursor na przycisku
			glBindTexture(GL_TEXTURE_2D, texture2); // Tekstura nr 2
		else
			glBindTexture(GL_TEXTURE_2D, texture); // Tekstura nr 1

		glTranslated( x, y, z ); // Przesuniêcie

		if( clicked ) // Jeœli wciœniêty
			glScaled( 0.9, 0.9, 1.0 ); // Przeskaluj

		glCallList( MeshList ); // Wyœwietl listê
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
	glPopMatrix();
}

bool CButton::Logic( CCursor *cursor )
{
	// Sprawdzanie kolizji kursora z przyciskiem
	if( cursor->x > this->x && cursor->x < (this->x + this->width) && cursor->y > this->y && cursor->y < (this->y + this->height) )
		mouse_on = true;
	else
		mouse_on = false;

	// Sprawdzanie czy przycisk jest wciœniêty
	if( mouse_on && cursor->clicked )
		clicked = true;
	else
	{
		// Sprawdzanie czy przycisk zosta³ klikniêty
		if( mouse_on && !cursor->clicked && clicked )
		{
			clicked = false;
			return true;
		}
		else
			clicked = false;
	}

	return false;
}