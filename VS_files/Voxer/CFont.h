/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CFont.h
// Desc.: Rysowanie napisów i obs³uga czcionki
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CFont_h
#define CFont_h

#include "declarations.h"

// Rodzaje wyrównania
enum FontAlign
{
	F_Left,
	F_Right,
	F_Center
};

class CFont
{
private:
	std::string current_text; // Aktualny tekst
	SDL_Surface *text_surface; // Tekstura z napisem (SDL)
public:
	GLuint texture; // Tekstura z napisem (OpenGL)

	CFont(){ text_surface = 0; current_text=""; texture = 0;}
	~CFont();

	// Wyœwietlanie napisu
	void RenderText( const char * text, SDL_Color color, FontAlign align, double height, double width_ratio, double x, double y, double z );
};

bool InitFont( char *font_file, int ptsize);
void DestroyFont( );

#endif