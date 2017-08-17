/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CWindow.h
// Desc.: Zawiera klas� okna
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CWindow_h
#define CWindow_h

#include "declarations.h"

// Deklaracje zapowiadaj�ce
struct AppSettings;

class CWindow
{
	private:
		SDL_GLContext context; //	Kontekst OpenGL

	public:
		SDL_Window *window;	// Okno

		CWindow();
		~CWindow();

		bool create( AppSettings &settings );	// Tworzenie okna
		unsigned int src_width, src_height;	// Rozdzielczo�� okna (szeroko��, wysoko��)
};

#endif