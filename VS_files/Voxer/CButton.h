/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CButton.h
// Desc.: Klasa opisuj¹ca przycisk
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CButton_h
#define CButton_h

#include "CMesh.h"

// Deklaracje zapowiadaj¹ce
class CCursor;

// Klasa przycisk dziedziczy po CMesh
class CButton : public CMesh
{
private:
	bool mouse_on; // Myszka na przycisku
	bool clicked; // Przycisk wciœniêty

public:
	GLuint texture2; // Druga tekstura (gdy myszka na przycisku)
	double height, width; // Wysokoœæ, szerokoœæ
	bool LoadTex2( char * file_texture ); // Wczytywanie drugiej tekstury
	void Draw(); // Rysowanie
	bool Logic( CCursor *cursor ); // Czêœæ logiczna
};

#endif