/////////////////////////////////////////////////////////////////////////////////////////////
// Name: CGraphic.h
// Desc.: Zawiera klas� odpowiedzialn� za cz�� graficzn�
// Author: Gerard Wypych
/////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CGraphic_h
#define CGraphic_h

#include "declarations.h"

// Deklaracje zapowiadaj�ce
class CApp;
struct AppSettings;

class CGraphic
{
	private:
		CApp *app; // Wska�nik na klas� nadrz�dn�
	public:
		CGraphic(CApp *app){this->app = app;}
		~CGraphic(){};

		void init( AppSettings &settings ); // Inicjalizowanie grafiki
		void set_viewport( unsigned int width, unsigned int height ); // Ustawienie obszaru roboczego i perspektywy
		void draw(); // Rysowanie
};

#endif